#include <cstdio>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int i=0,j=0;
    for(;i<numsSize;i++) {
        for (j=i+1; j < numsSize; j++) {
            if (nums[i]>target) break;
            if (nums[j] == target - nums[i]) {
                returnSize[0] = i;
                returnSize[1] = j;
                return returnSize;
            }
        }
    }
}

int main()
        {
    int num[3] = {3,2,2};
    int target = 6, numsize=3;
    int ret[2];
    twoSum(num, numsize, target, ret);
    printf("[%d , %d ]\n", ret[0],ret[1]);
    return 0;
        };