#!/usr/bin/python
#-*- coding:utf-8 -*-

# Each executable that wants to output performance information must
# output it to a file containing an array of JSON objects of the form:
# { "name": "a description of the test",
#   "size": for instance number of elements, or size of the matrix
#   "nProcs": number of processors
#   "time": time in seconds in decimal form
# }
#
# This script must be called with fisrt argument being the key for X-axix
# (either 'size' or 'nProcs') second being Y-axis (either time or throughput)
# and some files containing properly formatted JSON

import json
import matplotlib.pyplot as plt
import sys


class Test:
    def __init__(self, keyX, keyY, measures, color, name):
        self.keyX = keyX
        self.keyY = keyY
        self.measures = measures
        self.color = color
        self.name = name



colors = ['blue', 'green', 'red', 'cyan', 'magenta', 'yellow', 'black', '0.75', '#FF5100', '#780000',
          '#005078']

# get file names and criteria for X-axix
if len(sys.argv) < 4:
    print("Usage: %s [size|nProcs] [time|throughput] file [file...]" % sys.argv[0])
    exit(1)

keyX = sys.argv[1]
keyY = sys.argv[2]
filenames = sys.argv[3:]


# Get all the data in one big dict
data = []
for fname in filenames:
    d = json.load(open(fname))
    data += d


# Partition in different tests based on their name
tests = []
test_names = list(set( [ e['name'] for e in data ] ))
for i, name in enumerate(test_names):
    tests_for_name = [e for e in data if e['name'] == name]
    tests.append(Test(keyX, keyY, tests_for_name, colors[i], name))


# For each test, average the Y-values for the same X-value
for t in tests:
    # Get all different X values
    Xvalues = list(set([e[t.keyX] for e in t.measures]))
    Xvalues.sort()

    mean_values = []
    for v in Xvalues:
        print("x value: %d" % v)
        Yvalues = [e[t.keyY] for e in t.measures if e[t.keyX] == v]
        meanY = sum(Yvalues) / len(Yvalues)
        mean_values.append({t.keyX: v, t.keyY: meanY})

    t.measures = mean_values


# Now we can plot every test
for t in tests:
    #t.measures.sort(key = lambda e: e[t.keyX])
    n_items_or_procs = [ e[t.keyX] for e in t.measures ]
    times_or_throughputs = [ e[t.keyY] for e in t.measures ]

    plt.plot(n_items_or_procs, times_or_throughputs,
             color = t.color, linestyle='-', marker='o',
             linewidth=2, label=t.name)

# start from 0, 0, hack.
plt.plot([0], [0], color = 'white')


if keyX == "size":
    plt.xlabel("Number of pixels")
else:
    plt.xlabel("Number of execution cores")

if keyY == "time":
    plt.ylabel("Execution time in seconds")
else:
    plt.ylabel("Throughput in pixels by second")

plt.legend(loc='best', prop={'size':12})
plt.show()
