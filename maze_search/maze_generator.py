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
import dash
from dash.dependencies import Output, Input
import dash_core_components as dcc
import dash_html_components as html
import plotly
import random
import plotly.graph_objs as go
from collections import deque

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
        self.builder_map = np.ones((map_size, map_size)) * np.inf
        self.map = np.ones((2 * map_size, 2 * map_size)) # Map is 2 times bigger to accommodate walls

        self.builder_map = np.pad(self.builder_map, 1, constant_values=self.wall)
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
            new_cell, direction = self.check_for_unvisited_neighbors(current_cell)
            if new_cell:
                self.builder_stack.append(current_cell)
                self.map[2 * new_cell[0], 2 * new_cell[1]] = self.free
                self.map[2 * current_cell[0] + direction[0], 2 * current_cell[1] + direction[1]] = self.free
                self.builder_map[new_cell[0], new_cell[1]] = self.free
                self.builder_stack.append(new_cell)

    def check_for_unvisited_neighbors(self, cell):
        assert(isinstance(cell, tuple))

        # search up, down, left, right of the cell and return the first unvisited cell
        neighbor_indices = np.array([[1, 0], # right
                                     [-1, 0], # left
                                     [0, 1], # up
                                     [0, -1]]) # down

        # permutation prevents biasing direction of expansion
        for i in np.random.permutation(neighbor_indices.shape[0]):
            neighbor_x = cell[0] + neighbor_indices[i, 0]
            neighbor_y = cell[1] + neighbor_indices[i, 1]
            if self.builder_map[neighbor_x, neighbor_y] == np.inf:
                return (neighbor_x, neighbor_y), (neighbor_indices[i, 0], neighbor_indices[i, 1])

        return None, None

    def visualize_map(self):
        fig = plt.figure()

        ax = plt.subplot(111)

        ax.imshow(self.map)

        plt.show()



if __name__ == "__main__":
    map_size = int(20)

    MazeGeneratorObj = MazeGenerator(map_size)
    MazeGeneratorObj.init_map()
    MazeGeneratorObj.create_map()
    MazeGeneratorObj.visualize_map()

