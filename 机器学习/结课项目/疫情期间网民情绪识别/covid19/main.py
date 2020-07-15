# coding=utf-8
from confusionMatrix import checkResult
from splitNegPos import split
from bosonNLP import readAndAnalysis
from bosonNLP import sentimentTrain
fileIn = 'train&test/test.txt' #测试文件
fileOut = 'train&test/test_predict.txt' #预测结果文件
filePos = 'train&test/pos.txt'
fileNeg = 'train&test/neg.txt'
fileMarshal = '/Users/alexfan/anaconda3/lib/python3.7/site-packages/snownlp/sentiment/sentiment.marshal'
fileNewMarshal = "sentiment.marshal" #如果是python3，则会在这个文件尾自动加上.3

'''
训练结束后，请在snownlp/sentiment/__init__.py文件中
讲data_path改成训练之后的文件路径
注意：在data_path中加的文件路径不要带上.3，因为系统会自动添加上.3
'''


if __name__ == '__main__':
    #splitToTxt = split()
    #splitToTxt.startSplit(10000,1000,10000,200) #设置读取的训练集中pos、neg、mid样本的大小,以及训练集大小
    #sentimentTrain(fileNeg, filePos, fileNewMarshal) #训练自己的sentimentMarshal
    result,trueResult = readAndAnalysis(fileIn,fileOut)
    #print(checkResult(result,trueResult))