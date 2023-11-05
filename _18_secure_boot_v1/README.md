> ⚠️flashing this version will permanently change your ESP32

# Secure boot version 1

## commands

Use either of the below two commands to generate an elliptic private key.

```bash
# you can use espsecure.py
python ${IDF_PATH}/components/esptool_py/esptool/espsecure.py generate_signing_key key.pem
# or openssl
openssl ecparam -name prime256v1 -genkey -noout -out key.pem
```

## resources

to convert bytes sizes to hex you can use the [online byte converter](https://www.alterlinks.com/byte-converter/byte-converter.php)

If you are interested on how the Elliptic Curves works, check this out.

[![youtube elliptic curve](https://img.youtube.com/vi/NF1pwjL9-DE/0.jpg)](https://www.youtube.com/watch?v=NF1pwjL9-DE)
