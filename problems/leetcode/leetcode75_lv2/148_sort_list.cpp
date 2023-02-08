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
    ListNode* sortList(ListNode* head) {
       // use merge sort. find middle of list with slow and fast ptr
       // split into two halves by setting next of slow to nullptr
        // take slow next as start of upper half, save to fast
       // sort head, recurse
       // sort fast, recurse
       // merge both halves
       //
        // in merge create new helper list node
        // copy low and high into it
        // then make current and helper left and helper right
        // set helper right to middle
        
        if (head == nullptr || head->next == nullptr)
        {
            return head;
        }
        ListNode* slow = head;
        // if list is 4 long, in one loop we will be at index 3, the last one
        // if list is 3 long, in one loop we will be at the nullptr at the end
        // if we started at the head, and 4 long, index 2 after one loop, nullptr at 2nd loop.
        // then the while condition would fail as we are looking for next in nullptr
        // if we started at head, and 3 long index 2 after one loop, real num.
        ListNode* fast = head->next;
        while(fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode* middle = slow->next;
        slow->next = nullptr;
        ListNode* new_head = sortList(head);
        ListNode* new_middle = sortList(middle);
        return merge(new_head, new_middle);
    }
    
    ListNode* merge(ListNode* low, ListNode* high)
    {
        ListNode node = ListNode(0);
        ListNode* node_ptr = &node;

        while ( low != nullptr && high != nullptr)
        {
            if (low->val < high->val)
            {
                node_ptr->next = low;
                low = low->next;
            }
            else
            {
                node_ptr->next = high;
                high = high->next;
            }
            node_ptr = node_ptr->next;
        }

        if (low != nullptr)
        {
            node_ptr->next = low;
        }
        else
        {
            node_ptr->next = high;
        }

        return node.next;
   
    }
    
};
Console
