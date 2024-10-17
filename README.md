# Three-Body Problem Simulation

### Overview
This project simulates the three-body problem, a classic problem in physics where three celestial bodies interact under mutual gravitational forces. The system’s evolution over time is computed using numerical integration, specifically the Runge-Kutta 4th Order (RK4) method, which ensures a stable and accurate approximation of the bodies' trajectories. The simulation is rendered in real-time using SDL2, offering an interactive visualization of the system's complex dynamics.

### Features
- Real-time simulation and visualization of three-body dynamics.
- Adjustable initial positions, velocities, and masses.
- Simulation results can be saved to a CSV file for analysis.
- Interactive rendering using SDL2.

### Requirements
- Real-time simulation and visualization of complex three-body dynamics.
- Adjustable initial positions, velocities, and masses to explore various scenarios.
- Simulation data can be saved to a CSV file for further analysis or plotting.
- Interactive rendering of the system using SDL2.
- Supports pre-configured stable or chaotic orbits, providing both predictable and unpredictable behavior examples.

### Hénon’s First Orbit:
<img src="https://github.com/obluda2173/3_body_problem/blob/main/media/stable_1.gif" width="100%" height="100%">

### Chaotic example 1:
<img src="https://github.com/obluda2173/3_body_problem/blob/main/media/chaotic_1.gif" width="100%" height="100%">

### Chaotic example 2:
<img src="https://github.com/obluda2173/3_body_problem/blob/main/media/chaotic_2.gif" width="100%" height="100%">

### How to run
This project includes a Makefile, making it easy to compile and run:
- Run make to compile the program.
- Execute the program with ./tbp

> **_NOTE:_** You might need to adjust the SDL2 library path in the tbp.h file depending on your SDL2 installation.

### Key Parameters
- Mass1, Mass2, Mass3: Set the masses of the bodies in tbp.h.
- TIME_STEP: Adjust the time step for numerical integration.
You can modify the initial conditions in the code for different scenarios. The simulation also logs the positions and velocities to tbp.csv.

### Customization
To further experiment with the system:
- Edit the initial masses, positions, or velocities in tbp.h and tbp.c to simulate various celestial configurations.
- Predefined scenarios, including stable orbits and chaotic systems, are included for exploration. You can select these options in tbp.c.
