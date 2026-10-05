#ifdef LOCAL
#include "local.hpp"
#endif

// 示例题：https://leetcode.com/problems/reverse-linked-list/
class Solution
{
public:
    ListNode* reverseList(ListNode* head)
    {
        ListNode* previous = nullptr;
        while (head != nullptr)
        {
            ListNode* next = head->next;
            head->next = previous;
            previous = head;
            head = next;
        }
        return previous;
    }
};

#ifdef LOCAL
int main()
{
    vector<vector<int>> cases{{1, 2, 3, 4, 5}, {1, 2}, {}, {7}, {2, 2, -1}};
    Solution solution;
    for (const auto& values : cases)
    {
        ListNode* head = local::make_list(values);
        vector<ListNode*> nodes;
        for (ListNode* p = head; p != nullptr; p = p->next) nodes.push_back(p);
        ListNode* answer = solution.reverseList(head);
        reverse(nodes.begin(), nodes.end());
        ListNode* p = answer;
        for (ListNode* expected : nodes)
        {
            assert(p == expected); // 同时检查确实是原来的节点。
            p = p->next;
        }
        assert(p == nullptr);
        auto expected = values;
        reverse(expected.begin(), expected.end());
        assert(local::list_values(answer) == expected);
        local::free_list(answer); // 反转后从新的头开始释放，不能再释放旧 head。
    }
    cout << "PASS reverse_list: " << cases.size() << " cases\n";
}
#endif
