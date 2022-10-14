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
        // we could take the second node and remember it in a variable.
        // this we will have to set to as next for the last node in the every other
        // then we take a ptr to the head and move through the linked list
        // while our ptr is not nullptr
        // we check if  our ptr next is not nullptr and if head next next is not nullptr
        // if thats the case, we can simply set our ptr next to our ptr next next
        // else we are at the second to last node
        // if the list has an odd number of entries, the second to last will be the last in the tranfsormed list, so set this next to nullptr and the next of it to the start of new region
        //
        // else the list has even number of entries and we simply set this to start of next region and break
        // operate in O(1) space, O(n) time.
        
        ListNode* start_of_next_region = nullptr;
        if (head != nullptr && head->next != nullptr)
        {
          start_of_next_region = head->next;
        }
        else
        {
            return head;
        }
        
        ListNode* moving_ptr = head;
        ListNode* tmp;
        int count = 1;
        while (moving_ptr != nullptr)
        {
            tmp = moving_ptr->next;
            if (moving_ptr->next != nullptr && moving_ptr->next->next != nullptr)
            {
                moving_ptr->next = moving_ptr->next->next;
            }
            // we are at second to last and our linked list is odd in length
            // hence have to set this one to nullptr and the next to the start of new region
            else if (moving_ptr->next->next == nullptr && count % 2 == 0)
            {
                moving_ptr->next = nullptr;
                tmp->next = start_of_next_region;
                break;
            }
            // even total, so we need to set this one to start of next region, and leave last as it is.
            else
            {
                moving_ptr->next = start_of_next_region;
                break;
            }
            moving_ptr = tmp;
            count ++;
        }
        return head;
        
    }
};
