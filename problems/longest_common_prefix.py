class Solution():
    # horizontal scanning
    # in space, we store a constant, the num chars of first string, so worst case O(200), O(1)
    # in run time, worst case is all strings same length
    # then we compare s1 with each word, ie, s character comparisons, S is sum of characters
    def longest_overlap_horiz(self, strs: list(str)) -> str:
        if len(strs) == 1:
            return strs[0]
        prefix = strs[0]
        for i in range(1, len(strs)):
            # while we havne't found prefix
            while strs[i].find(prefix) != 0:
                prefix = prefix[0:len(prefix) - 1]
                if prefix == "":
                    return prefix
        return prefix
        
    # vertical scanning. if short string is prefix at end, compare characters of words 
    # before moving on to next column. in best case, could save time
    def longest_overlap_vert(self, strs: list(str)) -> str:
        if strs == None or len(strs) == 0: return ""
        for i in range(0, len(strs[0])):
            c = strs[0][i]
            for j in range(1, len(strs)):
                # if we are at length of word if we don't have prefix to that point
                # also, check if the first word is greater length than next
                if i == len(strs[j]) or strs[j][i] != c:
                    return strs[0][0:i]
        return strs[0]
        
    # divide and conquor. LCP is associative, we can split out list into two parts,
    # find LCP of left, find LCP or right, then find LCP of both those. Divide and conquor.
    # in terms of timea complexity, in worst case, n equal strings, length m, 
    # we do O(S) comparisons, S is number of chars in array, S = m * n
    # 2 * T(n/2) + O(m), so O(S)
    # in best case: we do O(minLen * n) comparisons. 
    # space complexity. we store recursive calls in execution stack
    # lon n recursive calls, each store m space to store result, so space complexity is
    # O(m * log n)
    def divide_conquor_lcp(self, strs: list(str)) -> str:
        if strs is None or len(strs) == 0: return ""
        return self._divide_conquor_lcp_splitter(strs, 0, len(strs)-1)
        
    def _divide_conquor_lcp_splitter(self, strs: list[str], l: int, r: int) -> "":
        if l == r:
            return strs[l]
        else:
            mid = (l + r) // 2
            lcpLeft = self._divide_conquor_lcp_splitter(strs, l, mid)
            lcpRight = self._divide_conquor_lcp_splitter(strs, mid+1, r)
            return self._common_prefix(lcpLeft, lcpRight)
    
    def _common_prefix(self, left: str, right: str) -> str:
        min_len = min([len(left), len(right)])
        for i in range(0, min_len):
            if left[i] != right[i]:
                return left[0:i]
        return left[0:min_len]
        
        
        
    # this isn't what problem asked for
    def longest_overlap(self, strs: list[str]) -> str:
        prefix_possibilities = {}
        # for each word, add each possible prefix to a dictionary
        # count how many times that prefix appears
        for word in strs:
            # gotta have a prefix of at least 2 characters
            # so start letter count at 1
            # also, max prefix would be number of chars equal to length
            # so end at len(word + 1) to get the max prefix possible
            for letter_count in range(1, len(word) + 1):
                for starting_letter in range(0, len(word)):
                    ending_letter_num = starting_letter + letter_count + 1
                    # if starting at this letter and picking this many letters after
                    # would take us out of bounds, skip it
                    if ending_letter_num > len(word) + 1:
                        continue
                    # if it'll take us to the end of the word, take it all
                    if ending_letter_num == len(word) + 1:
                        prefix = word[starting_letter:]
                    else:
                        prefix = word[starting_letter:ending_letter_num]
                    # add this prefix to count, or add it as new
                    if prefix in prefix_possibilities.keys():
                        prefix_possibilities[prefix] += 1
                    else:
                        prefix_possibilities[prefix] = 1
        longest_prefix = ""
        max_prefix_count = 1
        for prefix in prefix_possibilities:
            if prefix_possibilities[prefix] > max_prefix_count:
                longest_prefix = prefix
                max_prefix_count = prefix_possibilities[prefix]
        return longest_prefix
        
    # below is n^2 for first part, and n^2 for second part, so n^4?
    # storage wise, n^2? as we store in hash map all the prefixes, n * n?
    def longest_common_prefix(self, strs: list(str)) - > str:
        prefix_possibilities = {}
        # for each word, add each possible prefix to a dictionary
        # count how many times that prefix appears
        for word in strs:
            if word == "":
                continue
            # take each run of letters as a possible prefix
            for letter_count in range(0, len(word)):
                ending_letter = letter_count + 1
                # grab all the letters
                if ending_letter == len(word):
                    prefix = word[0:]
                else:
                    prefix = word[0:ending_letter]
                    
                if prefix in prefix_possibilities.keys():
                    prefix_possibilities[prefix] += 1
                else:
                    prefix_possibilities[prefix] = 1
            
        longest_prefix = ""
        # the minimum number of matches is how many words we have
        max_prefix_count = len(strs)
        # we'll take any prefix that overlaps at the start
        # but as we go through, we want longest
        max_prefix_length = 0
        for prefix in prefix_possibilities:
            if prefix_possibilities[prefix] > max_prefix_count or (prefix_possibilities[prefix] == max_prefix_count and len(prefix) > max_prefix_length):
                longest_prefix = prefix
                max_prefix_count = prefix_possibilities[prefix]
                max_prefix_length = len(prefix)
                
        return longest_prefix
                    