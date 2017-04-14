#icp:   icp.cpp icp.h icp_accel.h   
#	g++ icp.cpp    -O3 -o icp -DFILE_INDEX=100 -DSDEPCX=1 -DSDEPCG=4 -DPOWER_MONITORING -DFREQUENCY_SCALING -DVOLTAGE_SCALING -I/opt/Mohammad/bristol_projects/measurement/power_monitor_usermode/include/  -L/opt/Mohammad/bristol_projects/measurement/power_monitor_usermode/lib -I/opt/Mohammad/bristol_projects/linux_drivers/zynq_opencl_pattern_based/dev-final-with-mem-cacheable  -lfpgaclmeasurement  -pthread -I/usr/local/opencv-2.4/include -L/usr/local/opencv-2.4/lib -lopencv_core -lopencv_highgui -lopencv_imgcodecs
	
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

.SUFFIXES: .f90 .c .o .cpp 


NTHREADS = 2

OBJ-SERIAL  = icp_serial.o 
OBJ-OPENMP = icp_openmp.o 
OBJ-OPENMP-NEON = icp_openmp_neon.o

EXE-SERIAL  = icp_serial.exe
EXE-OPENMP = icp_openmp.exe
EXE-OPENMP-NEON = icp_openmp_neon.exe

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


$(EXE-SERIAL): $(OBJ-SERIAL)
	$(CCX)  -o $(EXE-SERIAL) $(OBJ-SERIAL) $(LDFLAGS) $(LIBS) -lm
$(EXE-OPENMP): $(OBJ-OPENMP)
	$(CCX)  -o $(EXE-OPENMP) $(OBJ-OPENMP) $(LDFLAGS) $(C_OMP) $(LIBS) -lm

$(EXE-OPENMP-NEON): $(OBJ-OPENMP-NEON)
	$(CCX)  -o $(EXE-OPENMP-NEON) $(OBJ-OPENMP-NEON) $(LDFLAGS) $(C_OMP) $(LIBS) -lm


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

icp_serial.o: icp_serial.cpp 
	$(CCX) -c $(CXXFLAGS)  $*.cpp -lm

icp_openmp_neon.o:icp_openmp_neon.cpp 
	$(CCX) -c  $(CXXFLAGS) $(NEON-FLAG) $(C_OMP)  -lm $*.cpp

icp_openmp.o:icp_openmp.cpp
	$(CCX) -c $(CXXFLAGS) $(C_OMP)  $*.cpp -lm



clean:
	@/bin/rm -f $(OBJ-SERIAL)  $(EXE-SERIAL) $(OBJ-OPENMP-NEON)
	@/bin/rm -f $(OBJ-OPENMP) $(EXE-OPENMP)  $(EXE-OPENMP-NEON)


	