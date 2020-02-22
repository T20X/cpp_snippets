INCLUDES = 
LIBS = 
DEBUG = -g

CXX = g++
CXXFLAGS = -O0 -Wall -g -std=c++17 -DLINUX=1 -m64 -pthread -lhugetlbfs -D_REENTRANT $(INCLUDES)
LDFLAGS=-lhugetlbfs

all: app 

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

.cpp:
	$(CXX) $(CXXFLAGS) $< -o $@ 

SRC = main.cpp
OBJ = $(addsuffix .o, $(basename $(SRC)))

app: $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(OBJ)

clean:
	rm -f $(OBJ) app
