cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME demo)
project(${PROJECT_NAME})

# Get DOLFIN configuration data (DOLFINConfig.cmake must be in DOLFIN_CMAKE_CONFIG_PATH)
find_package(DOLFIN REQUIRED)
include(${DOLFIN_USE_FILE})



add_executable(hyper_elasticity2 lab3.cpp)
target_link_libraries(hyper_elasticity2 dolfin)

add_executable(pois2 pois_lab3.cpp)
target_link_libraries(pois2 dolfin)


