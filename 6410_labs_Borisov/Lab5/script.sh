#!/bin/bash
#PBS -l feature=gpu
#PBS -N matMulGPU_DiBoS
#PBS -l walltime=00:03:00
#PBS -l nodes=1:ppn=1:gpu
#PBS -j oe
#PBS -A tk
cd $PBS_O_WORKDIR
cd /home/stud06/6410_labs_Borisov/Lab5

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/COMMON/cuda-6.5/lib64
./mmul 32
