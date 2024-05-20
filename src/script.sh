#!/bin/bash

# echo "Teste pentru neoptimizat"
# ./tema3_neopt ../input/input
# ./tema3_neopt ../input/input
# ./tema3_neopt ../input/input
# ./tema3_neopt ../input/input
# ./tema3_neopt ../input/input
# valgrind --tool=memcheck --leak-check=full ./tema3_neopt ../input/input_valgrind
# valgrind --tool=cachegrind --branch-sim=yes --cache-sim=yes ./tema3_neopt ../input/input_valgrind

# echo "Teste pentru blas"
# ./tema3_blas ../input/input
# ./tema3_blas ../input/input
# ./tema3_blas ../input/input
# ./tema3_blas ../input/input
# ./tema3_blas ../input/input
# valgrind --tool=memcheck --leak-check=full ./tema3_blas ../input/input_valgrind
# valgrind --tool=cachegrind --branch-sim=yes --cache-sim=yes ./tema3_blas ../input/input_valgrind


echo "Teste pentru optimizat"
./tema3_opt_m ../input/input
./tema3_opt_m ../input/input
./tema3_opt_m ../input/input
./tema3_opt_m ../input/input
./tema3_opt_m ../input/input

valgrind --tool=memcheck --leak-check=full ./tema3_opt_m ../input/input_valgrind
valgrind --tool=cachegrind --branch-sim=yes --cache-sim=yes ./tema3_opt_m ../input/input_valgrind

echo "Verificare rezultate"
./compare out1 ../reference/out1
./compare out2 ../reference/out2
./compare out3 ../reference/out3