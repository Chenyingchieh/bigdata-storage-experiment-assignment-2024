import boto3

# �޸�Access Key��Secret Key
access_key = 'xmLt6Uruw0DvkSiedNVL'
secret_key = 'tgw0XGubjYVSDtId14TdwZHqY7VvTqHAZno9d5RO'

# �޸�ΪMinio Server�������е���ַ
endpoint_url = 'http://10.21.207.28:58063/api/v1/service-account-credentials'

s3 = boto3.client('s3',
                  endpoint_url=endpoint_url,
                  aws_access_key_id=access_key,
                  aws_secret_access_key=secret_key)

"""Ͱ����"""
# ����Ͱ
def create_bucket(bucket_name):
    s3.create_bucket(Bucket=bucket_name)
    print(f'Bucket {bucket_name} created.\n')

# �г�����Ͱ
def list_buckets():
    response = s3.list_buckets()
    buckets = [bucket['Name'] for bucket in response['Buckets']]
    return buckets

# ����Ͱ�ڶ���
def update_object(bucket_name, object_key, new_file_path):
    # �����ϴ������Ը���������
    with open(new_file_path, "rb") as f:
        s3.put_object(Bucket=bucket_name, Key=object_key, Body=f)
    
    print(f"Object '{object_key}' in bucket '{bucket_name}' updated.\n")

# ɾ��Ͱ
def delete_bucket(bucket_name):
    s3.delete_bucket(Bucket=bucket_name)
    print(f'Bucket {bucket_name} deleted.\n')

"""�������"""
# �ϴ�����
def upload_object(bucket_name, object_key, file_path):
    s3.upload_file(file_path, bucket_name, object_key)
    print(f"Object '{object_key}' from '{file_path}' uploaded to bucket '{bucket_name}'\n")

# ���ض���
def download_object(bucket_name, object_key, local_file_path):
    s3.download_file(bucket_name, object_key, local_file_path)
    print(f"Object '{object_key}' downloaded from bucket '{bucket_name}' to Local '{local_file_path}'\n")

# Ͱ�ڿ�������
def copy_object(source_bucket, source_key, dest_bucket, dest_key):
    s3.copy_object(Bucket=dest_bucket, Key=dest_key, CopySource={'Bucket': source_bucket, 'Key': source_key})
    print(f"Object '{object_key}' copied from bucket '{source_bucket}' to bucket '{dest_bucket}'\n")

# ɾ��Ͱ�ڶ���
def delete_object(bucket_name, object_key):
    s3.delete_object(Bucket=bucket_name, Key=object_key)
    print(f"Object '{object_key}' deleted from bucket '{bucket_name}'\n")


# �û�ѡ�����
while True:
    print("1. Create Bucket")
    print("2. Read Bucket(List Bucket)")
    print("3. Update Object in Bucket")
    print("4. Delete Bucket")
    print("5. Upload Object")
    print("6. Download Object")
    print("7. Copy Object")
    print("8. Delete Object")
    print("0. Exit")
    choice = input("Please KeyIn 0~8: ")

    if choice == "1":
        print("\nCreating Bucket")
        bucket_name = input("Bucket Name: ")
        create_bucket(bucket_name)

    elif choice == "2":
        print("\nListing Bucket")
        buckets = list_buckets()
        print("Bucket List:")
        for bucket in buckets:
            print(bucket)
            print()

    elif choice == "3":
        print("\nUpdating Object in Bucket")
        bucket_name = input("Bucket Name: ")
        object_key = input("Object Name: ")
        new_file_path = input("New File Path: ")
        update_object(bucket_name, object_key, new_file_path)

    elif choice == "4":
        print("\nDeleting Bucket")
        bucket_name = input("Bucket Name: ")
        delete_bucket(bucket_name)

    elif choice == "5":
        print("\nUploading New Object to Bucket")
        bucket_name = input("Bucket Name: ")
        object_key = input("Object Key: ")
        file_path = input("File Path: ")
        upload_object(bucket_name, object_key, file_path)

    elif choice == "6":
        print("\nDownloading Object from Bucket")
        bucket_name = input("Bucket Name: ")
        object_key = input("Object Key: ")
        local_file_path = input("Local File Path: ")
        download_object(bucket_name, object_key, local_file_path)

    elif choice == "7":
        print("\nCopying Object from Bucket to Bucket")
        source_bucket = input("Source Bucket Name: ") 
        source_key = input("Source Object Key: ")
        dest_bucket = input("Destination Bucket Name: ")
        dest_key = input("Destination Object Key: ")
        copy_object(source_bucket, source_key, dest_bucket, dest_key)

    elif choice == "8":
        print("Deleting Object in Bucket")
        bucket_name = input("Bucket Name: ")
        object_key = input("Object Key: ")
        delete_object(bucket_name, object_key)

    elif choice == "0":
        print("Thanks for using! See you Next Time!")
        break
    
    else:
        print("Invalid Number! Please try again!")