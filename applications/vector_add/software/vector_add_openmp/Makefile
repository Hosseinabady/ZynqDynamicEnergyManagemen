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

OBJ-SERIAL  = vector_add_serial.o
OBJ-OPENMP = vector_add_openmp.o
OBJ-OPENMP-NEON = vector_add_openmp_neon.o

EXE-SERIAL  = vector_add_serial.exe
EXE-OPENMP = vector_add_openmp.exe
EXE-OPENMP-NEON = vector_add_openmp_neon.exe

NEON-FLAG = -O3 -mcpu=cortex-a9 -mfpu=neon-fp16 -ftree-vectorize -mvectorize-with-neon-quad -mfloat-abi=hard -ffast-math


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
	@echo "   $(EXE-OPENMP-NEON) - OpenMP version in C"	
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


$(EXE-SERIAL): $(OBJ-SERIAL)
	$(CC)  -o $(EXE-SERIAL) $(OBJ-SERIAL) $(LDFLAGS)
	
$(EXE-OPENMP): $(OBJ-OPENMP)
	$(CC)  -o $(EXE-OPENMP) $(OBJ-OPENMP) $(LDFLAGS) $(C_OMP)
	
$(EXE-OPENMP-NEON): $(OBJ-OPENMP-NEON)
	$(CC)  -o $(EXE-OPENMP-NEON) $(OBJ-OPENMP-NEON) $(LDFLAGS) $(C_OMP)

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


vector_add_serial.o: vector_add_serial.c
	$(CC)  -c  $(CFLAGS) $*.c 

vector_add_openmp.o:vector_add_openmp.c 
	$(CC)  -c $(CFLAGS) $(C_OMP) $*.c 

vector_add_openmp_neon.o:vector_add_openmp_neon.c 
	$(CC)  -c  $(CFLAGS) $(NEON-FLAG) $(C_OMP)  $*.c 

clean:
	@/bin/rm -f $(OBJ-SERIAL)  $(EXE-SERIAL)
	@/bin/rm -f $(OBJ-OPENMP) $(EXE-OPENMP)
	@/bin/rm -f $(OBJ-OPENMP-NEON) $(EXE-OPENMP-NEON)

