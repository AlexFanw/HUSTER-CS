# coding=utf-8
import pandas as pd
import jieba
import numpy as np

all = pd.read_csv("train&test/train.csv")

pos = all.loc[all['情感倾向']==1]
pos = pos['微博中文内容'].values.tolist()

neg = all.loc[all['情感倾向']==-1]
neg = neg['微博中文内容'].values.tolist()

mid = all.loc[all['情感倾向']==0]
mid = mid['微博中文内容'].values.tolist()

file = open("train&test/pos.txt",'w');
for comment in pos[0:1000]:
    file.write(comment)
    file.write('\n')
file.close()

file = open("train&test/neg.txt",'w');
for comment in neg[0:1000]:
    file.write(comment)
    file.write('\n')
file.close()

file = open("train&test/mid.txt",'w');
for comment in mid:
    file.write(comment)
    file.write('\n')
file.close()

