> ⚠️flashing this version will permanently change your ESP32

# Secure boot version 2 configuration

> targets the esp32s3

## commands

generate private keys

```bash
# you can use open ssl
openssl genrsa -out priv_key1.pem 3072
# or espsecure.py
python ${IDF_PATH}/components/esptool_py/esptool/espsecure.py  generate_signing_key --version 2 --scheme rsa3072 priv_key1.pem
```
