# Three-Body Problem Simulation

### Overview
This project simulates the three-body problem, visualizing how three celestial bodies interact under mutual gravitational forces. Using numerical integration (Runge-Kutta method), it computes the motion of the bodies and visualizes their orbits in real-time using SDL2.

### Features
- Real-time simulation and visualization of three-body dynamics.
- Adjustable initial positions, velocities, and masses.
- Simulation results can be saved to a CSV file for analysis.
- Interactive rendering using SDL2.

### Requirements
- SDL2 for visualization
- GCC (or any C compiler)
- Install SDL2 on macOS via Homebrew:

### Hénon’s First Orbit:
<img src="https://github.com/obluda2173/3_body_problem/blob/main/media/example_1.gif" width="40%" height="40%">

### How to run
This project already has a Makefile, this making it easy to run:
1. Run make
2. Run ./tbp

### Key Parameters
- Mass1, Mass2, Mass3: Set the masses of the bodies in tbp.h.
- TIME_STEP: Adjust the time step for numerical integration.
You can modify the initial conditions in the code for different scenarios. The simulation also logs the positions and velocities to tbp.csv.
To adjust the masses, positions, or velocities, edit the corresponding values in tbp.h and tbp.c.
You can also choose few option of bodies in tbp.c as well.
