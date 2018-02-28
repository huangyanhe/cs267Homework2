#
# Edison - NERSC 
#
# Intel Compilers are loaded by default; for other compilers please check the module list
#
CC = CC
MPCC = CC
OPENMP = -fopenmp #Note: this is the flag for Intel compilers. Change this to -fopenmp for GNU compilers. See http://www.nersc.gov/users/computational-systems/edison/programming/using-openmp/
CFLAGS = -O3
LIBS =


TARGETS = serial openmp mpi autograder

all:	$(TARGETS)

serial: serial.o common.o decomposition.o
	$(CC) -o $@ $(LIBS) serial.o common.o decomposition.o
autograder: autograder.o common.o
	$(CC) -o $@ $(LIBS) autograder.o common.o
openmp: openmp.o common.o decomposition.o
	$(CC) -o $@ $(LIBS) $(OPENMP) openmp.o common.o decomposition.o
mpi: mpi.o common.o decomposition_mpi.o
	$(MPCC) -o $@ $(LIBS) $(MPILIBS) mpi.o common.o decomposition_mpi.o
	sbatch job-cori-mpi32

autograder.o: autograder.cpp common.h
	$(CC) -c $(CFLAGS) autograder.cpp
openmp.o: openmp.cpp common.h
	$(CC) -c $(OPENMP) $(CFLAGS) openmp.cpp -o openmp.o
serial.o: serial.cpp common.h
	$(CC) -c $(CFLAGS) serial.cpp
mpi.o: mpi.cpp common.h
	$(MPCC) -c $(CFLAGS) mpi.cpp
common.o: common.cpp common.h
	$(CC) -c $(CFLAGS) common.cpp
decomposition.o: decomposition.cpp decomposition.h
	$(CC) -c $(CFLAGS) decomposition.cpp
decomposition_mpi.o: decomposition_mpi.cpp decomposition_mpi.h
	$(CC) -c $(CFLAGS) decomposition_mpi.cpp

clean:
	rm -f *.o $(TARGETS) *.stdout *.txt *.error
