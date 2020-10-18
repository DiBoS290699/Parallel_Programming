#!/bin/bash
#PBS -N hello_MPI_24T
#PBS -l walltime=00:01:10
#PBS -l nodes=3:ppn=8
#PBS -j oe
#PBS -A tk
cd $PBS_O_WORKDIR

module load impi/4
export I_MPI_DEVICE=rdma
export I_MPI_DEBUG=0
export I_MPI_FALLBACK_DEVICE=disable
mpirun -r ssh -machinefile $PBS_NODEFILE -np $PBS_NP ./test_mpi
