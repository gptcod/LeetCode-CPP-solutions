#include "leetcode.h"

class Solution {
public:
    static int findMaxLength(vector<int> &numbers) {
        unordered_map<int, size_t> firstOccurrence; // 如有需要 可以使用数组来提高速度

        int ctr = 0;
        int maxLength = 0;

        for (size_t i = 0; i < numbers.size(); ++i) {
            if (numbers[i] == 0) {
                ++ctr; // 当值为0时增加计数
            } else {
                --ctr; // 当值为1时减少计数
            }

            if (ctr == 0) {
                maxLength = static_cast<int>(i + 1); // 计数值为0 表明从数组最左端至当前位置0和1的数量相同
            } else if (firstOccurrence.find(ctr) == firstOccurrence.end()) {
                firstOccurrence[ctr] = i; // 计数值未重复出现过 记录首次出现位置
            } else {
                maxLength = max(maxLength, static_cast<int>(i - firstOccurrence[ctr])); // 计数值重复出现过 表明从该计数值最初出现的位置至当前位置0和1的数量相同
            }
        }

        return maxLength;
    }
};
