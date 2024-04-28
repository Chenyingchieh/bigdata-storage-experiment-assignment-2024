# 实验名称
Lab 3 观测分析性能


# 实验环境

	* 处理器	11th Gen Intel(R) Core(TM) i5-1135G7 @ 2.40GHz   2.42 GHz
	* 版本	Windows 11 家庭中文版

# 实验记录

	接着实验二的内容。
	下载s3bench.exe和run-s3bench.cmd，将其放置同一目录下。
	编辑run-s3bench.cmd，修改用户名、密码、bucket，改为minioadmin、minioadmin、textbucket。
	使用控制变量的方法，改变一项参数固定其他几项参数，如并发数 numClients、样本数 numSamples、对象尺寸 objectSize，以测试吞吐率 Throughput、读写时间 Duration 等指标。
	    * 改变并发数numClients为8、16、24，固定样本数numSamples为256，固定对象尺寸objectSize为1024。
	    * 固定并发数numClients为8，改变样本数numSamples为128、256、512，固定对象尺寸objectSize为1024。
	    * 固定并发数numClients为8，固定样本数numSamples为256，改变对象尺寸objectSize为1024、2048、4096。

# 实验小结

	观察不同的输入参数得出的运行结果，整理成表格分析可得出结论：
	 
	* 当客户端并发数增大时，吞吐率先上升在下降，时间则先下降再上升，但这里读时间的结果由于差异不大并未明显地观察到。  
	* 当样本数量增多时，吞吐率基本不变，而读写的时间会随之增大。
	* 当对象尺寸增大时，吞吐率随之增大，读写时间基本不变。   
	* 同等条件下，读速率一般远大于写速率。