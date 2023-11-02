> ⚠️flashing this version will permanently change your ESP32

# Secure boot version 1

## commands

to generate an elliptic private key you can either use

```bash
# espsecure.py
python ${IDF_PATH}/components/esptool_py/esptool/espsecure.py generate_signing_key key.pem
# or openssl
openssl ecparam -name prime256v1 -genkey -noout -out key.pem
```

## resources

[online byte converter](https://www.alterlinks.com/byte-converter/byte-converter.php)

If you are interested on Elliptic Curves work check this out

[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/NF1pwjL9-DE/0.jpg)](https://www.youtube.com/watch?v=NF1pwjL9-DE)

https://www.youtube.com/watch?v=NF1pwjL9-DE

python c:\esp\esp-idf\components\esptool_py\esptool\esptool.py -p COM7 -b 460800 read_flash 0 0x400000 enc-flash.bin
