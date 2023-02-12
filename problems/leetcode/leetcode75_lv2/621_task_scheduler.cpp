#include <queue>
#include <unordered_map>
#include <utility>

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        // we first use unordered map to count all of the entries per unique char.
        // we go through array once and populate map.

        // then we make a priority queue, which will keep pairs of int, char type.
        // this will have biggest at the top.

        // then we start looping over cycles, where a cycle is n loops.
        // for each cycle we grab the biggest and schedule it and so on.
        // we just have to handle cases where we exit early during cycle
        // and we have to put stuff back into priority queue if it has to be done further

        // time complexity
        // O(N) as we go through vector, a couple times, and use pq, logarithmic insert.
        // storage: O(N)

        std::unordered_map<char, int> task_counts;
        for (const char& c : tasks)
        {
            task_counts[c]++;
        }

        std::priority_queue<std::pair<int, char>> pq;
        for (std::pair<char, int> p : task_counts)
        {
            pq.push(std::make_pair(p.second, p.first));
        }

        int cycle = n + 1;
        int total_time = 0;

        while (!pq.empty())
        {
            std::vector<std::pair<int, char>> tmp;
            int time = 0;
            for (int i = 0; i < cycle; i++)
            {
                if (pq.size() > 0)
                {   
                    std::pair<int, char> p = pq.top();
                    pq.pop();
                    tmp.push_back(p);
                    time++;
                }
            }

            for (std::pair<int, char> p : tmp)
            {
                if (p.first > 1)
                {
                    p.first--;
                    pq.push(p);
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
    }
};
