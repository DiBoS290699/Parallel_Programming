#!/bin/bash
#PBS -N Work_MPI 
#PBS -l walltime=00:01:10 
#PBS -l nodes=3:ppn=8 
#PBS -j oe 
#PBS -A tk 
cd $PBS_O_WORKDIR
cd /home/stud06/6410_labs_Borisov/Lab2/mpi/

module load impi/4
export I_MPI_DEVICE=rdma
export I_MPI_DEBUG=0
export I_MPI_FALLBACK_DEVICE=disable

touch result_mpi_p2p_1.txt
touch result_mpi_broadcast_1.txt

touch result_mpi_p2p_16.txt
touch result_mpi_broadcast_16.txt

touch result_mpi_p2p_24.txt
touch result_mpi_broadcast_24.txt

for i in {1..10}; do mpirun -np 1 out/mpi_p2p_out; done > result_mpi_p2p_1.txt
for i in {1..10}; do mpirun -np 1 out/mpi_broadcast_out ; done > result_mpi_broadcast_1.txt

for i in {1..10}; do mpirun -np 16 out/mpi_p2p_out; done > result_mpi_p2p_16.txt
for i in {1..10}; do mpirun -np 16 out/mpi_broadcast_out; done > result_mpi_broadcast_16.txt

for i in {1..10}; do mpirun -np 24 out/mpi_p2p_out; done > result_mpi_p2p_24.txt
for i in {1..10}; do mpirun -np 24 out/mpi_broadcast_out; done > result_mpi_broadcast_24.txt

