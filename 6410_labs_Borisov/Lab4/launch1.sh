#!/bin/bash
#PBS -N matMulGPU_DiBoS
#PBS -l nodes=1:ppn=1:gpu
#PBS -j oe
#PBS -A tk
cd $PBS_O_WORKDIR
cd /home/stud06/6410_labs_Borisov/Lab4

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/COMMON/cuda-6.5/lib64

touch result_CUDA_2048.txt
touch result_CUDA_4096.txt
touch result_CUDA_8192.txt
touch result_single_thread_2048.txt
touch result_single_thread_4096.txt
touch result_single_thread_8192.txt

module load cuda/6.5
module load intel/icc16

for i in {1..12}; do ./Add 2048; done > result_CUDA_2048.txt
for i in {1..12}; do ./Add 4096; done > result_CUDA_4096.txt
for i in {1..12}; do ./Add 8192; done > result_CUDA_8192.txt

./single_thread.out 2048 > result_single_thread_2048.txt
./single_thread.out 4096 > result_single_thread_4096.txt
./single_thread.out 8192 > result_single_thread_8192.txt
