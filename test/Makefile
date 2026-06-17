OBJS=test.o H2prO.o
SKETCHDIR=../sketch/
CLASS=$(SKETCHDIR)H2prO.cpp
CXXFLAGS=-I$(SKETCHDIR)

all: $(OBJS)
	$(CXX) $(OBJS) -o test

H2prO.o: $(CLASS)
	$(CXX) -c $(CLASS) -o H2prO.o

test: all
	./test

clean:
	$(RM) *.o test
