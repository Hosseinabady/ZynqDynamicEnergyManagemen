IDIR =../dev
SRCDIR =./
CC=gcc
CFLAGS=-I$(IDIR)

ODIR =.
LDIR =./

LIBOUT = ./libfpgacl_memory.a
LIBS=-lm -pthread

_DEPS = fpgacl_memory.h 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = fpgacl_memory.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


$(LIBOUT): $(OBJ)
	ar rcs $(LIBOUT) $(OBJ)

	
	
	
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~  ./test
	

