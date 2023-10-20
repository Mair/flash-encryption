#ifndef GET_AWS_S3_OBJECT_H
#define GET_AWS_S3_OBJECT_H

typedef struct s3_params_t
{
    char *access_key;
    char *secret_key;
    char *host;
    char *canonical_uri;
    char *region;

} s3_params_t;

void get_s3_headers(char *ntp_address, s3_params_t *s3_params, char *out_authorization_header, char *out_amz_date, char *out_payload_hash);
void calculate_s3_header(char *amz_date, char *date_stamp, s3_params_t *s3_params, char *authorization_header, char *out_payload_hash);

#endif