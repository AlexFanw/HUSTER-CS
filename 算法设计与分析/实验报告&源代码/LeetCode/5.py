a = "asdfdsasvadbb"
class Solution:
    def longestPalindrome(self, s: str):
        s_ext='#'+'#'.join(s)+'#'
        s_ext_len = len (s_ext)
        RL=[0]*s_ext_len
        mid = 0
        maxright = 0
        maxlen = 0
        for i in range(s_ext_len):
            #如果i还处于最右边界线内,找对称点的RL[i]
            if i < maxright:
                RL[i] = min (RL[2*mid-i] , maxright-i)
            else:
                RL[i] = 1
            #如果两边都没有超出边界且两边元素相同,则扩张到不能扩张为至
            while i >= RL[i] and i + RL[i] < s_ext_len and s_ext[i-RL[i]] == s_ext[i+RL[i]]:
                RL[i]+=1
            #如果最右边界扩张出去了,更新中心点
            if RL[i]+i-1 > maxright:
                maxright = RL[i]+i-1
                mid = i
            maxlen = max(maxlen,RL[i])
        final_mid = (RL.index(max(RL))-1)/2
        final_long = max(RL)/2-1         
        return s[int(final_mid-final_long):int(final_mid+final_long+1)]


c = Solution()
c.longestPalindrome(a) 