class Solution:
    def intToRoman(self,num:int) -> str:
        r = ['M','CM','D','CD','C','XC','L','XL','X','IX','V','IV','I']
        rint = [1000,900,500,400,100,90,50,40,10,9,5,4,1]
        roman = ''
        for i in range(len(r)):
            while(num >= rint[i]):
                roman = roman + r[i]
                num -= rint[i]
        return roman