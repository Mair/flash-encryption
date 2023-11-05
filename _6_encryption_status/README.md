# Encryption Status

```C
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
```
