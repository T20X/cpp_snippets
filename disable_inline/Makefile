INCLUDES = -I$(BOOST_INCLUDE) -I${PROJECTS}/common
LIBS = 
DEBUG = -g

CXX = g++
CXXFLAGS = -O0 -Wall  -std=c++17 -DLINUX=1 -m64 -pthread -D_REENTRANT $(INCLUDES)

all: app 

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

.cpp:
	$(CXX) $(CXXFLAGS) $< -o $@ 

SRC = C.cpp main.cpp A.cpp B.cpp
OBJ = $(addsuffix .o, $(basename $(SRC)))

app: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

clean:
	rm -f $(OBJ) app
