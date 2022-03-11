'''
Author: Bryson Jones
Email: bkjones97@gmail.com

Description:
This file is used to generate motion primitives for robot systems
with non-holonomic constraints
'''

import numpy as np
import csv
import json
import random
import matplotlib.pyplot as plt
import plotly
import random
import plotly.graph_objs as go

'''
Generate motion primitives for an ackermann vehicle
inputs:
    arc_length:
    kappa: curvature
'''
def gen_ackermann(num_prims, arc_length, kappa):
    output_file = "motion_prim.csv"

    fig = plt.figure()
    ax = plt.subplot(111)

    start_angle = 0
    num_segments = 20

    # discretize kappa into range to generate correct number of primitives
    disc_kappa = np.linspace(-kappa, kappa, num_prims)
    with open(output_file, 'w', newline='\n') as f:
        writer = csv.writer(f)
        for i, kappa_i in enumerate(disc_kappa):
            writer.writerow(["motion primitive: " + str(i)])
            if kappa_i != 0:
                radius = 1 / kappa_i
                end_angle = arc_length / radius
            else:
                x = np.zeros(num_segments)
                y = np.linspace(0, arc_length, num_segments)
                ax.plot(x, y)
                writer.writerow("x")
                writer.writerow(x)
                writer.writerow("y")
                writer.writerow(y)
                continue

            # The coordinates of the arc
            theta = np.linspace(start_angle, end_angle, num_segments)
            x = radius * np.cos(theta) - radius
            y = radius * np.sin(theta)
            writer.writerow("x")
            writer.writerow(x)
            writer.writerow("y")
            writer.writerow(y)

            ax.plot(x, y)

    ax.set(xlim=[-50, 50], ylim=[0, 50])

    # plt.show()

if __name__ == "__main__":

    gen_ackermann(num_prims=3, arc_length=50, kappa=0.02)
