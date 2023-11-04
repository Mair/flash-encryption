#include <stdio.h>
#include <string.h>
#include "wifi_connect.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_https_ota.h"
#include "esp_http_client.h"
#include "app.h"
#include "esp_crt_bundle.h"
#include "nvs_flash.h"
#include "s3_auth_header.h"

static char *TAG = "OTA";
static SemaphoreHandle_t ota_semaphore;

void get_wifi_creds(wifi_credentials_t *wifi_credentials);
void get_s3_creds(api_key_t *api_key);

static esp_err_t http_client_init(esp_http_client_handle_t esp_http_client)
{
    api_key_t api_key;
    get_s3_creds(&api_key);

    s3_params_t s3_params = {
        .access_key = api_key.accessKey,
        .secret_key = api_key.secret,
        .host = "ota-flash-encryption.s3.amazonaws.com",
        .region = "us-east-1",
        .canonical_uri = "/flash-encryption.bin",
        .method = "GET",
        .should_get_time = true};

    http_client_set_aws_header(esp_http_client, &s3_params);

    return ESP_OK;
}

static void run_ota_task(void *params)
{
    while (true)
    {
        xSemaphoreTake(ota_semaphore, portMAX_DELAY);
        wifi_connect_init();
        wifi_credentials_t wifi_credentials;
        get_wifi_creds(&wifi_credentials);
        wifi_connect_sta(wifi_credentials.ssid, wifi_credentials.password, 10000);

        esp_http_client_config_t esp_http_client_config = {
            .url = "https://ota-flash-encryption.s3.amazonaws.com/flash-encryption.bin",
            .crt_bundle_attach = esp_crt_bundle_attach};

        esp_https_ota_config_t esp_https_ota_config = {
            .http_config = &esp_http_client_config,
            .http_client_init_cb = http_client_init};

        if (esp_https_ota(&esp_https_ota_config) == ESP_OK)
        {
            ESP_LOGI(TAG, "OTA successful");
            printf("restarting in 3 seconds\n");
            vTaskDelay(pdMS_TO_TICKS(3000));
            esp_restart();
        }
        ESP_LOGE(TAG, "Failed to update firmware");
    }
}

static void IRAM_ATTR on_button_pushed(void *args)
{
    xSemaphoreGiveFromISR(ota_semaphore, pdFALSE);
}

void init_ota(void)
{
    gpio_set_direction(GPIO_NUM_0, GPIO_MODE_INPUT);
    gpio_set_intr_type(GPIO_NUM_0, GPIO_INTR_NEGEDGE);
    gpio_install_isr_service(0);
    gpio_isr_handler_add(GPIO_NUM_0, on_button_pushed, NULL);

    ota_semaphore = xSemaphoreCreateBinary();
    xTaskCreate(run_ota_task, "run_ota_task", 1024 * 10, NULL, 5, NULL);
}

void get_wifi_creds(wifi_credentials_t *wifi_credentials)
{
    FILE *file = fopen("/fat/wifi", "r");
    fread(wifi_credentials, sizeof(wifi_credentials_t), 1, file);
    fclose(file);
}

void get_s3_creds(api_key_t *api_key)
{
    nvs_handle_t nvs_handle;
    nvs_open_from_partition("nvs_priv", "store", NVS_READONLY, &nvs_handle);
    size_t max_size = sizeof(api_key->accessKey);
    nvs_get_str(nvs_handle, "S3_ACCESS", api_key->accessKey, &max_size);
    max_size = sizeof(api_key->secret);
    nvs_get_str(nvs_handle, "S3_SECRET", api_key->secret, &max_size);
    nvs_close(nvs_handle);
}