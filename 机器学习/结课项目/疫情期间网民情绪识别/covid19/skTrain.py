# coding=utf-8
import jieba
from collections import defaultdict
import os
from sklearn.feature_extraction.text import TfidfTransformer
from sklearn.feature_extraction.text import CountVectorizer


def readfile(filename):
    file = open(filename, 'r', encoding='utf-8')
    data = []
    for x in file.readlines():
        if(x.strip() != ''):
            data.append(x.strip())
    file.close()
    return data


def cut2wd(sentence):
    wordcut = jieba.cut(sentence)
    wordcheck = []
    for w in wordcut:
        wordcheck.append(w)
    stopwords = readfile('train&test/stopwords.txt')
    # print(stopwords)
    newword = []
    for w in wordcheck:
        if w in stopwords:
            continue
        else:
            newword.append(w)
    return newword


def count(words):
    corpus = words
    vectorizer = CountVectorizer(token_pattern="\\b\\w+\\b")
    transformer = TfidfTransformer(norm=None, use_idf=False)
    tf = transformer.fit_transform(vectorizer.fit_transform(corpus))
    word = vectorizer.get_feature_names()
    weight = tf.toarray()
    print(weight)
    mycp = {}
    for i in range(len(weight)):
        for j in range(len(word)):
            mycp.update({str(word[j]): int(weight[i][j])})
    return mycp


def pos(wddict):
    senlist = readfile()


if __name__ == '__main__':
    x = readfile('train&test/pos.txt')
    # print(x)
    a = cut2wd("我爱北京天安门")
    # print(a)
    b = count(["我", "爱", "中国", "噢", "我"])
    print(b)
