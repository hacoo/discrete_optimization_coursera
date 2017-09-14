#! /usr/bin/python
# -*- coding: utf-8 -*-

from ctypes import *

anyint = cdll.LoadLibrary("cpp/build/libanyint_lib.so")


def solve_it(input_data):
    # return a positive integer, as a string
    return anyint.get_int() + 7

if __name__ == '__main__':
    print('This script submits the integer: %s\n' % solve_it(''))

    
