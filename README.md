### C++ K-Means Clustering Visualizer

An interactive data mining application built from scratch in C++ that implements the K-Means clustering algorithm and visualizes its behavior in real-time using the SDL2 library.

I got this idea from one of my Data Analytics class where the topic were market basket analysis,fp trees and clustering

I used the two moons dataset to show the challenges of applying centroid based techniques to non-spherical data.

📊 Project Showcase: Visualizing K-Means

The primary goal is to visually demonstrate both the behavior and limitations of the K-Means algorithm.

🔹 Initial State

The visualization begins with two randomly placed centroids.
All data points are initially assigned to the first cluster (red)

![Initial State](https://github.com/Axikop/Data-Mining-in-C-/blob/main/Screenshot%202025-07-29%20230418.png?raw=true)


🔸 Final Converged State

After several iterations (by pressing the space bar), the algorithm converges.
The final result clearly shows how K-Means incorrectly splits crescent-shaped clusters, highlighting a major limitation.

![Final State](https://github.com/Axikop/Data-Mining-in-C-/blob/main/limit.png?raw=true)


### ⚙️ How to Build and Run

✅ 1. Prerequisites
A C++ compiler (recommended: g++ with MinGW-w64 on Windows)
SDL2 development library, placed under an SDL2/ directory


🧱 2. Compilation
Open a terminal, navigate to the root directory, and run:

bash
```
g++ main.cpp -ISDL2/include -LSDL2/lib -lmingw32 -lSDL2main -lSDL2 -o output/visualizer.exe
```

📦 3. Prepare to Run
Copy the SDL2 runtime file before running:


copy SDL2/bin/SDL2.dll output/


🚀 4. Execution
Run the application:
```
./output/visualizer.exe
```

