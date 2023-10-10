#
# @lc app=leetcode.cn id=16 lang=python3
#
# [16] 最接近的三数之和
#

# @lc code=start
class Solution:
    # @return an integer
    def threeSumClosest(self, num, target):
        num.sort()
        result = num[0] + num[1] + num[2]
        for i in range(len(num) - 2):
            j, l = i+1, len(num) - 1
            while j < l:
                sum = num[i] + num[j] + num[l]
                if sum == target:
                    return sum
                
                if abs(sum - target) < abs(result - target):
                    result = sum
                
                if sum < target:
                    j += 1
                elif sum > target:
                    l -= 1
            
        return result

nums = [1,2,4,8,16,32,64,128]
target = 82
test = Solution()
print(test.threeSumClosest(nums,target))

# @lc code=end

