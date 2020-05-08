# only for cmake --version >= 3.5.1
cmake_minimum_required(VERSION 3.5.1)

get_filename_component(MY_PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
message( ${MY_PROJECT_NAME} )

# project name
project(${MY_PROJECT_NAME})

# creates the variable EXEC and sets it to hello
set(EXEC ${MY_PROJECT_NAME})
message( ${EXEC} )

# set the C++14 standard
set(CMAKE_CXX_STANDARD 17)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_NO_SYSTEM_PATHS TRUE)

if (Boost_NO_SYSTEM_PATHS)
  set(BOOST_ROOT "/home/maine/boost/boost_1_71_0/build")
  set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}/include")
  set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/lib")
endif (Boost_NO_SYSTEM_PATHS) 

find_package(Boost COMPONENTS regex date_time system filesystem thread graph program_options) 
find_package(Boost REQUIRED regex date_time system filesystem thread graph program_options)
find_package(Boost COMPONENTS program_options REQUIRED)

# I../includes
include_directories(includes)

# puts all .cpp files inside src to the SOURCES variable
file(GLOB SOURCES *.cpp)

# compiles the files defined by SOURCES to generante the executable defined by EXEC
add_executable(${EXEC} ${SOURCES})
