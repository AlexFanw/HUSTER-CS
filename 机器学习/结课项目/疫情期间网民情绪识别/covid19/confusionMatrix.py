# coding=utf-8


def checkResult(result,realResult):
    correct = 0
    for i in range(len(result)):
        if result[i] == realResult[i]:
            correct += 1
    print(correct, len(result))
    return correct / len(result)

def checkResultNoMid(result, realResult):
    correct = 0
    sum = 0
    for i in range(len(result)):
        if realResult[i] != 0:
            sum += 1
        if result[i] == realResult[i]:
            correct += 1
    print(correct, sum)
    return correct / sum