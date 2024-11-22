# Shallow Water Equations Simulation

## Overview

This code implements a numerical simulation of the shallow water equations using a parallel computing approach with OpenMP. The shallow water equations are a set of hyperbolic partial differential equations that describe the flow of a fluid under the influence of gravity, assuming that the horizontal length scale is much greater than the vertical depth.

## Mathematical Background

### Shallow Water Equations

The shallow water equations in two dimensions are:

1. Continuity equation:

   $\frac{\partial h}{\partial t} + \frac{\partial (hu)}{\partial x} + \frac{\partial (hv)}{\partial y} = 0$

2. Momentum equations:

   $\frac{\partial (hu)}{\partial t} + \frac{\partial}{\partial x}(hu^2 + \frac{1}{2}gh^2) + \frac{\partial (huv)}{\partial y} = 0$
   
   $\frac{\partial (hv)}{\partial t} + \frac{\partial (huv)}{\partial x} + \frac{\partial}{\partial y}(hv^2 + \frac{1}{2}gh^2) = 0$
   
   Where:
   - $h$ is the total fluid column height
   - $u$ is the fluid velocity in x-direction
   - $v$ is the fluid velocity in y-direction
   - $g$ is the acceleration due to gravity

## Numerical Method

### Finite Difference Scheme

The simulation uses a finite difference method to discretize the shallow water equations in space and time. The spatial derivatives are approximated using central differences, and time integration is performed using a third-order Runge-Kutta method.

### Flux Calculation

The code calculates fluxes in both x and y directions using a high-order finite difference approximation:

$f_{i+1/2} = \frac{-f_{i-1} + 26f_i - f_{i+1}}{24}$

This scheme provides better accuracy compared to simple first-order methods.


### Runge-Kutta Method

A third-order Runge-Kutta method is used for time integration, providing stability and accuracy. The method involves three substeps per time step, each updating the state variables.


# Running the Shallow Water Equations Simulation

## Prerequisites

- Intel C Compiler (icc)
- OpenMP support (included with Intel Compiler)

## Compilation Instructions

1. Ensure all source files are in the same directory:
   - `main.c`
   - `flux.c`
   - `tendency.c`
   - `bound.c`
   - Any necessary header files (`.h` files)

2. Compile the code using the Intel C Compiler with the following command:
   ```
   icc -O3 -g -std=c99 -qopenmp -o main bound.c flux.c tendency.c main.c
   ```

   This command does the following:
   - Uses the Intel C Compiler (icc)
   - `-O3`: Applies aggressive optimizations
   - `-g`: Includes debugging information
   - `-std=c99`: Uses the C99 standard
   - `-qopenmp`: Enables OpenMP support
   - `-o main`: Names the output executable "main"

## Running the Simulation

1. Set the number of OpenMP threads:
   ```
   export OMP_NUM_THREADS=4  # Or any other number
   ```

2. Run the executable:
   ```
   ./main
   ```
