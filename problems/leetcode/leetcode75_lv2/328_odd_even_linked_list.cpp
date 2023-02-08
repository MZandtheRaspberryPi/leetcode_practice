/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        /*
            so first we go through the list and count how many items we have.
            we take first entry as start of even list and keep runner for even list, set to start.
            take second entry as start of odd list, keep runner for odd list, set to start.

            keep ctr of nodes we are on, starting with 0 + 2.
            keep main runner, set to odd_runner->next.

            go through rest of list while main runner != nullptr
            runner_to_adjust = nullptr.
            if ctrl % 2 == 0, set runner_to_adjust = even_runner.
            else set runner_to_adjust = odd_runner.

            runner_to_adjust->next = main_runner;
            main_runner = main_runner->next;
            runner_to_adjust->next->next = nullptr;
            ctr ++;

            then after loop, go throug and put start of odd list to even list.

            time complexity O(N)
            space complexity O(1)
        */
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr)
        {
            return head;
        }

        ListNode* runner = head->next->next;
        ListNode* even_runner = head;
        ListNode* even_head = even_runner;
        ListNode* odd_runner = head->next;
        ListNode* odd_head = odd_runner;
        odd_head->next = nullptr;
        even_head->next = nullptr;
        int counter = 2;

        while (runner != nullptr)
        {
            ListNode* runner_to_change = nullptr;
            if (counter % 2 == 0)
            {
                runner_to_change = even_runner;
            }
            else
            {
                runner_to_change = odd_runner;
            }

            runner_to_change->next = runner;
            runner = runner->next;
            runner_to_change->next->next = nullptr;

            if (counter % 2 == 0)
            {
                even_runner = even_runner->next;
            }
            else
            {
                odd_runner = odd_runner->next;
            }
            counter++;
        }
        runner = even_head;
        while (runner->next != nullptr)
        {
            runner = runner->next;
        }
        runner->next = odd_head;
        return even_head;
    }
};
