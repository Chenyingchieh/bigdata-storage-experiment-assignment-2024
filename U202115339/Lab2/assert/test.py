import boto3

# �޸�Ϊ����Access Key��Secret Key
access_key = 'Q7IJN4uJKI51Ww6EgnXi'
secret_key = '2DfGuyJUy5cHNUJfI7rGL7jCJc8x5uriI19AUgTN'

# �޸�ΪMinio Server�������е���ַ
endpoint_url = 'http://10.11.163.247:64264'

# ����Boto3�ͻ���
s3 = boto3.client('s3', endpoint_url=endpoint_url, aws_access_key_id=access_key, aws_secret_access_key=secret_key)

# ��ȡ���д洢Ͱ
response = s3.list_buckets()

# ��ӡ���д洢Ͱ
print("Existing buckets:")
for bucket in response['Buckets']:
    print(f"  {bucket['Name']}")