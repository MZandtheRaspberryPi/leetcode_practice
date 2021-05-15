class Solution():
    # horizontal scanning
    # in space, we store a constant, the num chars of first string, so worst case O(200), O(1)
    # in run time, worst case is all strings same length
    # then we compare s1 with each word, ie, s character comparisons, S is sum of characters
    def longest_overlap_horiz(self, strs: List(str)) -> str:
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



    # this isn't what problem asked for
    def longest_overlap(self, strs: List[str]) -> str:
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
    def longest_common_prefix(self, strs: List(str)) - > str:
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
                    