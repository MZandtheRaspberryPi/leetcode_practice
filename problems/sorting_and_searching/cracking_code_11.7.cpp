/*

A circus desiging touwer routine for people atop one another. each person must be shorter and lighter than person below him/her. given height and waitghts,
write method to compute largets possible num people in tower.

input:
(ht, wt): (65, 100) (70, 50), (56, 90)....ect.

output
(56, 90) (65, 100)

idea: need to sort array a couple times and toss out a different problematic one each time till we get the max.

first sort by heights.
then look at weights. 
problem is that we arent guaranteed perfect solution.

five approaches
exemplify - write out examples and derive general rule from there

pattern matching - consider what problems algo is similar to and try and modify solutions to those.

simplify and generalize. change constraint, solve simpler.

base case and build. solve first for base case, like n = 1, then go on.

data structures

// problematic case is when one person has lower height, but heigher height than another. then gotta drop one.
// or vice versa.
// perhaps we drop the one with the biggest difference between height and weight?
// 
// we would want to drop the one with the higher problem value.
// this gives us the best chance to match others.
// 

// so, stupid way, sort by heights first

// first sort by height.
// then go through and try and build longest sub array from weight. Do this by iterating through array and picking that as the last value, and then look at stuff
// before and count how high can go.

// 



*/
#include<algorithm>
#include<stdio.h>
#include<vector>

struct Person
{
    int weight;
    int height;
};

typedef std::vector<Person> Circus;

void printCircus(const Circus& circus)
{
  for (int i = 0; i < circus.size(); i++)
  {
    printf("%d %d, ", circus[i].height, circus[i].weight);
  }
  printf("\n");
}

bool personSmallerHeight(const Person& a, const Person& b)
{
  return a.height < b.height;
}

Circus findLargetIncreasingSubsequence(const Circus& circus)
{
    int max_sequence_index = 0;
    int max_sequence_length = 1;
    for (int i = 1; i < circus.size(); i++)
    {
        int current_sequence_length = 1;
        int j = i - 1;
        while (j >= 0 && j < i)
        {
            if (circus[j].weight <= circus[j + 1].weight)
            {
                current_sequence_length += 1;
                if (current_sequence_length > max_sequence_length)
                {
                    max_sequence_index = i;
                    max_sequence_length = current_sequence_length;
                }
                j--;
            }
            else
            {
                break;
            }
        }
    }

    Circus circus_largest_ladder;
    for (int i = max_sequence_index - max_sequence_length + 1; i <= max_sequence_index; i++)
    {
        circus_largest_ladder.push_back(circus[i]);
    }
    return circus_largest_ladder;
}

Circus getIncreasingSubsequence(const Circus& circus)
{
    Circus circus_subset = circus;
    std::sort(circus_subset.begin(), circus_subset.end(), personSmallerHeight);
    circus_subset = findLargetIncreasingSubsequence(circus_subset);
    return circus_subset;
}

int main()
{

  Person cloun;
  Person juggler;
  Person opera_singer;
  Person acrobat;
  cloun.height = 100;
  cloun.weight = 123;
  opera_singer.height = 80;
  opera_singer.weight = 140;
  juggler.height = 110;
  juggler.weight = 140;
  acrobat.height = 80;
  acrobat.weight = 90;

  Circus circus;
  circus.push_back(cloun);
  circus.push_back(opera_singer);
  circus.push_back(juggler);
  circus.push_back(acrobat);
  printCircus(circus);

  Circus circus_subset = getIncreasingSubsequence(circus);
  printCircus(circus_subset);


}