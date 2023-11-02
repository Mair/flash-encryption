openssl genrsa -out priv_key1.pem 3072

espsecure.py sign_data BINARY_FILE --version 2 --keyfile PRIVATE_SIGNING_KEY

python C:\esp\esp-idf\components\esptool_py\esptool\espsecure.py sign_data -k key2.pem -v 2 --append_signatures bootloader.bin

python C:\esp\esp-idf\components\esptool_py\esptool\espsecure.py signature_info_v2 bootloader.bin

python C:\esp\esp-idf\components\esptool_py\esptool\esptool.py -p COM9 -b 460800 --before default_reset --after no_reset --chip esp32s3 --no-stub write_flash --flash_mode dio --flash_size 16MB --flash_freq 80m 0x0 bootloader.bin

python C:\esp\esp-idf\components\esptool_py\esptool\esptool.py  -p COM9 -b 460800 --before default_reset --after no_reset --chip esp32s3 --no-stub write_flash --flash_mode dio --flash_size 16MB --flash_freq 80m 0x10000 partition-table.bin 0x20000 flash-encryption.bin 0x2a0000 ota_data_initial.bin 0x160000 flash-encryption.bin

python C:\esp\esp-idf\components\esptool_py\esptool\espsecure.py sign_data bootloader.bin --version 2 --keyfile priv_key1.pem


c:\esp\tools\python_env\idf5.0_py3.8_env\Scripts\python.exe ..\..\..\..\..\esp\esp-idf\components\esptool_py\esptool\esptool.py -p COM9 -b 460800 --before default_reset --after no_reset --chip esp32s3 --no-stub write_flash --flash_mode dio --flash_size 16MB --flash_freq 80m 0x10000 partition-table.bin 0x20000 flash-encryption.bin 0x3e0000 ota_data_initial.bin


c:\esp\tools\python_env\idf5.0_py3.8_env\Scripts\python.exe ..\..\..\..\esp\esp-idf\components\esptool_py\esptool\esptool.py -p COM9 -b 460800 --before default_reset --after no_reset --chip esp32s3 --no-stub write_flash --flash_mode dio --flash_size 16MB --flash_freq 80m 0x10000 build\partition_table\partition-table.bin 0x20000 build\flash-encryption.bin 0x3e0000 build\ota_data_initial.bin