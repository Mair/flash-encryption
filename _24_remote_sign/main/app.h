#ifndef APP_H
#define APP_H

typedef struct wifi_credentials_t
{
    char ssid[30];
    char password[30];
} wifi_credentials_t;

typedef struct api_key_t
{
    char accessKey[50];
    char secret[70];
} api_key_t;

#endif