g++ -std=c++17 -c -fpic static.cpp
ar rcs libstatic.a static.o
g++ -std=c++17 -c -fpic dynamic.cpp 
g++ -shared -o libdynamic.so dynamic.o -L./ -lstatic
g++ -std=c++17 -c main.cpp A.cpp C.cpp
g++ -L./ -Wl,-rpath=./ main.o A.o C.o -lstatic -ldynamic
