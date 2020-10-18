#!/bin/bash
#PBS -N pp_lab_1 
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

mpirun -r ssh -machinefile $PBS_NODEFILE -np 1 ./mpi.out > mpi_result_1.txt
mpirun -r ssh -machinefile $PBS_NODEFILE -np 16 ./mpi.out > mpi_result_16.txt
mpirun -r ssh -machinefile $PBS_NODEFILE -np 24 ./mpi.out > mpi_result_24.txt
