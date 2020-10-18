#!/bin/bash
#PBS -N hello_OpenMP_24T
#PBS -l walltime=00:01:10
#PBS -l nodes=3:ppn=8
#PBS -j oe
#PBS -A tk
cd $PBS_O_WORKDIR

module load intel/icc16
./test_omp
