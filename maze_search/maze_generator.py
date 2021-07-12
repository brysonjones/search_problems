'''
Author: Bryson Jones
Email: bkjones97@gmail.com

Description:
This file is used for the automatic generation of random mazes for
agents to be deployed, and search algorithms to be tested.
'''

import numpy as np
import random
import matplotlib.pyplot as plt

"""
MazeGenerator Class:
    - Inputs:
        - map_size (int) - 
    
"""
class MazeGenerator:
    def __init__(self, map_size):
        assert(isinstance(map_size, int))
        self.map_size = map_size
        self.map = None
        self.starting_loc = None
        self.free = 0
        self.wall = 1

        self.builder_stack = []

    def init_map(self):

        # init all values to infinity to mark them as unvisited
        self.map = np.ones((map_size, map_size)) * np.inf

        self.map = np.pad(self.map, 1, constant_values=self.wall)

        self.starting_loc = (np.random.randint(1, map_size-1),
                             np.random.randint(1, map_size-1))

    def create_map(self):
        # use iterative maze generation algorithm
        # choose the initial cell, mark it as visited and push it to the stack
        current_cell = self.starting_loc
        self.map[current_cell[0], current_cell[1]] = self.free
        self.builder_stack.append(self.starting_loc)

        while self.builder_stack:
            # pop a cell from the stack and make it the current cell
            current_cell = self.builder_stack.pop()

            # if the current cell has any neighbors which have not been visited:
            if self.check_for_unvisited_neighbors(current_cell):
                pass

    def check_for_unvisited_neighbors(self, cell):
        assert(isinstance(cell, tuple))

        # search up, down, left, right of the cell and return the first unvisited cell
        neighbor_indices = np.array([[1, 0], # right
                                     [-1, 0], # left
                                     [0, 1], # up
                                     [0, -1]]) # down


        for i in range(neighbor_indices.shape[0]):
            neighbor_x = cell[0] + neighbor_indices[i, 0]
            neighbor_y = cell[1] + neighbor_indices[i, 1]
            if self.map[neighbor_x, neighbor_y] == np.inf:
                return neighbor_x, neighbor_y

        return None


    def visualize_map(self):
        pass


if __name__ == "__main__":
    map_size = int(500)

    MazeGeneratorObj = MazeGenerator(map_size)
    MazeGeneratorObj.init_map()
    MazeGeneratorObj.create_map()


