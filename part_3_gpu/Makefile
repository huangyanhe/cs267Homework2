# Load CUDA using the following command
# module load cuda
#
CC = nvcc
CFLAGS = -O3 -arch=compute_37 -code=sm_37 -std=c++11
NVCCFLAGS = -O3 -arch=compute_37 -code=sm_37
LIBS = 

TARGETS = serial gpu autograder

all:	$(TARGETS)

serial: serial.o common_gsi.o
	$(CC) -o $@ $(LIBS) serial.o common_gsi.o
gpu: gpu.o common.o 
	$(CC) -o $@ $(NVCCLIBS) gpu.o common.o 
autograder: autograder.o common.o
	$(CC) -o $@ $(LIBS) autograder.o common.o

serial.o: serial.cu common_gsi.h
	$(CC) -c $(CFLAGS) serial.cu
common_gsi.o: common_gsi.cu common.h
	$(CC) -c $(CFLAGS) common_gsi.cu
autograder.o: autograder.cu common.h
	$(CC) -c $(CFLAGS) autograder.cu
gpu.o: gpu.cu common.h
	$(CC) -c $(NVCCFLAGS) gpu.cu
common.o: common.cu common.h
	$(CC) -c $(CFLAGS) common.cu

clean:
	rm -f *.o $(TARGETS) *.stdout *.txt *.error
