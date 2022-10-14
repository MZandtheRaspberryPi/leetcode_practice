#include <queue>
#include <unordered_map>
#include <utility>

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        // could make a vector of ints, size 26, 0
        // loop through the array and add to vector at index char - 'A' + 1
        // then make time counter, set to 0
        // then make a new vector, of chars
        // make a copy of vector of ints
        // make bool changed_elements set to true
        // while changed_elements
        // loop over int list, find max
        // put that character into array first
        // set changeD_elements to true, break
        // set changed_elements to false
        
        // now we can loop through and count time
        // we want to iterate over our options, and if enough time has passed since most popular option
        // go back and schedule that next
        // loop over list, 
        // while map is not empty
        // loop over map,
        // if last_processed_time[task] < 2, continue
        // else if cur_task != map.begin() and map.begin(), and its count is bigger than curr count, the biggest task, if thats counter is >= 2, break
        // else set map[task] --, and its counter to 0
        // then set time counter ++.
        
        // time complexity, O(N), though visit each task around 3 times
        // storage complexity O(N), store 2 maps of each unique task
        
        // but, optimal way, use priority queue with pairs in it of int and chars
        // so first, make unordered map of char int, where we add 1 for each task in vector
        // then, make priority queue of type pair<int, char>, and add each entry in unordered map
        // make total time counter = 0
        // make cycle = n + 1
        // while pq not empty
        // make tmp vector of tasks, pair<int, char>
        // set time = 0
        // loop over cycle, i = 0 < cycle
        // push tmp back by pair
        // pop pq top
        // time ++
        // 
        // then come and decrement pair and put back into pq if greater than 0
        // if pq is empty add time to alltime
        // else add cycle
        // time complexity, O(N). Gotta visit each task, a couple times tho
        // storage complexity, O(N), storing each unique task, a couple times.
        
        std::unordered_map<char, int> task_counts;
        for (const char& task : tasks)
        {
            task_counts[task]++;
        }
        
        std::priority_queue<std::pair<int, char>> pq;
        for (std::pair<char, int> task : task_counts)
        {
            pq.push(std::make_pair(task.second, task.first));
        }
        
        int cycle = n + 1;
        int total_time = 0;
        
        while (!pq.empty())
        {
            int time = 0;
            std::vector<std::pair<int, char>> tmp;
            for (int i = 0; i < cycle; i++)
            { 
              if (!pq.empty())
              {
                tmp.push_back(pq.top());
                pq.pop();
                time++;
              }
            }
            
            for (std::pair<int, char> task : tmp)
            {
                if (task.first > 1)
                {
                    task.first--;
                    pq.push(task);
                }
            }
            
            if (pq.empty())
            {
                total_time += time;
            }
            else
            {
                total_time += cycle;
            }
        }
        
        return total_time;
        
    return 0;
    }
};
