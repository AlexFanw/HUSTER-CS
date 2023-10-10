class Solution:
    def isPalindrome(self, x: int) -> bool:
        x = str(x)
        x='#'+'#'.join(x)+'#'
        x_len = len(x)
        mid = int((x_len-1)/2)
        for i in range(int((x_len-1)/2)):
            if x[mid+i] != x[mid-i]:
                return False 
        return True