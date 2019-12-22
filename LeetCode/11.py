L = [1,1]
class Solution:
    def maxArea(self, height : list) -> int:
        i = 0
        j = len(L)-1
        vol = (j-i)*(min(height[i],height[j]))
        for line in range(len(L)-1):
            if height[i] <= height[j]:
                i+=1
            else: j-=1
            vol_temp = (j-i)*(min(height[i],height[j]))
            vol = max(vol,vol_temp)
            print(vol)
        return vol

test = Solution()
test.maxArea(L)