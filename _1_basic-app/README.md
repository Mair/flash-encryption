# Building a basic app

```c
#include <stdio.h>
#include "esp_log.h"
#include "esp_vfs.h"
#include "esp_vfs_fat.h"

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
}

```
