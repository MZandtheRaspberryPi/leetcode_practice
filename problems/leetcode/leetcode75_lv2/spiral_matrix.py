"""
Given an m x n matrix, return all elements of the matrix in spiral order.

 1 2 3
 4 5 6
 7 8 9
 
 out: list of 123698745
 
 m rows, n cols
 
 we could have four direction states
 right, down, left, up, in that order.
 each state has an end index, right is the col index.
 down is the row index, left is col index, up is row index.
 
 we go from one state to another.
 we will update the end index for right when we finish going right.
 update end index for down when finish going down.
 update end index for left when finish going left.
 update end index for up when finish going up.
 end becomes cur_end - 1 for right and down.
 end becomes cur_end + 1 for left or up.
 
 keep track of current index.
 if right, increment col. if down increment row. if left decrement col. if up, decrement row.

"""
from typing import List
from enum import Enum

class Direction(Enum):
    RIGHT = 0
    DOWN = 1
    LEFT = 2
    UP = 3

class TrafficDirector:
    def __init__(self, m: int, n: int, matrix: List[List[int]]):
        self.right_end = n - 1
        self.down_end = m - 1
        self.left_end = 0
        self.up_end = 1
        self.current_direction = Direction.RIGHT
        self.matrix = matrix
        self.current_row = 0
        self.current_col = 0
        
        self.m = m
        self.n = n
        
        self.output_array = []
        
    def __is_out_of_bounds(self) -> bool:
        if self.current_direction == Direction.RIGHT:
            return self.current_col > self.right_end
        elif self.current_direction == Direction.DOWN:
            return self.current_row > self.down_end
        elif self.current_direction == Direction.LEFT:
            return self.current_col < self.left_end
        else: # self.current_direction == Direction.UP:
            return self.current_row < self.up_end
    def move(self) -> bool:
        if self.__is_out_of_bounds():
            return False
        self.output_array.append(self.matrix[self.current_row][self.current_col])
        if self.current_direction == Direction.RIGHT:
            self.current_col += 1
            if self.__is_out_of_bounds():
                self.current_direction = Direction.DOWN
                self.current_row += 1
                self.current_col -= 1
                self.right_end -= 1
        elif self.current_direction == Direction.DOWN:
            self.current_row += 1
            if self.__is_out_of_bounds():
                self.current_direction = Direction.LEFT
                self.current_col -= 1
                self.current_row -= 1
                self.down_end -= 1
        elif self.current_direction == Direction.LEFT:
            self.current_col -= 1
            if self.__is_out_of_bounds():
                self.current_direction = Direction.UP
                self.current_row -= 1
                self.current_col += 1
                self.left_end += 1
        else: # self.current_direction == Direction.UP:
            self.current_row -= 1
            if self.__is_out_of_bounds():
                self.current_direction = Direction.RIGHT
                self.current_row += 1
                self.current_col += 1
                self.up_end += 1
        return True
        
    def get_output_array(self):
        return self.output_array

class Solution:
    def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
        traffic_director: TrafficDirector = TrafficDirector(len(matrix), len(matrix[0]), matrix)
        while traffic_director.move():
            continue
        return traffic_director.get_output_array()
        