#include <stdio.h>
#include "esp_log.h"
#include "esp_vfs.h"
#include "esp_vfs_fat.h"
#include "nvs_flash.h"

typedef struct wifi_credentials_t
{
    char ssid[30];
    char password[30];
} wifi_credentials_t;

typedef struct api_key_t
{
    char key[30];
} api_key_t;

void print_status(void);

void app_main(void)
{
    print_status();

    wifi_credentials_t wifi_credentials_init = {
        .ssid = "WIFI_DEFAULT_SSID",
        .password = "WIFI_DEFAULT_PASSWORD1",
    };

    esp_vfs_fat_mount_config_t esp_vfs_fat_mount_config = {
        .allocation_unit_size = CONFIG_WL_SECTOR_SIZE,
        .max_files = 5,
        .format_if_mount_failed = true};

    wl_handle_t wl_handle;
    esp_vfs_fat_spiflash_mount_rw_wl("/fat", "storage", &esp_vfs_fat_mount_config, &wl_handle);

    FILE *file = fopen("/fat/wifi", "w");
    fwrite(&wifi_credentials_init, sizeof(wifi_credentials_t), 1, file);
    fclose(file);

    file = fopen("/fat/wifi", "r");
    wifi_credentials_t wifi_credentials;
    fread(&wifi_credentials, sizeof(wifi_credentials_t), 1, file);
    fclose(file);

    ESP_LOG_BUFFER_HEXDUMP("WIFI CREDS", &wifi_credentials, sizeof(wifi_credentials_t), ESP_LOG_INFO);

    /****************************************/

    ESP_ERROR_CHECK(nvs_flash_erase_partition("nvs_priv"));
    ESP_ERROR_CHECK(nvs_flash_init_partition("nvs_priv"));
    nvs_handle_t nvs_handle;
    nvs_open_from_partition("nvs_priv", "store", NVS_READWRITE, &nvs_handle);
    nvs_set_str(nvs_handle, "API_KEY", "API_KEY_abcdefg");
    nvs_commit(nvs_handle);
    nvs_close(nvs_handle);

    nvs_open_from_partition("nvs_priv", "store", NVS_READONLY, &nvs_handle);
    api_key_t api_key = {};
    size_t max_size = sizeof(api_key.key);
    nvs_get_str(nvs_handle, "API_KEY", api_key.key, &max_size);
    ESP_LOGI("API KEY", "%s", api_key.key);
    nvs_close(nvs_handle);
}
