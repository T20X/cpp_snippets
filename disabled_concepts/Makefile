INCLUDES = 
LIBS = 
DEBUG = -g

CXX = g++
CXXFLAGS = -O0 -Wall -g -std=c++2a -fconcepts -DLINUX=1 -m64 -pthread -D_REENTRANT $(INCLUDES)

all: app 

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

.cpp:
	$(CXX) $(CXXFLAGS) $< -o $@ 

SRC = main.cpp
OBJ = $(addsuffix .o, $(basename $(SRC)))

app: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

clean:
	rm -f $(OBJ) app
