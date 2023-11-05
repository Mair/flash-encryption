# Flash encrypting

Welcome to the course on ESP32 flash encryption. 

In this course, you will learn how to use the flash encryption feature of the ESP32 microcontroller to protect your firmware and data from unauthorized access.

*Flash encryption is a security mechanism that encrypts the contents of the external flash memory using a hardware-generated AES(Advanced Encryption Standard)-256 key*. This key is stored in a secure storage called eFuse, which is inaccessible to software. Once flash encryption is enabled, the firmware is flashed as plaintext, and then encrypted in place on the first boot. As a result, physical readout of flash will not be sufficient to recover most flash contents.

![Alt text](https://github.com/Mair/flash-encryption/blob/main/_0_intro/Secure%20chip.jpg?raw=true)

Flash encryption can be used together with secure boot, which is another security feature that verifies the digital signature of the firmware before executing it.

*Secure boot ensures that only authorized and unmodified firmware can run on the ESP32*. 

Flash encryption and secure boot can provide a high level of protection for your ESP32 applications.

In this course, you will learn how to enable flash encryption in different modes, how to configure the flash encryption settings, how to use encrypted partitions, and how to update your firmware after flash encryption is enabled. You will also learn about the eFuses that control the flash encryption operation, and how to use the ESP-IDF tools to manage them. You will also see some examples and demos of flash encryption in action.

By the end of this course, you will have a solid understanding of how flash encryption works on the ESP32, and how to use it effectively in your projects. You will also be able to apply the best practices and recommendations for using flash encryption in production.

## Getting the most from this course

To get the most out of this course I recommend that you have some experience with ESP32 development and ESP-IDF. You should be familiar with the basic concepts of ESP32 programming, such as partitions, bootloader, app binary format, etc.
If you need to learn this information or need a refresher please have a look at https://learnesp32.com which could be considered a good prerequisite

## Hardware you will need

### ESP32

All that is required for this course are some basic esp32 boards. As we are making physical changes to the hardware and there is a high risk of bricking the chips I recommend having a few around

![Alt text](https://github.com/Mair/flash-encryption/blob/main/_0_intro/esp32.jpg?raw=true)

### ESP32S3 /ESP32C3

Later in this course we cover Secure boot version 2 which is only available on some of the more modern chips. If you which to explore these options and test them out you will need a newer model of the ESP32 such as the ESP32S3
![Alt text](https://github.com/Mair/flash-encryption/blob/main/_0_intro/esp32s3.png?raw=true)

## Lets start

If you are ready to learn more about ESP32 flash encryption, let’s get started!
