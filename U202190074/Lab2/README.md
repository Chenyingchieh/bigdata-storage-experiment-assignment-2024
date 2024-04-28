# 实验名称
Lab 2 实践基本功能

# 实验环境
* 处理器	11th Gen Intel(R) Core(TM) i5-1135G7 @ 2.40GHz   2.42 GHz
* 版本	Windows 11 家庭中文版


# 实验记录

在命令行输入

	.\minio.exe server D:minio

得到服务端调用的 URL 为本机网络 IP 的 9000 端口，服务器控制台为本机网络 IP 的 64445 端口，登录的初始账号名和密码为默认值 minioadmin。

用浏览器访问 http://192.168.133.1:64445，输入上述用户名和密码后，进入界面。

可以在界面create a bucket，也可以重新打开一个命令行通过客户端访问服务器再进行bucket的添加删除查看。注意原本运行服务器minio.exe的命令行窗口不可以关掉。

* 创建新的bucket

	.\mc.exe mb mymnio/newbucket

* 查看bucket

	.\mc.exe ls myminio

* 删除指定bucket

	.\mc.exe rb myminio/newbucket

# 实验小结
	
完成一些增删查的经典操作。