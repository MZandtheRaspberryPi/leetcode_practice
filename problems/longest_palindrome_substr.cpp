#include<string>

class Solution {
public:
    std::string longestPalindrome(std::string s) {
        // for each letter in string, loop over string in reverse looking for that letter
        // when find, start moving backthrough string checking letter by letter. if don't get a match
        // reset count and try from end - 1. exit when at start or less than. before exit set index and count of what found.
        // return that when exit.
        // this will be O(n^3) in time complexity and O(1) in space complexity
        
        // base case
        if (s.size() == 1) {
            return s;
        }
        
        int maxLen = 0;
        int maxLenIndex;
        int workingIndex;
        int consecutiveCount = 0;
        
        for (int i = 0; i < s.size(); i++) {
            workingIndex = s.size() - 1;
            consecutiveCount = 0;
            while (workingIndex >= i) {
                if (s[i + consecutiveCount] == s[workingIndex]) {
                    consecutiveCount++;
                }
                else {
                    // moving working index back to its original point
                    // it'll go down by one at the end of this loop and we'll start checking from
                    // the new position
                    workingIndex = workingIndex + consecutiveCount;
                    consecutiveCount = 0;
                }
                workingIndex--;
            }
            
            if (consecutiveCount > maxLen) {
                maxLen = consecutiveCount;
                maxLenIndex = i;
            }
            
        }
        return s.substr(maxLenIndex, maxLen);
        
    }
};

class SolutionOpt {
public:
    int expandAroundCenter(std::string s, int left, int right) {
        int L = left, R = right;
        while (L >= 0 && R < s.length() && s[L] == s[R]) {
            L--;
            R++;
        }
        return R - L - 1;
    }
public:
    std::string longestPalindrome(std::string s) {
        // notice palindromes can be expanded from centers
        // there are only 2n-1 centers. why not n centers? center palindrome could be between 2 letters
        // if even number of letters abba. center are in between two b's.
        // given we check 2n-1 centers, and each center takes n time, we are O(N^2) in time complexity
        // we store O(1)

        // checking input
        if (s.size() < 1) {
            return "";
        }

        int start = 0;
        int end = 0;
        for (int i = 0; i < s.size(); i++) {
            int len1 = expandAroundCenter(s, i, i);
            int len2 = expandAroundCenter(s, i, i + 1);
            int len = std::max(len1, len2);

            if (len > end - start) {
                start = i - (len - 1) / 2;
                end = i + len / 2;
            }

        }
        return s.substr(start, end - start + 1);

    }
};

int main() {
    SolutionOpt sol = SolutionOpt{};
    std::string res = sol.longestPalindrome("zeusnilemacaronimaisanitratetartinasiaminoracamelinsuez");
    printf("res: %s", res.c_str());
}