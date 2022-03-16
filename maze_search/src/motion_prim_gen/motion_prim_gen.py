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
    output_file = "motion_prim.json"

    fig = plt.figure()
    ax = plt.subplot(111)

    start_angle = 0
    num_segments = 20

    # discretize kappa into range to generate correct number of primitives
    disc_kappa = np.linspace(-kappa, kappa, num_prims)

    mprim_blob = json.loads('{}')
    mprim_list = []
    for i, kappa_i in enumerate(disc_kappa):
        tmp_dict = {}
        if kappa_i != 0:
            radius = 1 / kappa_i
            end_angle = arc_length / radius
        else:
            x = np.zeros(num_segments)
            y = np.linspace(0, arc_length, num_segments)
            theta = np.zeros(num_segments)
            ax.plot(x, y)
            tmp_dict["x"] = x.tolist()
            tmp_dict["y"] = y.tolist()
            tmp_dict["theta"] = theta.tolist()
            mprim_list.append(tmp_dict)
            continue

        # The coordinates of the arc
        theta = np.linspace(start_angle, end_angle, num_segments)
        x = radius * np.cos(theta) - radius
        y = radius * np.sin(theta)
        tmp_dict["x"] = x.tolist()
        tmp_dict["y"] = y.tolist()
        tmp_dict["theta"] = theta.tolist()
        mprim_list.append(tmp_dict)

        ax.plot(x, y)

    mprim_blob["mprims"] = mprim_list
    ax.set(xlim=[-50, 50], ylim=[0, 50])

    # Save json blob
    mprim_str = json.dumps(mprim_blob)
    with open(output_file, 'w') as outfile:
        outfile.write(mprim_str)

    plt.show()
    print(mprim_str)

if __name__ == "__main__":

    gen_ackermann(num_prims=3, arc_length=50, kappa=0.02)
