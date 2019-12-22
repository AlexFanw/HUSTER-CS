class Solution:
    def reverse(self, x: int) -> int:
        r = 0
        i = 1 if x <= 0 else 0
        x = abs(x)
        while(x!=0):
            r = r*10+(x%10)
            x = int(x/10)
        r = r*(-1) if i == -1 else r
        return r