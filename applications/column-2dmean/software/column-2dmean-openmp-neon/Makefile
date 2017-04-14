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

OBJ-COLUMN-2DMEAN-SERIAL      = column-2dmean-serial.o
OBJ-COLUMN-2DMEAN-OMP         = column-2dmean-omp.o
OBJ-COLUMN-2DMEAN-OMP-NEON    = column-2dmean-omp-neon.o

EXE-COLUMN-2DMEAN-SERIAL      = column-2dmean-serial.exe
EXE-COLUMN-2DMEAN-OMP         = column-2dmean-omp.exe
EXE-COLUMN-2DMEAN-OMP-NEON    = column-2dmean-omp-neon.exe


NEON-FLAG = -O3 -mcpu=cortex-a9 -mfpu=neon-fp16 -ftree-vectorize -mvectorize-with-neon-quad -mfloat-abi=hard -ffast-math

help:
	@echo "Command to build all example programs:"
	@echo "    make build"
	@echo
	@echo Command to run all example programs:
	@echo "    make run"
	@echo
	@echo "Targets to build individual examples:"
	@echo "   $(EXE-COLUMN-2DMEAN-SERIAL)  - Sequential version of MXV in C"
	@echo "   $(EXE-COLUMN-2DMEAN-OMP) - OpenMP version in C"
	@echo "   $(EXE-EXE-COLUMN-2DMEAN-OMP-NEON) - OpenMP version in C"
	@echo
	@echo "Targets to run individual examples:"
	@echo "    run-$(EXE-COLUMN-2DMEAN-SERIAL)"
	@echo "    run-$(EXE-COLUMN-2DMEAN-OMP)"
	@echo "    run-$(EXE-EXE-COLUMN-2DMEAN-OMP-NEON)"
	@echo 
	@echo "Command to remove all objects and executables:"
	@echo "    make clean"

build: $(EXE-COLUMN-2DMEAN-SERIAL)  \
       $(EXE-COLUMN-2DMEAN-OMP) \
       $(EXE-COLUMN-2DMEAN-OMP-NEON) 
 


run: run-$(EXE-COLUMN-2DMEAN-SERIAL)  \
     run-$(EXE-COLUMN-2DMEAN-OMP) \
     run-$(EXE-COLUMN-2DMEAN-OMP-NEON)  


$(EXE-COLUMN-2DMEAN-SERIAL): $(OBJ-COLUMN-2DMEAN-SERIAL)
	$(CC)  -o $(EXE-COLUMN-2DMEAN-SERIAL) $(OBJ-COLUMN-2DMEAN-SERIAL) $(LDFLAGS)
	
$(EXE-COLUMN-2DMEAN-OMP): $(OBJ-COLUMN-2DMEAN-OMP)
	$(CC)  -o $(EXE-COLUMN-2DMEAN-OMP) $(OBJ-COLUMN-2DMEAN-OMP) $(LDFLAGS) $(C_OMP)
	
$(EXE-COLUMN-2DMEAN-OMP-NEON): $(OBJ-COLUMN-2DMEAN-OMP-NEON)
	$(CC)  -o $(EXE-COLUMN-2DMEAN-OMP-NEON) $(OBJ-COLUMN-2DMEAN-OMP-NEON) $(LDFLAGS) $(C_OMP)

run-$(EXE-COLUMN-2DMEAN-SERIAL):
	@(OMP_NUM_THREADS=1; export OMP_NUM_THREADS;\
	  echo "$(M_DIM) $(N_DIM)" > INPUT ;\
	  ./$(EXE-COLUMN-2DMEAN-SERIAL) < INPUT ;\
	  /bin/rm INPUT)


run-$(EXE-COLUMN-2DMEAN-OMP):
	@(OMP_NUM_THREADS=$(NTHREADS); export OMP_NUM_THREADS;\
	  echo "$(M_DIM) $(N_DIM)" > INPUT ;\
	  ./$(EXE-COLUMN-2DMEAN-OMP) < INPUT ;\
	  /bin/rm INPUT)

run-$(EXE-COLUMN-2DMEAN-OMP-NEON):
	@(OMP_NUM_THREADS=$(NTHREADS); export OMP_NUM_THREADS;\
	  echo "$(M_DIM) $(N_DIM)" > INPUT ;\
	  ./$(EXE-COLUMN-2DMEAN-OMP-NEON) < INPUT ;\
	  /bin/rm INPUT)



column-2dmean-serial.o: column-2dmean-serial.c
	$(CC) -c $(CFLAGS) $*.c

column-2dmean-omp.o: column-2dmean-omp.c
	$(CC) -c $(CFLAGS) $(C_OMP) $*.c

column-2dmean-omp-neon.o:column-2dmean-omp-neon.c 
	$(CC) $(NEON-FLAG) -c $(CFLAGS) $(C_OMP) $*.c

clean:
	@/bin/rm -f $(OBJ-COLUMN-2DMEAN-SERIAL)  $(EXE-COLUMN-2DMEAN-SERIAL)
	@/bin/rm -f $(OBJ-COLUMN-2DMEAN-OMP) $(EXE-COLUMN-2DMEAN-OMP)
	@/bin/rm -f $(OBJ-COLUMN-2DMEAN-OMP-NEON) $(EXE-COLUMN-2DMEAN-OMP-NEON)


