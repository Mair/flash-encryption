> ⚠️flashing this version will permanently change your ESP32

# Secure boot version 2

> targets the esp32s3

## commands

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

inspecting the e-fuses

```bash
python ${IDF_PATH}/components/esptool_py/esptool/espfuse.py -p COM9 summary
```
