#include "leetcode.h"

class Solution {
public:
    static ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        stack<int> s1, s2; // 使用栈反转链表

        while (l1) { s1.push(l1->val); l1 = l1->next; }
        while (l2) { s2.push(l2->val); l2 = l2->next; }

        int carry = 0, v1 = 0, v2 = 0, s = 0;
        auto *head = new ListNode(0);

        while (true) {
            bool e1 = s1.empty(), e2 = s2.empty();

            if (e1 && e2 && carry == 0) { break; }
            if (!e1) { v1 = s1.top(); s1.pop(); } else { v1 = 0; }
            if (!e2) { v2 = s2.top(); s2.pop(); } else { v2 = 0; }

            s = v1 + v2 + carry; // 求和并处理进位
            carry = s / 10;
            s %= 10;

            auto next = head->next;
            head->next = new ListNode(s); // 头插法构造链表
            head->next->next = next;
        }

        return head->next;
    }
};
