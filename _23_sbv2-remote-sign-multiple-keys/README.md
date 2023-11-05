> ⚠️flashing this version will permanently change your ESP32

# Multiple signing keys

## commands

(powershell optional) view only current directory

```powershell
function prompt {
 $p = Split-Path -Leaf -Path (Get-Location)
 "$p> "
}
```

generate private keys

```bash
# you can use open ssl
openssl genrsa -out priv_key1.pem 3072
# or espsecure.py
python ${IDF_PATH}/components/esptool_py/esptool/espsecure.py  generate_signing_key --version 2 --scheme rsa3072 priv_key1.pem
```

interrogating bootloader.bin

```bash
python ${IDF_PATH}/components/esptool_py/esptool/espsecure.py signature_info_v2 bootloader.bin
```

appending keys to the bootloader

```bash
python ${IDF_PATH}/components/esptool_py/esptool/espsecure.py sign_data -k key2.pem -v 2 --append_signatures bootloader.bin

```

flashing the bootloader

```bash
idf.py bootloader-flash
```

flashing the chip if idf.py flash does not work

```bash
python <path_tools_dir>\esptool.py -p (PORT) -b 460800 --before default_reset --after no_reset --chip esp32s3 --no-stub write_flash --flash_mode dio --flash_size <size of chip>MB --flash_freq 80m 0x10000 build\partition_table\partition-table.bin 0x20000 build\flash-encryption.bin 0x3e0000 build\ota_data_initial.bin
```

inspecting the e-fuses

NB. this will not work on a chip that has its UART permanently disabled

```bash
python ${IDF_PATH}/components/esptool_py/esptool/espfuse.py -p COM9 summary
```
