'''
Author: Bryson Jones
Email: bkjones97@gmail.com

Description:
This file is used for the automatic generation of random mazes for
agents to be deployed, and search algorithms to be tested.
'''

import numpy as np
import json
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
SCALE_FACTOR = 2


class MazeGenerator:
    def __init__(self, map_size):
        assert(isinstance(map_size, int))
        self.map_size = map_size
        self.map = None
        self.starting_loc = None
        self.free = int(0)
        self.wall = int(1)

        self.builder_stack = []

    def init_map(self):

        # init all values to infinity to mark them as unvisited
        self.builder_map = np.ones((map_size, map_size)) * np.inf
        # Map is 2 times bigger to accommodate walls
        self.map = np.ones((SCALE_FACTOR * map_size, SCALE_FACTOR * map_size))

        self.builder_map = np.pad(self.builder_map, 1, constant_values=self.wall)
        self.map = np.pad(self.map, 1, constant_values=self.wall)

        self.builder_starting_loc = (np.random.randint(1, map_size-1),
                                    np.random.randint(1, map_size-1))

        self.starting_loc = self.builder_starting_loc * SCALE_FACTOR

        self.builder_goal_loc = (np.random.randint(1, map_size - 1),
                                 np.random.randint(1, map_size - 1))

        self.goal_loc = self.builder_goal_loc * SCALE_FACTOR

    def create_map(self):
        # use iterative maze generation algorithm
        # choose the initial cell, mark it as visited and push it to the stack
        current_cell = self.builder_starting_loc
        self.map[current_cell[0], current_cell[1]] = self.free
        self.builder_stack.append(self.builder_starting_loc)

        while self.builder_stack:
            # pop a cell from the stack and make it the current cell
            current_cell = self.builder_stack.pop()

            # if the current cell has any neighbors which have not been visited:
            new_cell, direction = self.check_for_unvisited_neighbors(current_cell)
            if new_cell:
                self.builder_stack.append(current_cell)
                self.map[SCALE_FACTOR * new_cell[0], SCALE_FACTOR * new_cell[1]] = self.free
                self.map[SCALE_FACTOR * current_cell[0] + direction[0], SCALE_FACTOR * current_cell[1] + direction[1]] = self.free
                self.builder_map[new_cell[0], new_cell[1]] = self.free
                self.builder_stack.append(new_cell)

        self.map[SCALE_FACTOR * self.goal_loc[0], SCALE_FACTOR * self.goal_loc[1]] = self.free

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

    def write_map(self, map_file_str):
        assert(isinstance(self.map, np.ndarray))
        map_file = open(map_file_str, "w+")

        map_file.write("map_size\n")
        map_file.write(str(self.map.shape[0]) + "," + str(self.map.shape[1]) + "\n")
        map_file.write("collision_threshold\n")
        map_file.write(str(1) + "\n")
        map_file.write("starting_pose\n")
        map_file.write(str(self.starting_loc[0]) + "," + str(self.starting_loc[1]) + "\n")
        map_file.write("goal_pose\n")
        map_file.write(str(self.goal_loc[0]) + "," + str(self.goal_loc[1]) + "\n")
        map_file.write("map\n")
        for i in range(self.map.size):
            map_file.write(str(int(self.map.ravel()[i])))
            if i != self.map.size-1:
                map_file.write(",")
        map_file.write("\r\n")

        # clean up resources
        map_file.close()


if __name__ == "__main__":
    map_size = int(20)
    output_file = "map1.txt"

    MazeGeneratorObj = MazeGenerator(map_size)
    MazeGeneratorObj.init_map()
    MazeGeneratorObj.create_map()
    MazeGeneratorObj.visualize_map()
    MazeGeneratorObj.write_map(output_file)

