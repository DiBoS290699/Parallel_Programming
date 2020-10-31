#!/bin/bash
#PBS -l feature=gpu
#PBS -N Work_OPENMP
#PBS -j oe
#PBS -A tk
cd $PBS_O_WORKDIR
cd /home/stud06/6410_labs_Borisov/Lab3/openmp

module load intel/icc16
./out/openmp_dynamic_out 1
./out/openmp_dynamic_out 16
./out/openmp_dynamic_out 24
./out/openmp_static_out 1
./out/openmp_static_out 16
./out/openmp_static_out 24
./out/openmp_guided_out 1
./out/openmp_guided_out 16
./out/openmp_guided_out 24
