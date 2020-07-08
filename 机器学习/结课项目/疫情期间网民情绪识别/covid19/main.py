from splitNegPos import split
if __name__ == '__main__':
    splitToTxt = split()
    splitToTxt.startSplit(1000,1000,1000) #设置读取的训练集中pos、neg、mid样本的大小