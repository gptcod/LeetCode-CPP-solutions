#include "leetcode.h"

class Solution {
public:
    static int removeDuplicates(vector<int> &numbers) {
        if (numbers.empty()) { return 0; }

        auto leader = numbers.begin(), follower = numbers.begin();

        while (leader != numbers.end()) {
            if (*leader == *follower) { ++leader; } // 跳过已出现元素
            else { *(++follower) = *leader++; } // 复制未出现元素
        }

        return static_cast<int>(distance(numbers.begin(), follower) + 1);
    }
};
