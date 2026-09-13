# Barnes–Hut N-Body Gravity Simulation

A real-time 2D gravitational N-body simulation written in C++ using OpenGL and ImGui.

This project implements a Barnes–Hut quadtree approximation to accelerate force computation from:

\[
O(N^2) \rightarrow O(N \log N)
\]

allowing simulations with up to 100k particles in real time on CPU.

---

# Features

- Real-time gravitational N-body simulation
- Barnes–Hut quadtree force approximation
- Custom quadtree memory pool allocator
- OpenGL rendering pipeline
- ImGui control/debug interface
- Runtime simulation controls
- Emergent structure formation
- Stable large-scale particle evolution
- Supports 100k+ particles

---

# Simulation Overview

Particles interact through Newtonian gravity:

\[
F \propto \frac{1}{r^2}
\]

To avoid the quadratic complexity of direct pairwise interaction, the simulation uses a Barnes–Hut quadtree structure to approximate distant particle clusters using their center of mass.

This reduces computational complexity significantly while preserving large-scale dynamics.

---

# Emergent Behavior

The simulation exhibits several interesting collective behaviors:

- Filamentary collapse
- Hierarchical clustering
- Violent relaxation
- Approximate virialized equilibrium
- Fractal-like transient structures

Uniform random initial conditions naturally evolve into dense gravitational clusters over time.

---

# Screenshots

<img width="1920" height="1080" alt="Screenshot (313)" src="https://github.com/user-attachments/assets/02a2f059-a1bf-4ed8-958f-5c65d261f3f2" />
<img width="1920" height="1080" alt="Screenshot (312)" src="https://github.com/user-attachments/assets/88af4af5-ed56-410f-9a87-18a57c411d35" />
<img width="1920" height="1080" alt="Screenshot (321)" src="https://github.com/user-attachments/assets/bba9b1b2-e388-4af7-aaef-c7ca6313dcea" />
<img width="1920" height="1080" alt="Screenshot (326)" src="https://github.com/user-attachments/assets/1c89982f-1d7e-4736-a7a3-3e1af70961ea" />
<img width="1920" height="1080" alt="Screenshot (318)" src="https://github.com/user-attachments/assets/f7c1db56-3b53-408c-8911-e76c15b2df50" />

# Technologies Used

- C++
- OpenGL
- GLFW
- GLM
- ImGui

---

# Performance

| Particle Count | FPS |
|---|---|
| 10k | ~120 |
| 20k | ~60 |
| 50k | ~30 |
| 100k | ~14 |

Performance scales approximately as:

\[
O(N \log N)
\]

consistent with Barnes–Hut complexity.

---

# Quadtree Structure

Each quadtree node stores:

- Bounding box
- Total mass
- Center of mass
- Child pointers

The tree is rebuilt every frame based on updated particle positions.

---

# Numerical Stability

The simulation includes:

- Gravitational softening
- Minimum node subdivision size
- Recursive force traversal
- Dynamic timestep evolution

Current integration uses Euler integration.

Future improvements include:
- Leapfrog integration
- Symplectic integrators
- Adaptive timesteps
- Proper Barnes–Hut opening criterion

---

# Controls

| Key / UI | Action |
|---|---|
| Pause | Pause simulation |
| Reset | Reset particle distribution |
| ImGui Panel | Runtime diagnostics |

Displayed runtime data:
- Particle count
- FPS
- Quadtree node count
- Timestep

---

# Future Improvements

- Proper Barnes–Hut opening criterion
- GPU compute acceleration
- SIMD optimization
- Parallel tree traversal
- Collision handling
- Galaxy initial conditions
- Energy diagnostics
- Center-of-mass tracking
- Velocity Verlet / Leapfrog integration

---

# Building

## Requirements

- C++17
- OpenGL
- GLFW
- GLM (Please include the glm files inside a folder named glm under the resources folder)
- ImGui
