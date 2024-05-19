#!/bin/bash

valgrind --tool=memcheck --leak-check=full ./tema3_opt_m ../input/input
