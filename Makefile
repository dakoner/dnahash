CXX=g++
## gcc 3.1 changed to using DWARF debugging
DEBUG=-ggdb -Wall
OPT=-O2
PROFILE=#-pg
CXXFLAGS=$(DEBUG) $(OPT) $(PROFILE) -fno-omit-frame-pointer

DEPEND=-MM
LDFLAGS=$(STLLIB)

all:  rolling slowhash slowdeque Makefile.dep

OBJ=Fasta.o str_toupper.o
rolling: rolling.o convert_2bit.o $(OBJ)
	$(CXX) $(DEBUG) $(OPT) $(PROFILE) -o rolling rolling.o convert_2bit.o $(OBJ) $(LDFLAGS)

slowhash: slowhash.o $(OBJ)
	$(CXX) $(DEBUG) $(OPT) $(PROFILE) -o slowhash slowhash.o $(OBJ)  $(LDFLAGS)

slowdeque: slowdeque.o $(OBJ)
	$(CXX) $(DEBUG) $(OPT) $(PROFILE) -o slowdeque slowdeque.o $(OBJ)  $(LDFLAGS)

clean:
	rm -f rolling slowhash slowdeque rolling.o convert_2bit.o slowhash.o slowdeque.o $(OBJ) Makefile.dep gmon.out

Makefile.dep:
	$(CXX) $(CXXFLAGS) $(DEPEND) $(OBJ:.o=.C) > $@

include Makefile.dep
