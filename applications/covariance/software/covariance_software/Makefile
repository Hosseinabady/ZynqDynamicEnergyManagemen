#----------------------------------------------------
# This is the make file for the example programs
# in Chapter 3 of the book 'Using OpenMP'
#----------------------------------------------------



include gnu-compilers.h

#-----------------------------------------------------------------------
# Make file for the source examples given in Chapter 3 of the book
# "Using OpenMP"
#-----------------------------------------------------------------------

.IGNORE:

.SUFFIXES: .f90 .c .o 


NTHREADS = 2

OBJ-SERIAL  = covariance_serial.o 
OBJ-OPENMP = covariance_openmp.o 
OBJ-OPENMP-NEON = covariance_openmp_neon.o

EXE-SERIAL  = covariance_serial.exe
EXE-OPENMP = covariance_openmp.exe
EXE-OPENMP-NEON = covariance_openmp_neon.exe

NEON-FLAG = -O3 -mcpu=cortex-a9 -mfpu=neon -ftree-vectorize -mvectorize-with-neon-quad -mfloat-abi=hard -ffast-math


help:
	@echo "Command to build all example programs:"
	@echo "    make build"
	@echo
	@echo Command to run all example programs:
	@echo "    make run"
	@echo
	@echo "Targets to build individual examples:"
	@echo "   $(EXE-SERIAL)  - Sequential version of MXV in C"
	@echo "   $(EXE-OPENMP) - OpenMP version in C"
	@echo
	@echo "Targets to run individual examples:"
	@echo "    run-$(EXE-SERIAL)"
	@echo "    run-$(EXE-OPENMP)"
	@echo "    run-$(EXE-OPENMP-NEON)"
	@echo 
	@echo "Command to remove all objects and executables:"
	@echo "    make clean"

build: $(EXE-SERIAL)  \
       $(EXE-OPENMP)  \
       $(EXE-OPENMP-NEON)
 


run: run-$(EXE-SERIAL)  \
     run-$(EXE-OPENMP)  \
     run-$(EXE-OPENMP-NEON) 


$(EXE-SERIAL): $(OBJ-SERIAL) polybench.o
	$(CC)  -o $(EXE-SERIAL) $(OBJ-SERIAL) polybench.o $(LDFLAGS) -lm
$(EXE-OPENMP): $(OBJ-OPENMP) polybench.o
	$(CC)  -o $(EXE-OPENMP) $(OBJ-OPENMP) polybench.o $(LDFLAGS) $(C_OMP) -lm

$(EXE-OPENMP-NEON): $(OBJ-OPENMP-NEON) polybench.o
	$(CC)  -o $(EXE-OPENMP-NEON) $(OBJ-OPENMP-NEON) polybench.o $(LDFLAGS) $(C_OMP) -lm


run-$(EXE-SERIAL):
	@(OMP_NUM_THREADS=1; export OMP_NUM_THREADS;\
	  ./$(EXE-SERIAL) ;\
	  )


run-$(EXE-OPENMP):
	@(OMP_NUM_THREADS=$(NTHREADS); export OMP_NUM_THREADS;\
	  ./$(EXE-OPENMP) ;\
	  )

run-$(EXE-OPENMP-NEON):
	@(OMP_NUM_THREADS=$(NTHREADS); export OMP_NUM_THREADS;\
	  ./$(EXE-OPENMP-NEON) ;\
	  )

covariance_serial.o: covariance_serial.c polybench.c
	$(CC) -c $(CFLAGS) $*.c polybench.c -lm

covariance_openmp_neon.o:covariance_openmp_neon.c polybench.c
	$(CC) -c  $(CFLAGS) $(NEON-FLAG) $(C_OMP) -lm $*.c 

covariance_openmp.o:covariance_openmp.c polybench.c
	$(CC) -c $(CFLAGS) $(C_OMP) $*.c -lm


polybench.o:polybench.c
	$(CC) -c $(CFLAGS) $(C_OMP) $*.c -lm

clean:
	@/bin/rm -f $(OBJ-SERIAL)  $(EXE-SERIAL) $(OBJ-OPENMP-NEON)
	@/bin/rm -f $(OBJ-OPENMP) $(EXE-OPENMP)  $(EXE-OPENMP-NEON)


