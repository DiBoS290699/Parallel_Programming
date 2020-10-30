module load intel/icc16
icc -qopenmp -o out/openmp_static_out openmp_static.cpp
icc -qopenmp -o out/openmp_dynamic_out openmp_dynamic.cpp
icc -qopenmp -o out/openmp_guided_out openmp_guided.cpp
