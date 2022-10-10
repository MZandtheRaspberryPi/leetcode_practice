#include <stack>

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
    bool isPalindrome(ListNode* head) {
        // could store the second half of the list in a stack, and pop it out and move head up each time
        // this would need to traverse once to find length
        // then traverse a second time to put everything in middle on into stack
        // then traverse a third time to the middle moving head up and popping from stack
        // and checking equality.
        
        // would operate in O(N) time, where N is length of list, but gotta do 2.5 passes.
        // storage is O(N), as we store second half of the list
        ListNode* list_ptr = head;
        int list_length = 1;
        std::stack<ListNode*> node_stack;
        while (list_ptr->next != nullptr)
        {
            list_ptr = list_ptr->next;
            list_length++;
        }
        
        int middle_point = list_length / 2;
        list_ptr = head;
        
        for (int i = 0; i < list_length; i++)
        {
            if (i > middle_point - 1)
            {
                node_stack.push(list_ptr);
            }
            list_ptr = list_ptr->next;
        }
        
        list_ptr = head;
        while(node_stack.size() > 0)
        {
            if (list_ptr->val != node_stack.top()->val)
            {
                return false;
            }
            list_ptr = list_ptr->next;
            node_stack.pop();
        }
        return true;
        
    }
};


#include <stack>

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
    bool isPalindrome(ListNode* head) {
        // we could create a coule ptrs and reverse the second half of the linked list.
        // first, find the middle. slow ptr, fast ptr, move fast twice when move slow once.
        // when fast->next is nullptr, slow is in the middle
        // then make variable tmp, prev, both ptr type
        // set prev = slow, slow = slow->next, prev->next=nullptr.
        // while slow
        // set tmp = slow->next; set slow->next = prev.
        // prev = slow; slow = tmp.
        // now slow pts to last element, and its next is second to last, reversed.
        // so now set fast to head, and check they are equal till slow is nullptr.
        
        ListNode* fast_ptr, * slow_ptr;
        fast_ptr = slow_ptr = head;
        while (fast_ptr != nullptr && fast_ptr->next != nullptr)
        {
            slow_ptr = slow_ptr->next;
            fast_ptr = fast_ptr->next->next;
        }
        
        ListNode* prev, *tmp;
        prev = slow_ptr;
        slow_ptr = slow_ptr->next;
        prev->next = nullptr; // so that we avoid a cycle later on when we loop through
        while (slow_ptr != nullptr)
        {
            tmp = slow_ptr->next;
            slow_ptr->next = prev;
            prev = slow_ptr;
            slow_ptr = tmp;
        }
        
        fast_ptr = head;
        slow_ptr = prev;
        while (slow_ptr != nullptr)
        {
            if (fast_ptr->val != slow_ptr->val)
            {
                return false;
            }
            fast_ptr = fast_ptr->next;
            slow_ptr = slow_ptr->next;
        }
        return true;
    }
};
