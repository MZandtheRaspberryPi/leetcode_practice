class Solution {
public:
    int longestPalindrome(vector<string>& words) {
        // examplification
        // solve simpler problem
        // datastructure brainstorm
        // solve for base case
        // pattern matching
        
        // examplification
        // it has to have a pair in the array that is reversed
        // so we could a new array of bools of length words
        // that stores whether we have used a word already
        // then we iterate through words
        // for each element, iterate through words again
        // if indexes match continue
        // else check if the first letter of the first word matches the second letter of the second word
        // and check if the second letter of the first word matches the first letter of the first word
        // if so, check if the second word index is already true, if so, continue, if not set to true then break
        
        // check the unmatched same letters, if we have one left we can increment answer by 2
        
        
        // and then iterate through our bool vector and count the number of trues.
        // return that number multiplied by 2.
        // time complexity O(N^2), storage complexity O(N)
        
        std::vector<bool> words_used(words.size(), false);
        for (int i = 0; i < words.size(); i++)
        {
            
            if (words_used[i])
            {
                continue;
            }
            
            for (int j = 0; j < words.size(); j++)
            {
                if (i == j)
                {
                    continue;
                }
                if (words_used[j])
                {
                    continue;
                }
                
                if (words[i][0] == words[j][1] && words[i][1] == words[j][0])
                {
                    words_used[i] = true;
                    words_used[j] = true;
                    break;
                }
            }
        }
        
        int palindrome_words = 0;
        bool repeat_letters_for_middle_sed = false;
        for (int i = 0; i < words.size(); i++)
        {
            palindrome_words += words_used[i];
            if (!words_used[i] && words[i][0] == words[i][1])
            {
                repeat_letters_for_middle_sed = true;
            }
        
        }
        
        if (repeat_letters_for_middle_sed)
        {
            palindrome_words++;
        }
            
        
        return palindrome_words * 2;
        
    }
};

#include <unordered_map>

std::string reverseString(const std::string& in_string)
{
    char tmp;
    int middle = in_string.size() / 2;
    int str_size = in_string.size();
    std:string out_string = in_string;
    for (int i = 0; i < middle; i++)
    {
        tmp = in_string[i];
        out_string[i] = in_string[str_size - 1 - i];
        out_string[str_size - 1 -i] = tmp;
    }
    return out_string;
    
}

class SolutionOptimal {
public:
    int longestPalindrome(vector<string>& words) {
        // we create an unordered map of strings ints
        // we then loop through the words vector, and for each word
        // if it has the same letter twice, we check if its in the map already
        // and if it is we decrement that entry, add to our ans 4, decerment unmatched_same_letter, and move on
        // if it is not, we increment that entry and increment unmatched_same_letter
        // if it does not have the same letter twice,
        // we can reverse it and check if that is in the map already
        // if so, decrement it and increment ans by 4
        // if not, increment the original by 1 in the map.
        
        // at the end check if unmatched_same_letter greater than zero, if so
        // add 2 to answer. If odd or even words we can add this as each one is palindrome
        std::unordered_map<std::string, int> word_map;
        int unmatched_same_letters = 0;
        int answer = 0;
        for (std::string word : words)
        {
            if (word[0] == word[1])
            {
                if (word_map[word] > 0)
                {
                    word_map[word]--;
                    answer += 4;
                    unmatched_same_letters--;
                }
                else
                {
                    word_map[word]++;
                    unmatched_same_letters++;
                }
            }
            else
            {
                std::string string_rev = reverseString(word);
                if (word_map[string_rev] > 0)
                {
                    word_map[string_rev]--;
                    answer += 4;
                }
                else
                {
                    word_map[word]++;
                }
                
                
            }
        }
        
        if (unmatched_same_letters > 0)
        {
            answer += 2;
        }
        
        return answer;
        
    }
};
