# ʵ������
Lab2ʵ�ֻ�������
# ʵ�黷��
```
Microsoft Window 10 
Git-2.44.0-64-bit.exe
Visual Studio Code1.88.1.0
Server	minIO Server
Client	boto3 & mc
Enviroment	python 3.12
```
# ʵ���¼
## Lab 2-1 : Client - mc
### ��һ����������װ

�ڹ��� min.io ������ mc

### �ڶ���������

�� mc.exe ���ļ��д��µ�cmd������ `mc alias set name webUI username password `

���У�ʹ����ʵ webUI �Լ��û���������(Lab1�л�ȡ����Ϣ)��� webUI��username �� password

name��Ϊ�洢��������������

������ҵ�����Ϊ`mc alias set bigdata http://10.11.163.247:50493 minioadmin minioadmin`

���� `mc mb bigdata/test1`�����µ�Ͱ test1

���� `mc ls bigdata` �г������������е�Ͱ
![alt text](figure/Lab2-1.png)
���� `mc rb bigdata/test1` ɾ��Ͱ test1 
![alt text](figure/Lab2-2.png)
��������˱������Ǿ������ȷɾ����Ͱ test1��ʵ����ɾ���Ĺ��ܣ�����ԭ���ݲ���ȷ��

## Lab 2-2 : Client - boto 3 wif python
### ��һ����������װ

�ӹ������� Python 3.7���ϵİ汾�����úû�������ʹ������ָ�װʵ���ṩ��boto��Դ
```
    $ git clone https://github.com/boto/boto3.git
    $ cd boto3
    $ py -m pip install -r requirements.txt 
    $ py -m pip install -e 
```
![alt text](figure/Lab2-3.png)
������ɺ�������
![alt text](figure/Lab2-4.png)
![alt text](figure/Lab2-4.png)
### �ڶ������ڷ��������AccessKey

����minIO Server ���ò������ AccessKey & SecretKey������ֱ������Key����������

![alt text](figure/Lab2-6.png)

### ����������дpython�����ļ�

`test.py`

��������Է���˺Ϳͻ��˵����ӡ�����Ҫ�Ѵ�����е�access_key��secret_key�޸ĳ�����һ�����ɵ�һ�¡����ӳɹ�����ʱ������ӡ��������������Ͱ������

`CRUD.py`

��minIO Server���Ͱ�Ͷ��������ɾ�Ķ���һϵ��ϵ�в���

# ʵ��С��
ʹ�� mc �� boto3 minIO Server �����˻����Ĳ����������� minIO Server �Ļ���������