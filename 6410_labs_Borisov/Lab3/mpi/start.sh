#!/bin/bash
#PBS -N Work_MPI 
#PBS -l walltime=00:01:10 
#PBS -l nodes=3:ppn=8 
#PBS -j oe 
#PBS -A tk 
cd $PBS_O_WORKDIR
cd /home/stud06/6410_labs_Borisov/Lab3/mpi/

module load impi/4
export I_MPI_DEVICE=rdma
export I_MPI_DEBUG=0
export I_MPI_FALLBACK_DEVICE=enable

mpirun -np 1 out/mpi_out
mpirun -np 16 out/mpi_out
mpirun -np 24 out/mpi_out
