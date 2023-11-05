# AWS IAM policies

below are some AWS policies to allow access to S3 buckets

## Read only permissions

```json
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Sid": "MyReadWriteBucketPolicyV1",
      "Effect": "Allow",
      "Action": ["s3:ListBucket", "s3:GetObject*"],
      "Resource": [
        "arn:aws:s3:::esp-read-write",
        "arn:aws:s3:::esp-read-write/*"
      ]
    }
  ]
}
```

## read and write

```json
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Sid": "MyReadWriteBucketPolicyV1",
      "Effect": "Allow",
      "Action": [
        "s3:ListBucket",
        "s3:GetObject*",
        "s3:PutObject*",
        "s3:DeleteObject*"
      ],
      "Resource": [
        "arn:aws:s3:::esp-read-write",
        "arn:aws:s3:::esp-read-write/*"
      ]
    }
  ]
}
```

## read and write on multiple buckets

```json
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Sid": "MyReadWriteBucketPolicyV1",
      "Effect": "Allow",
      "Action": [
        "s3:ListBucket",
        "s3:GetObject*",
        "s3:PutObject*",
        "s3:DeleteObject*"
      ],
      "Resource": [
        "arn:aws:s3:::esp-read-write",
        "arn:aws:s3:::esp-read-write/*"
        "arn:aws:s3:::my-other-bucket",
        "arn:aws:s3:::my-other-bucket/*"
      ]
    }
  ]
}
```
