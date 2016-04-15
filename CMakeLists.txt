project("Interactive Broker API Python Wrapper")

#prerequests
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
find_package(PythonLibs REQUIRED)
find_package(PythonInterp REQUIRED)
find_package(Boost COMPONENTS python REQUIRED)  #boost_pythons need to be the same version

#code settings
include_directories(${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
file(GLOB OTHER_SRC
  "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
  )

#macro
add_definitions( -DIB_USE_STD_STRING -Wno-switch)

#remove prefix of generated library
set(CMAKE_SHARED_LIBRARY_PREFIX "")
#target library
add_library(IBCpp SHARED ${OTHER_SRC})
#link with boost_python
target_link_libraries(IBCpp ${Boost_LIBRARIES} ${PYTHON_LIBRARY})
#enable C++11
target_compile_features(IBCpp PUBLIC cxx_range_for)
