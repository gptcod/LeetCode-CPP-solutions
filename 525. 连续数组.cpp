#include "leetcode.h"

class Solution {
public:
    static int findMaxLength(vector<int> &numbers) {
        unordered_map<int, size_t> firstOccurrence;

        int ctr = 0;
        int maxLength = 0;

        for (size_t i = 0; i < numbers.size(); ++i) {
            if (numbers[i] == 0) {
                ++ctr; // 当值为0时增加计数
            } else {
                --ctr; // 当值为1时减少计数
            }

            if (ctr == 0) {
                maxLength = static_cast<int>(i + 1); // 从数组最左端到当前位置 0和1的数量相同
            } else if (firstOccurrence.find(ctr) == firstOccurrence.end()) {
                firstOccurrence[ctr] = i;
            } else {
                maxLength = max(maxLength, static_cast<int>(i - firstOccurrence[ctr])); // 计数值重复出现 表明这一段序列中0和1的数量相同
            }
        }

        return maxLength;
    }
};
