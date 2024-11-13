# Preconditioner for Cloth and Deformable Body Simulation
## Overview

Preconditioner for Cloth and Deformable Body Simulation is a high-performance C++ library designed to accelerate simulations involving cloth dynamics and deformable bodies. Leveraging advanced numerical methods and optimization techniques such as Schwarz preconditioning, SIMD (Single Instruction, Multiple Data) vectorization, and parallel computing with OpenMP, this library provides efficient and scalable solutions for real-time and large-scale simulations.

## Features

- **Schwarz Preconditioning**: Implements Schwarz preconditioner to enhance the convergence rate of iterative solvers in simulation tasks.
- **SIMD Optimization**: Utilizes SIMD vectorization for accelerated mathematical computations, improving performance on supported hardware.
- **Parallel Computing**: Integrates OpenMP for multi-threaded processing, enabling efficient use of multi-core CPUs.
- **Eigen Integration**: Incorporates Eigen's LDLT decomposition for reliable and efficient matrix factorization.
- **Flexible Data Structures**: Provides versatile vector and matrix classes tailored for simulation needs.
- **Modular Design**: Easily extendable and maintainable architecture, allowing seamless integration into larger simulation frameworks.

## Getting Started

### Prerequisites

- **C++ Compiler**: Compatible with C++17 standard (e.g., GCC, Clang, MSVC).
- **CMake**: Version 3.10 or higher.
- **Eigen3**: A high-level C++ library of template headers for linear algebra.
- **OpenMP**: For parallel computing support.

### Installation

1. **Clone the Repository**

   ```bash
   git clone https://github.com/yourusername/SeSchwarzPreconditionerProject.git
   cd SeSchwarzPreconditionerProject
   ```

2. **Install Dependencies**

   Ensure that Eigen3 and OpenMP are installed on your system.

   - **Ubuntu**

     ```bash
     sudo apt-get update
     sudo apt-get install -y libeigen3-dev
     ```

   - **macOS (using Homebrew)**

     ```bash
     brew install eigen
     ```

   - **Windows**

     - Download and install Eigen from [Eigen's official website](https://eigen.tuxfamily.org/).
     - Ensure that OpenMP is supported by your compiler (MSVC supports it by default).

3. **Build the Project**

   ```bash
   mkdir build
   cd build
   cmake .. -DCMAKE_BUILD_TYPE=Release
   make -j$(nproc)
   ```

4. **Run the Test Executable**

   After a successful build, run the test executable to verify the setup.

   ```bash
   ./SeSchwarzTest
   ```

## Usage

### Entry Point

The primary interface for using the Schwarz preconditioner is provided through the `SeSchwarzPreconditioner` class. For detailed usage, refer to the [SeSchwarzPreconditioner.h](./SeSchwarzPreconditioner.h) header file.


*This project is a mirror of [https://wanghmin.github.io/#featured](https://wanghmin.github.io/#featured).*