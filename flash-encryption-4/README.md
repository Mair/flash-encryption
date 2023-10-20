python c:\esp\esp-idf\components\esptool_py\esptool\esptool.py -p COM7 -b 460800 read_flash 0 0x400000 enc-flash.bin

openssl genrsa -out my_secure_boot_signing_key.pem 3072
