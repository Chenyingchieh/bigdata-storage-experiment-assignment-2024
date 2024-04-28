# 实验名称

搭建对象存储

## 实验环境

```shell
       /\         rick@ricksarchlinux
      /  \        os     Arch Linux
     /\   \       host   82JW Lenovo Legion R7000P2021
    /      \      kernel 6.8.1-arch1-1
   /   ,,   \     uptime 3h 20m
  /   |  |  -\    pkgs   1368
 /_-''    ''-_\   memory 6250M / 13830M
```

## 实验操作

本地使用 docker 搭建 swift 服务

创建对应的数据文件夹后

```shell
docker run -P \
--name swift \
-p 18080:8080  \
-d \
-t dockerswiftaio/docker-swift
```
