#!/bin/bash
#PBS -N Work_OPENMP
#PBS -l walltime=00:01:10
#PBS -j oe
#PBS -A tk
cd $PBS_O_WORKDIR
cd /home/stud06/6410_labs_Borisov/Lab2/openmp

module load intel/icc16
./openmp_reduction_out 1
./openmp_reduction_out 16
./openmp_reduction_out 24
./openmp_critical_out 1
./openmp_critical_out 16
./openmp_critical_out 24
./openmp_atomic_out 1
./openmp_atomic_out 16
./openmp_atomic_out 24
