# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def isPalindrome(self, head: Optional[ListNode]) -> bool:
        """
        could get length of list.
        then find middle of list, and save as var.

        then go into recursive function that recurses until before middle.
        then it checks its value with the middle next counters, if false returns false.
        if true, increments counter.

        storage: some needed for recursive call O(N) (N/2 really)
        time: O(N)

        do i need to use recursion, could i flip around the last half?

        set node prior to middle next to None.
        set new head, set val to middle, next to None.
        then go to next middle. new node, val to middle next, next to new head.
        new head to new node.

        so on. re-arranging list on the fly.
        O(N) time
        O(1) in space, tho in python more may get allocated unless init with copy...
        """
        if not head:
            return False
        if head.next == None:
            return True
        
        count: int = 0
        runner: ListNode = head
        while runner != None:
            count += 1
            runner = runner.next
        
        cur_count: int = 0
        runner = head
        prev: ListNode = None
        while cur_count < (count // 2):
            cur_count += 1
            prev = runner
            runner = runner.next
        
        # if odd, skip middle
        if count % 2 == 1:
            runner = runner.next

        new_head: ListNode = runner
        prev.next = None
        runner = runner.next
        new_head.next = None
        new_node: ListNode = None
        while runner != None:
            new_node = runner
            runner = runner.next
            new_node.next = new_head
            new_head = new_node
        runner = head
        runner_new: ListNode = new_head
        while runner != None:
            if runner.val != runner_new.val:
                return False
            runner = runner.next
            runner_new = runner_new.next
        return True
