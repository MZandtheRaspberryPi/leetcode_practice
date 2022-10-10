#include<deque>

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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // traverse list till find the end, keep track of previous n + 1 node ptrs
        // when reach end, if n+1 node is not nullptr point the n + 1 from end node to the next node of n
        // if it is nullptr, then put root next to nullptr
        // o(N) in terms of time complexity, where N is the length of linked list
        // o(n + 1) in terms of space complexity, where n is the number of nodes from the end
        // delete and free memory?
        // alternative idea is to use fast and slow ptr, stagger them by n. saves memory.
        ListNode* list_ptr = head;
        std::deque<ListNode*> prior_nodes;
        int deque_max_size = n + 1;
        for (int i = 0; i < deque_max_size; i++)
        {
            prior_nodes.push_front(nullptr);
            
        }
        while (list_ptr != nullptr)
        {
            if (prior_nodes.size() == deque_max_size)
            {
                prior_nodes.pop_back();
            }
            prior_nodes.push_front(list_ptr);
            list_ptr = list_ptr->next;
        }
        list_ptr = prior_nodes.at(n);
        // we will remove all of our list, dont have enough entries to keep any
        if (list_ptr == nullptr && prior_nodes.at(n - 1) == nullptr)
        {
            head = nullptr;
        }
        else if (list_ptr == nullptr && prior_nodes.at(n - 1) != nullptr)
        {
            head = prior_nodes.at(n-1)->next;
            
        }
        else
        {
            list_ptr->next = prior_nodes.at(n - 1)->next;
        }
        return head;
        
    }
};

#include<deque>

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
class SolutionOptimal {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // create 2 ptrs, fast ptr and slow ptr
        // move the fast ptr ahead by n, checking each time to see if next is nullptr and if so
        // breaking. if we break, the list isnt long enough, so we have to move head to head->next and return it
        // now, while fast_ptr->next isnt nullptr, move both up
        // at the end set slow_ptr->next to slow_ptr->next->next
        // return head.
        // will operate in O(N) where N is the length of linked list
        // storage is O(1)
        ListNode* slow_ptr;
        ListNode* fast_ptr;
        slow_ptr = fast_ptr = head;
        for (int i = 0; i < n; i++)
        {
            if (fast_ptr->next != nullptr)
            {
                fast_ptr = fast_ptr->next;
            }
            else
            {
                head = head->next;
                return head;
            }
        }
        
        while (fast_ptr->next != nullptr)
        {
            fast_ptr = fast_ptr->next;
            slow_ptr = slow_ptr->next;
        }
        
        slow_ptr->next = slow_ptr->next->next;
        return head;
        
    }
};
