# Building a basic app

    ✅create a secret
    ✅update partition table
    ✅use FAT storage
    ✅add NVS

---

    ✅steel secrets

## commands

```bash
python ${IDF_PATH}/esptool.py -p COM7 -b 460800 read_flash 0 0x400000 flash.bin
```
