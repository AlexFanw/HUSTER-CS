# coding=utf-8
from confusionMatrix import checkResult
from confusionMatrix import checkResultNoNeu
from confusionMatrix import checkResultCombNeuAndPos
from splitNegPos import split
from bosonNLP import readAndAnalysis
from bosonNLP import sentimentTrain

fileIn = 'train&test/test.txt'  # 测试文件
fileOut = 'train&test/test_predict.txt'  # 预测结果文件
filePos = 'train&test/pos.txt'
fileNeg = 'train&test/neg.txt'
fileMarshal = '/Users/alexfan/anaconda3/lib/python3.7/site-packages/snownlp/sentiment/sentiment.marshal'
fileNewMarshal = "sentiment.marshal"  # 如果是python3，则会在这个文件尾自动加上.3

'''
训练结束后，请在snownlp/sentiment/__init__.py文件中
讲data_path改成训练之后的文件路径
注意：在data_path中加的文件路径不要带上.3，因为如果是python3的话，系统会自动添加上.3
'''

if __name__ == '__main__':
    # 新建TXT切割实例
    splitToTxt = split()
    # 设置读取的训练集中pos、neg、mid样本的大小,以及训练集大小
    splitToTxt.startSplit(10000, 10000, 10000, 4500)
    # 训练自己的sentimentMarshal
    sentimentTrain(fileNeg, filePos, fileNewMarshal)
    # 读取测试文件，并开始进行打分
    result, trueResult = readAndAnalysis(fileIn, fileOut, 0.98, 0.54)
    # 预测结果
    print(result)
    # 正确结果
    print(trueResult)
    # 输出预测结果,三分类
    print(checkResult(result, trueResult))
    # 输出预测结果，二分类，剔除中性
    print(checkResultNoNeu(result, trueResult))
    # 输出预测结果，二分类，积极和中性都放在一起。
    print(checkResultCombNeuAndPos(result, trueResult))
