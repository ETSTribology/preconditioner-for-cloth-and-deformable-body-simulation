cmake_minimum_required(VERSION 3.10)
project(SeSchwarzPreconditionerProject VERSION 1.0 LANGUAGES CXX)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable warnings
if (MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -pedantic -O3)
endif()

# Find OpenMP
find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    set(OpenMP_LIBS OpenMP::OpenMP_CXX)
endif()

# Find Eigen3
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

# Collect source files
set(SOURCE_FILES
    SeSchwarzPreconditioner.cpp
    SeOmp.cpp
)

# Collect header files (optional, for IDEs)
set(HEADER_FILES
    SeAabb.h
    SeAabbSimd.h
    SeArray2D.h
    SeCollisionElements.h
    SeCsr.h
    SeIntrinsic.h
    SeMath.h
    SeMathSimd.h
    SeMatrix.h
    SeMorton.h
    SePreDefine.h
    SeSchwarzPreconditioner.h
    SeSchwarzPreconditionerPreviousVersion.h
    SeUtility.h
    SeVector.h
    SeVectorSimd.h
)

# Define the executable
add_executable(SeSchwarzTest main.cpp ${SOURCE_FILES} ${HEADER_FILES})

# Include directories
target_include_directories(SeSchwarzTest
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${EIGEN3_INCLUDE_DIR}
)

# Link libraries
target_link_libraries(SeSchwarzTest
    PRIVATE
        OpenMP_LIBS
        Eigen3::Eigen
)

# Optionally, set build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Installation
install(TARGETS SeSchwarzTest DESTINATION bin)
