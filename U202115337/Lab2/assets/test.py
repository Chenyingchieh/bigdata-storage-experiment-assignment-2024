import boto3

# �޸�Ϊ����Access Key��Secret Key
access_key = 'xmLt6Uruw0DvkSiedNVL'
secret_key = 'tgw0XGubjYVSDtId14TdwZHqY7VvTqHAZno9d5RO'

# �޸�ΪMinio Server�������е���ַ
endpoint_url = 'http://10.21.207.28:58063/api/v1/service-account-credentials'

# ����Boto3�ͻ���
s3 = boto3.client('s3', endpoint_url=endpoint_url, aws_access_key_id=access_key, aws_secret_access_key=secret_key)

# ��ȡ���д洢Ͱ
response = s3.list_buckets()

# ��ӡ���д洢Ͱ
print("Existing buckets:")
for bucket in response['Buckets']:
    print(f"  {bucket['Name']}")