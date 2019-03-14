#!/usr/bin/env python
# -*- coding: utf-8 -*-
import numpy as np
import sys


max = sys.maxsize
min = -sys.maxsize -1

# min_value, max_value = 999, -999

with open("testfile.txt") as file:
    for numbers in file:

        numbers = float(numbers.rstrip())
        if min > numbers:
            min_value = numbers
        if max < numbers:
            max_value = numbers
    print 'min:', min_value
    print 'max:', max_value
