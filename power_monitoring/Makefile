IDIR =./include
SRCDIR =./src
CC=gcc
CFLAGS=-I$(IDIR)

ODIR =./obj
LDIR =./lib

LIBOUT = ./lib/libfpgaclmeasurement.a
LIBS=-lm -pthread

_DEPS = measurement.h 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = measurement.o power_monitor.o measurement_threads.o set_frequency.o pl_frequency.o ps_frequency.o set_vccint_voltage.o monitoring.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


$(LIBOUT): $(OBJ)
	ar rcs $(LIBOUT) $(OBJ)

	
test: $(OBJ)
	gcc src/test.c src/monitoring.c -o test -DPOWER_MONITORING -L./lib   -Iinclude -lfpgaclmeasurement -pthread


set_vccint_voltage:$(OBJ)
	gcc src/set_vccint_voltage.c -o  set_vccint_voltage  -pthread -L./lib -lfpgaclmeasurement  -Iinclude

set_vccpint_voltage:$(OBJ)
	gcc src/set_vccpint_voltage.c -o  set_vccpint_voltage  -pthread -L./lib -lfpgaclmeasurement  -Iinclude
		
set_vcc1v5_voltage:$(OBJ)
	gcc src/set_vcc1v5_voltage.c -o  set_vcc1v5_voltage  -pthread -L./lib -lfpgaclmeasurement  -Iinclude
		
pl_frequency: $(OBJ)
	gcc src/pl_frequency.c -o pl_frequency -L./lib -lfpgaclmeasurement  -Iinclude

ps_frequency: $(OBJ)
	gcc src/ps_frequency.c -o ps_frequency -L./lib -lfpgaclmeasurement  -Iinclude

pl_disable_clock: $(OBJ)
	gcc src/pl_disable_clock.c -o pl_disable_clock -L./lib -lfpgaclmeasurement  -Iinclude			

pl_enable_clock: $(OBJ)
	gcc src/pl_enable_clock.c -o pl_enable_clock -L./lib -lfpgaclmeasurement  -Iinclude	
	
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~  ./test
	

