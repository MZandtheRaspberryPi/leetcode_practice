class Solution:
    def longestCommonPrefix(self, strs: list[str]) -> str:
        """
            take the smallest word as the possible prefix.
            then go to first entry, not the smallest word, and check what letters can keep.
            then to next entry, and so on. if get to 0 as possible prefix return "".

            time, once to find smallest. 
            then once, and for each loop, checking each letter.
            so if we have worst case scenario, same word repeated, and its 200.

            we would have O(200 + 200*200), or O(N * M) where N is num of words and M is length of words.

            space is constant.
        """
        num_words = len(strs)
        if num_words == 0:
            return ""
        possible_prefix = strs[0]
        prefix_index = 0
        for i in range(1, len(strs)):
            if len(strs[i]) < len(possible_prefix):
                possible_prefix = strs[i]
                prefix_index = i
        for i in range(0, len(strs)):
            if i == prefix_index:
                continue
            common_letters = 0
            for j in range(0, len(possible_prefix)):
                if possible_prefix[j] != strs[i][j]:
                    break
                common_letters += 1
            if common_letters < len(possible_prefix):
                possible_prefix = possible_prefix[0:common_letters]
            if len(possible_prefix) == 0:
                return ""
        return possible_prefix
