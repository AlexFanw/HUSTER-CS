# coding=utf-8
import pandas as pd
import jieba
import numpy as np
from snownlp import SnowNLP
from snownlp import sentiment
import pandas as pd
import numpy as np
import jieba

def GetScore(line, score, key):
    segs = jieba.lcut(line)
    score_list = [score[key.index(x)] for x in segs if (x in key)]
    # print(segs)
    return sum(score_list)


BosonNlpScore = pd.read_csv("bosonnlp//BosonNLP_sentiment_score.txt", sep=" ", names=['key', 'score'])
key = BosonNlpScore['key'].values.tolist()
score = BosonNlpScore['score'].values.tolist()

sentiment.train('train&test/neg.txt','train&test/pos.txt')
sentiment.save('/Users/alexfan/anaconda3/lib/python3.7/site-packages/snownlp/sentiment/sentiment.marshal')

'''
获取test.csv中所有的舆论
'''
test = pd.read_csv("train&test/test.csv")
# print(test)
test_list = test.values.tolist()
test_str = []
for i in test_list:
    test_str.append(i[0])

'''
获取test_label.csv的最终结果标识
'''
test_label = pd.read_csv("train&test/test_label.csv")
test_label = test_label["情感倾向"].values.tolist()

result = []
for comment in test_str[0:100]:
    #comment_predict = int(GetScore(comment, score, key))
    # if(comment_predict>0):comment_predict=1
    # if(comment_predict<0):comment_predict=-1
    comment = SnowNLP(comment)
    result.append(comment.sentiments)

print(test_label)
print(result)
