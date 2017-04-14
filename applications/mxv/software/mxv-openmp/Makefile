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

M_DIM = 2000
N_DIM = 2000
NTHREADS = 2

OBJ-FIG3.5  = fig3.5-mxv-serial.o
OBJ-FIG3.10 = fig3.10-mxv-omp.o
OBJ-FIG3.10-NEON = fig3.10-mxv-omp-neon.o

EXE-FIG3.5  = fig3.5.exe
EXE-FIG3.10 = fig3.10.exe
EXE-FIG3.10-NEON = fig3.10.neon.exe


NEON-FLAG = -O3 -mcpu=cortex-a9 -mfpu=neon-fp16 -ftree-vectorize -mvectorize-with-neon-quad -mfloat-abi=hard -ffast-math

help:
	@echo "Command to build all example programs:"
	@echo "    make build"
	@echo
	@echo Command to run all example programs:
	@echo "    make run"
	@echo
	@echo "Targets to build individual examples:"
	@echo "   $(EXE-FIG3.5)  - Sequential version of MXV in C"
	@echo "   $(EXE-FIG3.10) - OpenMP version in C"
	@echo "   $(EXE-FIG3.10-NEON) - OpenMP version in C"
	@echo
	@echo "Targets to run individual examples:"
	@echo "    run-$(EXE-FIG3.5)"
	@echo "    run-$(EXE-FIG3.10)"
	@echo 
	@echo "Command to remove all objects and executables:"
	@echo "    make clean"

build: $(EXE-FIG3.5)  \
       $(EXE-FIG3.10) \
       $(EXE-FIG3.10-NEON) 
 


run: run-$(EXE-FIG3.5)  \
     run-$(EXE-FIG3.10) \
     run-$(EXE-FIG3.10-NEON)  


$(EXE-FIG3.5): $(OBJ-FIG3.5)
	$(CC)  -o $(EXE-FIG3.5) $(OBJ-FIG3.5) $(LDFLAGS)
$(EXE-FIG3.10): $(OBJ-FIG3.10)
	$(CC)  -o $(EXE-FIG3.10) $(OBJ-FIG3.10) $(LDFLAGS) $(C_OMP)
$(EXE-FIG3.10-NEON): $(OBJ-FIG3.10-NEON)
	$(CC)  -o $(EXE-FIG3.10-NEON) $(OBJ-FIG3.10-NEON) $(LDFLAGS) $(C_OMP)

run-$(EXE-FIG3.5):
	@(OMP_NUM_THREADS=1; export OMP_NUM_THREADS;\
	  echo "$(M_DIM) $(N_DIM)" > INPUT ;\
	  ./$(EXE-FIG3.5) < INPUT ;\
	  /bin/rm INPUT)


run-$(EXE-FIG3.10):
	@(OMP_NUM_THREADS=$(NTHREADS); export OMP_NUM_THREADS;\
	  echo "$(M_DIM) $(N_DIM)" > INPUT ;\
	  ./$(EXE-FIG3.10) < INPUT ;\
	  /bin/rm INPUT)

run-$(EXE-FIG3.10-NEON):
	@(OMP_NUM_THREADS=$(NTHREADS); export OMP_NUM_THREADS;\
	  echo "$(M_DIM) $(N_DIM)" > INPUT ;\
	  ./$(EXE-FIG3.10-NEON) < INPUT ;\
	  /bin/rm INPUT)



fig3.5-mxv-serial.o: fig3.5-mxv-serial.c
	$(CC) -c $(CFLAGS) $*.c

fig3.10-mxv-omp.o: fig3.10-mxv-omp.c
	$(CC) -c $(CFLAGS) $(C_OMP) $*.c

fig3.10-mxv-omp-neon.o:fig3.10-mxv-omp-neon.c 
	$(CC) $(NEON-FLAG) -c $(CFLAGS) $(C_OMP) $*.c

clean:
	@/bin/rm -f $(OBJ-FIG3.5)  $(EXE-FIG3.5)
	@/bin/rm -f $(OBJ-FIG3.10) $(EXE-FIG3.10)
	@/bin/rm -f $(OBJ-FIG3.10-NEON) $(EXE-FIG3.10-NEON)


