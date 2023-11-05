# NVS Encryption

```c
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
```
