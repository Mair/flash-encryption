#include <stdio.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_http_client.h"
#include "esp_https_ota.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "protocol_examples_common.h"
#include "esp_crt_bundle.h"
#include "s3_auth_header.h"

#define TAG "OTA"
SemaphoreHandle_t ota_semaphore;

const int software_version = 1;
extern const uint8_t server_cert_pem_start[] asm("_binary_google_cer_start");

esp_err_t http_client_init(esp_http_client_handle_t http_client)
{
    char *host = "ota-flash-encryption.s3.amazonaws.com";

    char authorization_header[250] = {};
    char amz_date[30] = {};
    char content_hash[65] = {};

    s3_params_t s3_params = {
        .access_key = "AKIA2ZAB4IEWB2KDWCFS",
        .secret_key = "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",
        .host = host,
        .region = "us-east-1",
        .canonical_uri = "/flash-encryption.bin"};

    get_s3_headers("pool.ntp.org", &s3_params, authorization_header, amz_date, content_hash);

    esp_http_client_set_header(http_client, "x-amz-date", amz_date);
    esp_http_client_set_header(http_client, "Authorization", authorization_header);
    esp_http_client_set_header(http_client, "x-amz-content-sha256", content_hash);
    esp_http_client_set_header(http_client, "host", host);
    return ESP_OK;
}

void run_ota_task(void *params)
{
    while (true)
    {
        xSemaphoreTake(ota_semaphore, portMAX_DELAY);
        esp_netif_init();
        ESP_ERROR_CHECK(esp_event_loop_create_default());
        ESP_ERROR_CHECK(example_connect());

        esp_http_client_config_t clientConfig = {
            .url = "https://ota-flash-encryption.s3.amazonaws.com/flash-encryption.bin",
            .crt_bundle_attach = esp_crt_bundle_attach};

        esp_https_ota_config_t ota_config = {
            .http_config = &clientConfig,
            .http_client_init_cb = http_client_init};

        if (esp_https_ota(&ota_config) == ESP_OK)
        {
            ESP_LOGI(TAG, "OTA flash succsessfull for version %d.", software_version);
            printf("restarting in 5 seconds\n");
            vTaskDelay(pdMS_TO_TICKS(5000));
            esp_restart();
        }
        ESP_LOGE(TAG, "Failed to update firmware");
    }
}

void on_button_pushed(void *params)
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
    xTaskCreate(run_ota_task, "run_ota_task", 1024 * 4, NULL, 2, NULL);
}
