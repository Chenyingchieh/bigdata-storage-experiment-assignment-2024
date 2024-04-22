# ʵ������
Lab3�۲����ܷ���
# ʵ�黷��
```
Microsoft Window 10 
Git-2.44.0-64-bit.exe
Visual Studio Code1.88.1.0
Server	minIO Server
Client	boto3 & mc
Enviroment	python 3.12 & s3bench
```
# ʵ���¼
## Lab 3-1 : ����
### ��һ����������װ

�ڹ������� GO ���ԣ����汾�š�

![alt text](figure/Lab3-1.png)

ʹ��`go install github.com/igneous-systems/s3bench@latest `��װ s3bench
![alt text](figure/Lab3-2.png)
��֤�Ƿ�װ�ɹ�
![alt text](figure/Lab3-3.png)

### �ڶ�����ִ�в���
ʹ��Lab2��python������test-bucket����Ͱ


ʹ������ s3bench ָ��� minIO �е� loadgen Ͱ���в���
```
s3bench -accessKey=test:tester -accessSecret=testing -bucket=testbucket -endpoint=http://localhost:12345 -numClients=2 -numSamples=10 -objectNamePrefix=loadgen -objectSize=1024 -region=us-east-1
```
��ָ���β���� `>filepath\file.filetype` �ɱ���ִ�н���� filepath\file.filetype���������
```
endpoint(s):      [http://localhost:12345]
bucket:           test-bucket
objectNamePrefix: loadgen
objectSize:       0.0010 MB
numClients:       2
numSamples:       10
verbose:       %!d(bool=false)


Generating in-memory sample data... Done (0s)

Running Write test...

Running Read test...

Test parameters
endpoint(s):      [http://localhost:12345]
bucket:           test-bucket
objectNamePrefix: loadgen
objectSize:       0.0010 MB
numClients:       2
numSamples:       10
verbose:       %!d(bool=false)


Results Summary for Write Operation(s)
Total Transferred: 0.010 MB
Total Throughput:  0.03 MB/s
Total Duration:    0.296 s
Number of Errors:  0
------------------------------------
Write times Max:       0.061 s
Write times 99th %ile: 0.064 s
Write times 90th %ile: 0.062 s
Write times 75th %ile: 0.061 s
Write times 50th %ile: 0.060 s
Write times 25th %ile: 0.059 s
Write times Min:       0.053 s


Results Summary for Read Operation(s)
Total Transferred: 0.010 MB
Total Throughput:  0.29 MB/s
Total Duration:    0.036 s
Number of Errors:  0
------------------------------------
Read times Max:       0.008 s
Read times 99th %ile: 0.008 s
Read times 90th %ile: 0.008 s
Read times 75th %ile: 0.007 s
Read times 50th %ile: 0.007 s
Read times 25th %ile: 0.006 s
Read times Min:       0.006 s

Cleaning up 10 objects...
Deleting a batch of 10 objects in range {0, 9}... Succeeded
Successfully deleted 10/10 objects in 151.4718ms
```
��ɲ��Ժ�ͨ���޸������ж�Ӧ��������ʵ�飺
```
D:\go1.21.9.windows-amd64\GO��Ŀ\library\bin> s3bench -accessKey=test:tester -accessSecret=testing -bucket=test-bucket -endpoint=http://localhost:12345 -numClients=2 -numSamples=10 -objectNamePrefix=loadgen -objectSize=1024 -region=us-east-1 >test_objectsize_1024.txt

D:\go1.21.9.windows-amd64\GO��Ŀ\library\bin> s3bench -accessKey=test:tester -accessSecret=testing -bucket=test-bucket -endpoint=http://localhost:12345 -numClients=2 -numSamples=10 -objectNamePrefix=loadgen -objectSize=2048 -region=us-east-1 >test_objectsize_2048.txt

D:\go1.21.9.windows-amd64\GO��Ŀ\library\bin> s3bench -accessKey=test:tester -accessSecret=testing -bucket=test-bucket -endpoint=http://localhost:12345 -numClients=2 -numSamples=10 -objectNamePrefix=loadgen -objectSize=4096 -region=us-east-1 >test_objectsize_4096.txt

D:\go1.21.9.windows-amd64\GO��Ŀ\library\bin> s3bench -accessKey=test:tester -accessSecret=testing -bucket=test-bucket -endpoint=http://localhost:12345 -numClients=2 -numSamples=10 -objectNamePrefix=loadgen -objectSize=8192 -region=us-east-1 >test_objectsize_8192.txt

D:\go1.21.9.windows-amd64\GO��Ŀ\library\bin> s3bench -accessKey=test:tester -accessSecret=testing -bucket=test-bucket -endpoint=http://localhost:12345 -numClients=2 -numSamples=10 -objectNamePrefix=loadgen -objectSize=16384 -region=us-east-1 >test_objectsize_16384.txt
```
## Lab 3-2 : �۲�����С�����ܵ�Ӱ��
### ����Ŀ��
�����С�Դ洢���ܵ�Ӱ��

### ���Է���
���۲�����С������Ӱ��ʱ����Ҫ��ע��д�ӳ١���������CPUʹ���ʡ��ڴ�ʹ�á�����I/O������ָ�ꡢϵͳ���ء������볬ʱ���Լ�������������Щ���ݺ�ָ�ꡣͨ���ռ��ͷ����������ݺ�ָ�꣬���ǿ��Ը�ȫ����˽�����С��ϵͳ���ܵ�Ӱ�죬���ҳ�Ǳ�ڵ�����ƿ�����Ż����ᡣ
ʹ��python��ͼ�����������oversize��ͼ�����¡�
![alt text](figure/Lab3-5.png)
![alt text](figure/Lab3-6.png)
![alt text](figure/Lab3-7.png)

����ͼ���֪�������ʺ��ӳ������ܵ������ؼ�ָ�ꡣһ����ԣ������ʸߵ�ϵͳ���ܺã����ӳٵ����ʾ��Ӧ���졣�������ǵ�ʵ���У������С�������ʺ��ӳٵ�Ӱ�첢������һ�µġ����磬1024MB��С�Ķ����ڶ���������������ߣ������ӳ�Ҳ�������ӡ�

����ʵ��������Բ�ͬ��Ӧ�ó������������󣬿�����Ҫ��ȡ��ͬ���Ż����ԡ����磬������Ҫ�������ʵ�Ӧ�ã����Կ���ʹ��С���еȴ�С�Ķ��󣻶�������Ҫ���ӳٵ�Ӧ�ã�������Ҫ�Ż������Ĵ�����ơ�

����ʵ����Զ�д�ӳټ�������Ϊ��Ӧ�Ա�����������Ӱ����й۲��������

# ʵ��С��
ʹ��S3bench�Է������������ܵĲ��ԣ������������ͼ���з�����
