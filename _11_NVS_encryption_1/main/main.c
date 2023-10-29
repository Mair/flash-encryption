#include <stdio.h>
#include "esp_log.h"
#include "esp_vfs.h"
#include "esp_vfs_fat.h"
#include "nvs_flash.h"
#include "esp_efuse.h"
#include "esp_efuse_table.h"
#include "esp_flash_encrypt.h"
#include "esp_chip_info.h"

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

#ifndef CONFIG_NVS_ENCRYPTION
    if (nvs_flash_init())
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ESP_ERROR_CHECK(nvs_flash_init());
    }
    if (nvs_flash_init_partition("nvs_priv"))
    {
        ESP_ERROR_CHECK(nvs_flash_init_partition("nvs_priv"));
    }
#else
    const esp_partition_t *esp_partition = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_NVS_KEYS, NULL);
    nvs_sec_cfg_t nvs_sec_cfg = {};
    nvs_flash_read_security_cfg(esp_partition, &nvs_sec_cfg);
    nvs_flash_secure_init_partition("nvs_priv", &nvs_sec_cfg)
#endif
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

void print_status(void)
{
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("chip type %s silicon revision v%d.%d\n", CONFIG_IDF_TARGET,
           chip_info.revision / 100, chip_info.revision % 100);

    uint32_t bits;
#if CONFIG_IDF_TARGET_ESP32
    esp_efuse_read_field_blob(ESP_EFUSE_FLASH_CRYPT_CNT, &bits, 7);
#else
    esp_efuse_read_field_blob(ESP_EFUSE_SPI_BOOT_CRYPT_CNT, &bits, 3);
#endif
    printf("crypt cnt %lx\n", bits);

    esp_flash_enc_mode_t esp_flash_enc_mode = esp_get_flash_encryption_mode();
    switch (esp_flash_enc_mode)
    {
    case ESP_FLASH_ENC_MODE_DISABLED:
        printf("encryption mode is ESP_FLASH_ENC_MODE_DISABLED\n");
        break;
    case ESP_FLASH_ENC_MODE_DEVELOPMENT:
        printf("encryption mode is ESP_FLASH_ENC_MODE_DEVELOPMENT\n");
        break;
    case ESP_FLASH_ENC_MODE_RELEASE:
        printf("encryption mode is ESP_FLASH_ENC_MODE_RELEASE\n");
        break;
    }
}
