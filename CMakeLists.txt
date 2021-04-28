# only for cmake --version >= 3.5.1
cmake_minimum_required(VERSION 3.5.1)

get_filename_component(MY_PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
message( ${MY_PROJECT_NAME} "-----------" ${PROJECT_SOURCE_DIR} )

# project name
project(${MY_PROJECT_NAME})

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# creates the variable EXEC and sets it to hello
set(EXEC ${MY_PROJECT_NAME})
message( ${EXEC} )

# set the C++14 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-variable")
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

    unset(exe_full_target)

    # I used a simple string replace, to cut off .cpp.
    string( REPLACE ".cpp" "" testname ${testsourcefile} )
    get_filename_component(exe_name ${testname} NAME)
    get_filename_component(exe_parent_dir ${testsourcefile} DIRECTORY)
    get_filename_component(exe_parent_dir_name ${exe_parent_dir} NAME)
    string(APPEND exe_full_target ${exe_parent_dir_name} "-" ${exe_name})

    if (DEFINED ${exe_parent_dir_name}_CMAKE_FILE_PATH AND NOT  ${exe_parent_dir_name}_CMAKE_FILE_PATH STREQUAL  "${exe_parent_dir_name}_CMAKE_FILE_PATH-NOTFOUND")
      continue()
    endif()

    find_path (${exe_parent_dir_name}_CMAKE_FILE_PATH NAMES CMakeLists.txt PATHS ${exe_parent_dir})
    if (NOT (${exe_parent_dir_name}_CMAKE_FILE_PATH STREQUAL  "${exe_parent_dir_name}_CMAKE_FILE_PATH-NOTFOUND" OR exe_parent_dir STREQUAL ${PROJECT_SOURCE_DIR}) )
      message(${exe_full_target} "->"  ${CMAKE_FILE_PATH} " got its own CMake -> " ${exe_parent_dir} )
      add_subdirectory(${exe_parent_dir_name})
      continue()
    endif()

    if(NOT ${exe_full_target} MATCHES "disable.*" AND NOT ${exe_name} MATCHES "disable.*")
      message("added target " ${exe_full_target})
      add_executable( ${exe_full_target} ${testsourcefile} )
      target_link_libraries(${exe_full_target} PRIVATE Threads::Threads) 
    endif()

    # Make sure YourLib is linked to each app
    #target_link_libraries( ${testname} YourLib )
endforeach( testsourcefile ${SOURCES} )
