# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def removeNthFromEnd(self, head: Optional[ListNode], n: int) -> Optional[ListNode]:
        """
        we will go through the array, keeping track of last n nodes
        at the end, we change the node before the nth from end

        time O(N) where N is length of list
        storage O(n) where n is the nth from last node
        """
        if not head or head.next == None:
            return
        runner: ListNode = head
        last_n_nodes: List[ListNode] = [None] * (n + 1)
        count:int = 0
        while runner != None:
            last_n_nodes[count % (n+1)] = runner
            count += 1
            runner = runner.next
        # last node counts as 1, to get to before last node, we subtract n
        node_to_change_index = (count - n - 1) % (n + 1)
        node_to_change = last_n_nodes[node_to_change_index]
        # removing head
        if node_to_change == None:
            return head.next
        if node_to_change.next != None:
            node_to_change.next = node_to_change.next.next
        return head
