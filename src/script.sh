#!/bin/bash

#valgrind --tool=memcheck --leak-check=full ./tema3_neopt ../input/input_valgrind
#valgrind --tool=cachegrind --branch-sim=yes --cache-sim=yes ./tema3_neopt ../input/input_valgrind

#valgrind --tool=memcheck --leak-check=full ./tema3_blas ../input/input_valgrind
#valgrind --tool=cachegrind --branch-sim=yes --cache-sim=yes ./tema3_blas ../input/input_valgrind

#valgrind --tool=memcheck --leak-check=full ./tema3_opt_m ../input/input_valgrind
#valgrind --tool=cachegrind --branch-sim=yes --cache-sim=yes ./tema3_opt_m ../input/input_valgrind

# echo "Teste pentru neoptimizat"
# ./tema3_neopt ../input/input
# ./tema3_neopt ../input/input
# ./tema3_neopt ../input/input
# ./tema3_neopt ../input/input
# ./tema3_neopt ../input/input

# echo "Teste pentru blas"
# ./tema3_blas ../input/input
# ./tema3_blas ../input/input
# ./tema3_blas ../input/input
# ./tema3_blas ../input/input
# ./tema3_blas ../input/input

# echo "Teste pentru optimizat"
# ./tema3_opt_m ../input/input
# ./tema3_opt_m ../input/input
# ./tema3_opt_m ../input/input
# ./tema3_opt_m ../input/input
# ./tema3_opt_m ../input/input