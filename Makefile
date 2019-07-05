CXX=g++
## gcc 3.1 changed to using DWARF debugging
DEBUG=-g -Wall
OPT=-O2
PROFILE=-pg
CXXFLAGS=$(DEBUG) $(OPT) $(PROFILE) -fno-omit-frame-pointer

DEPEND=-MM
LDFLAGS=$(STLLIB)

all:  rolling Makefile.dep

OBJ=rolling.o Fasta.o
EXE=rolling
$(EXE): $(OBJ)
	$(CXX) $(DEBUG) $(OPT) $(PROFILE) -o $(EXE) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(EXE) $(OBJ) Makefile.dep

Makefile.dep:
	$(CXX) $(CXXFLAGS) $(DEPEND) $(OBJ:.o=.C) > $@

include Makefile.dep
