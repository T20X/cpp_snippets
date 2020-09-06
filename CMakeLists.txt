# only for cmake --version >= 3.5.1
cmake_minimum_required(VERSION 3.5.1)

get_filename_component(MY_PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
message( ${MY_PROJECT_NAME} )

# project name
project(${MY_PROJECT_NAME})

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# creates the variable EXEC and sets it to hello
set(EXEC ${MY_PROJECT_NAME})
message( ${EXEC} )

# set the C++14 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -latomic")

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_NO_SYSTEM_PATHS TRUE)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

if (Boost_NO_SYSTEM_PATHS)
  set(BOOST_ROOT "/home/maine/boost/boost_1_71_0/build")
  set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}/include")
  set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/lib")
endif (Boost_NO_SYSTEM_PATHS) 

find_package(Boost COMPONENTS regex date_time system filesystem thread graph program_options) 
find_package(Boost REQUIRED regex date_time system filesystem thread graph program_options)
find_package(Boost COMPONENTS program_options REQUIRED)

# I../includes
include_directories(includes common)

# puts all .cpp files inside src to the SOURCES variable
file(GLOB SOURCES *.cpp */*.cpp)

# compiles the files defined by SOURCES to generante the executable defined by EXEC
foreach( testsourcefile ${SOURCES} )
    # I used a simple string replace, to cut off .cpp.
    string( REPLACE ".cpp" "" testname ${testsourcefile} )
    get_filename_component(exe_name ${testname} NAME)
    get_filename_component(exe_parent_dir ${testsourcefile} DIRECTORY)
    get_filename_component(exe_parent_dir_name ${exe_parent_dir} NAME)
    string(APPEND exe_full_target ${exe_parent_dir_name} "-" ${exe_name})
    if(NOT ${exe_full_target} MATCHES "disable.*" OR ${exe_name} MATCHES "disable.*")
      message("added target " ${exe_full_target})
      add_executable( ${exe_full_target} ${testsourcefile} )
      target_link_libraries(${exe_full_target} PRIVATE Threads::Threads)
    endif()
    unset(exe_full_target)
    # Make sure YourLib is linked to each app
    #target_link_libraries( ${testname} YourLib )
endforeach( testsourcefile ${SOURCES} )
