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

�ڹ������� GO ����

ʹ��go install github.com/igneous-systems/s3bench@latest ��װ s3bench

### �ڶ�����ִ�в���

ʹ������ s3bench ָ��� minIO �е� loadgen Ͱ���в���
```
s3bench -accessKey=PjImVufTmBqriPgzp0Zo -accessSecret=dCL3V2KvN7bAnAZzsqbGJJYObSjlah11BIvelapP -endpoint=http://10.11.163.247:55750 -bucket=loadgen -objectNamePrefix=loadgen\ -numClients=10 -numSamples=100 -objectSize=1024
```
��ָ���β���� `>filepath\file.filetype` �ɱ���ִ�н���� filepath\file.filetype
ִ�н��
## Lab 3-2 : �۲�����С�����ܵ�Ӱ��
### ����Ŀ��
�����С�Դ洢���ܵ�Ӱ��

### ���Է���
���۲�����С������Ӱ��ʱ����Ҫ��ע��д�ӳ١���������CPUʹ���ʡ��ڴ�ʹ�á�����I/O������ָ�ꡢϵͳ���ء������볬ʱ���Լ�������������Щ���ݺ�ָ�ꡣͨ���ռ��ͷ����������ݺ�ָ�꣬���ǿ��Ը�ȫ����˽�����С��ϵͳ���ܵ�Ӱ�죬���ҳ�Ǳ�ڵ�����ƿ�����Ż����ᡣ

����ʵ����Զ�д�ӳټ�������Ϊ��Ӧ�Ա�����������Ӱ����й۲��������

### ���Խű���
```
����	       ��������                 ����ͼ����                 �ļ�·��
s3bench	       tesh.sh	                myplot.py	          s3-latency
python-boto3   latency_test_MinIO.py	latency-plot.ipynb	  py-latency
```
# ʵ��С��
...
