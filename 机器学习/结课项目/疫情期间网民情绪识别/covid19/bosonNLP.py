# coding=utf-8
import csv
import pandas as pd
from snownlp import SnowNLP
from snownlp import sentiment


def readAndAnalysis(input, output, left=0.33, right=-0.33):
    fileIn = open(input)
    fileOut = open(output, 'w')
    result = []

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
        s = SnowNLP(lines[0])
        print(s.sentiments, lines[0])
        seg_words = ""
        for x in s.words:
            seg_words += "_"
            seg_words += x
        normalizeResult = s.sentiments
        fileOut.write(str(normalizeResult) + "\n")
        result.append(normalizeResult)
    fileOut.close()
    fileIn.close()
    print(result)
    print(trueResult[0:len(result)])
    return result, trueResult[0:len(result)]


def normalize(normalizeResult, left, right):
    normalizeResult = (2 * normalizeResult) - 1
    if normalizeResult > left:
        normalizeResult = 1
    elif normalizeResult <= left and normalizeResult >= right:
        normalizeResult = -1
    else:
        normalizeResult = 0
    return normalizeResult


def sentimentTrain(negtxt, postxt, marshal):
    print(sentiment.data_path)
    sentiment.train(negtxt, postxt)
    sentiment.save(marshal, False)

#BosonNlpScore = pd.read_csv("bosonnlp/BosonNLP_sentiment_score.txt", sep=" ", names=['key', 'score'])
#key = BosonNlpScore['key'].values.tolist()
#score = BosonNlpScore['score'].values.tolist()
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
