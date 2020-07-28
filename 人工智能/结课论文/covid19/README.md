# 疫情期间网民情绪识别

### 设计步骤

- 一开始是打算使用BosonNLP的库来做的，但是后来发现效果奇差无比。所以后来便改用了sklearn了。
- 其实直接用百度的自然语言分析的黑盒API也可以，但是那样的话就完全越过了训练步骤，纯粹的是测试了，没有意义。
- 7.11 sklearn的训练速度很慢，所以再次选择SnowNLP来进行训练
- 7.12 SVM & 词向量方法加入
- 7.15 SnowNLP数据清洗，微博的很多奇怪的title会非常影响判断结果



### 文件说明

- bosonnlp: BosonNLP分词打分文件
- train&test: 训练集数据、测试集数据
- main.py: 入口函数
- alexNLP.py: snowNLP封装
- confusionMatrix.py: 校验函数包
- splitNegPos.py: 积极、负面词条划分函数包
- statistics.py: 统计函数
- skTrain.py: sklearn函数包（只是某些地方需要用到sklearn的函数，大部分函数是用不到）
- test.py: 测试函数（白盒测试文件）
- sentiment.marshal.3: 自己训练的训练集