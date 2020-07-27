# coding=utf-8


def checkResult(result, realResult):
    correct = 0
    for i in range(len(result)):
        if result[i] == realResult[i]:
            correct += 1
    print("\n<***********************强校验正确率***********************>")
    print(correct/len(result))
    print("正确结果数量：{}".format(correct))
    print("全部结果数量：{}".format(len(realResult)))
    return correct, len(result)


def checkResultNoNeu(result, realResult):
    correct = 0
    sum = 0
    for i in range(len(result)):
        if realResult[i] != 0:
            sum += 1
        if result[i] == realResult[i]:
            correct += 1
    print("\n<***********************无中性校验正确率***********************>")
    print(correct/sum)
    print("正确结果数量：{}".format(correct))
    print("全部结果数量：{}".format(sum))
    return correct, sum


def checkResultCombNeuAndPos(result, realResult):
    correct = 0
    for i in range(len(result)):
        if realResult[i] == -1:
            if result[i] == -1:
                correct += 1
        else:
            if result[i] == 1 or result[i] == 0:
                correct += 1
    print("\n<***********************弱校验正确率***********************>")
    print(correct/len(result))
    print("正确结果数量：{}".format(correct))
    print("全部结果数量：{}".format(len(realResult)))
    return correct, len(realResult)
