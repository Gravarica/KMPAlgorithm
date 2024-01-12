#!/bin/bash

gcc ./programs/NaiveSearch.c -fopenmp -o ./programs/naive
gcc ./programs/KMP.c -o ./programs/kmp
gcc ./programs/KMP_OMP.c -fopenmp -o ./programs/kmpomp
mpicc ./programs/KMP_MPI.c -o ./programs/kmpmpi
