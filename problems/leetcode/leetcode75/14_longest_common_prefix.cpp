class Solution {
public:
    bool isAnyStringEmpty(const vector<string>& strs)
    {
        for (int i = 0; i < strs.size(); i++)
        {
            if (strs[i].size() == 0)
            {
                return true;
            }
        }
        return false;
    }
    string longestCommonPrefix(vector<string>& strs) {
        // input vector will be at least 1, but given str could be empty
        // set prefix_length to zero
        // set exit flag to false
        // while not exit flag, loop over array from i = 1 to i < length
        // if str is empty set exit flag to true, break
        // if strs[i][prefix_length] == strs[i - 1][prefix_length]
        // prefix_length ++
        // else exit_flag = true, break;
        // this would operate in time O(n * m) where n is length of strs, and m is longest prefix length
        // space complexity is O(1) tho
        
        int prefix_length = 0;
        bool exit_flag = false;
        
        if (strs.size() == 1)
        {
            return strs[0];
        }
        
        if (isAnyStringEmpty(strs))
        {
            return "";
        }
        
        
        while (!exit_flag)
        {
            bool common_prefix = true;
            for (int i = 1; i < strs.size(); i++)
            {
                if (strs[i-1].size() <= prefix_length || strs[i].size() <= prefix_length)
                {
                    exit_flag = true;
                    common_prefix = false;
                    break;
                }
                
                if (strs[i][prefix_length] == strs[i - 1][prefix_length])
                {
                    continue;
                }
                else
                {
                    common_prefix = false;
                    exit_flag = true;
                    break;
                }
            }
            if (common_prefix)
            {
                prefix_length++;
            }
        }
        std::string longest_common_prefix = "";
        longest_common_prefix.resize(prefix_length);
        for (int i = 0; i < prefix_length; i ++)
        {
            longest_common_prefix[i] = strs[0][i];
        }
        return longest_common_prefix;
    }
};
