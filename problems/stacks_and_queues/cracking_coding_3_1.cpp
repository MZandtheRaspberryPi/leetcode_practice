/*
describe how could use single array
to implement 3 stacks

allocate fixed size for array up front.use 3rd for each stack.

so define constant for array aize and num stacks. calculate start and end indices for each, [0, n/3), [n/3 2n/3). struct for current index and start/stoo of each stack.

other way to do it is to dynamically resize available portion, and potentially even wrap around if needed.
*/

#include <stdio.h>
#include <vector>

struct StackIndices
{
  int start_index;
  int end_index;
  int current_index;
};

struct StackData
{
    int data;
    bool in_use;
};

class ArrayOfThreeStacks
{
public:
  ArrayOfThreeStacks();
  int pop(int stack_index);
  int front(int stack_index);
  int push(int stack_index, int data);

private:
  const int array_size_ = 5000;
  const int num_stacks_ = 3;
  std::vector<StackData> stack_data_;
  std::vector<StackIndices> stack_indices_;
};

ArrayOfThreeStacks::ArrayOfThreeStacks()
{
  StackData default_data{0, false};
  stack_data_ = std::vector<StackData>(array_size_, default_data);
  stack_indices_.resize(num_stacks_);
  for (int i = 0; i < num_stacks_; i++)
  {
    int start = (i * array_size_ / 3);
    int end = (i+1)*array_size_/3;
    StackIndices indices = StackIndices{ start, end, 0 };
    stack_indices_[i] = indices;
  }
}

int ArrayOfThreeStacks::pop(int stack_index)
{
  StackIndices& indices = stack_indices_[stack_index];
  int& current = indices.current_index;
  if (!(stack_data_[current].in_use))
  {
    return -1;
  }
  stack_data_[current].in_use = false;
  current = current <= indices.start_index ? indices.start_index : current - 1;
  return 0;
}

int ArrayOfThreeStacks::front(int stack_index)
{
  StackIndices& indices = stack_indices_[stack_index];
  if (!(stack_data_[indices.current_index].in_use))
  {
    return -1;
  }
  return stack_data_[indices.current_index].data;
}

int ArrayOfThreeStacks::push(int stack_index, int data)
{
  if (!(stack_index < num_stacks_))
  {
    return -1;
  }
  StackIndices& indices = stack_indices_[stack_index];
  if (indices.current_index < indices.end_index - 1)
  {
    indices.current_index++;
    stack_data_[indices.current_index].data = data;
    stack_data_[indices.current_index].in_use = true;
    return 0;
  }
  else
  {
    return -1;
  }
}

int main()
{
  ArrayOfThreeStacks stack_arr = ArrayOfThreeStacks();
  stack_arr.push(0, 4);
  stack_arr.push(0, 3);
  printf("0: %d\n", stack_arr.front(0));
  stack_arr.pop(0);
  printf("0: %d\n", stack_arr.front(0));
  stack_arr.push(2, 5);
  printf("2: %d\n", stack_arr.front(2));
  

}