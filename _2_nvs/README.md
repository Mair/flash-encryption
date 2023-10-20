# Building a basic app

    ✅create a secret
    ✅update partition table
    ✅use FAT storage

---

    ✅add NVS

## commands

```bash
# This command is used in the "steeling secrets" video
python ${IDF_PATH}/esptool.py -p COM7 -b 460800 read_flash 0 0x400000 flash.bin
```

## NVS Code

```C
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
```
