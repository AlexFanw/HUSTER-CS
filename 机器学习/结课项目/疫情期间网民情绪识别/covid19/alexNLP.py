# coding=utf-8
import csv
import pandas as pd
from snownlp import SnowNLP
from snownlp import sentiment
from skTrain import cut2wd


def readAndAnalysis(input, output, left=0.5, right=0.5):
    fileIn = open(input)
    fileOut = open(output, 'w')
    result = []
    # trueResult保存正确的预测结果
    with open('train&test/test_label.csv', 'r') as realResult:
        reader = csv.reader(realResult)
        trueResult = [row[1] for row in reader]
        trueResult = trueResult[1:]
        for i in range(len(trueResult)):
            trueResult[i] = round(float(trueResult[i]))

    while True:
        line = fileIn.readline()
        if not line:
            break
        lines = line.strip().split("\t")
        if(len(lines)) != 1:
            continue
        if(lines[0] == ''):
            lines[0] = "NAN"
            fileOut.write("0\n")
            result.append(0)
        else:
            s = SnowNLP(lines[0])
            normalizeResult = normalize(s.sentiments, left, right)
            fileOut.write(str(normalizeResult) + "\n")
            result.append(normalizeResult)
    fileOut.close()
    fileIn.close()
    return result, trueResult[0:len(result)]


def normalize(normalizeResult, left, right):
    if normalizeResult > left:
        normalizeResult = 1
    elif normalizeResult <= left and normalizeResult >= right:
        normalizeResult = 0
    else:
        normalizeResult = -1
    return normalizeResult


def sentimentTrain(negtxt, postxt, marshal):
    print("训练集保存地址为：{}\n".format(sentiment.data_path))
    sentiment.train(negtxt, postxt)
    sentiment.save(marshal, False)
    print("训练结束，请开始测试。")

# BosonNlpScore = pd.read_csv("bosonnlp/BosonNLP_sentiment_score.txt", sep=" ", names=['key', 'score'])
# key = BosonNlpScore['key'].values.tolist()
# score = BosonNlpScore['score'].values.tolist()
#
# def GetScore(line, score, key):
#    segs = jieba.lcut(line)
#    score_list = [score[key.index(x)] for x in segs if (x in key)]
#    return sum(score_list)
#
# def test():
#    '''
#    获取test.csv中所有的舆论
#    '''
#    test = pd.read_csv("train&test/test.csv")
#    test_list = test.values.tolist()
#    test_str = []
#    for i in test_list:
#        test_str.append(i[0])
#    '''
#    获取test_label.csv的最终结果标识
#    '''
#    test_label = (pd.read_csv("train&test/test_label.csv"))["情感倾向"].values.tolist()
#    result = []
#    for comment in test_str[0:100]: #这里为了效率只取100个。
#        #comment_predict = int(GetScore(comment, score, key))
#        # if(comment_predict>0):comment_predict=1
#        # if(comment_predict<0):comment_predict=-1
#        comment = SnowNLP(comment)
#        result.append(comment.sentiments)
#    return result
#
# if __name__ == '__main__':
#    print(GetScore("我太爱这个玩具熊了",score,key))
#    print(test())
