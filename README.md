# FdF - Fil de Fer

> 3D isometric rendering of topographic maps and 2D data representations.

FdF (Fil de Fer) is a 3D wireframe renderer that creates isometric representations from 2D map files. It transforms numerical grid data into visual 3D landscapes, making it ideal for visualizing topography, elevation data, and any structured 2D information in an engaging three-dimensional perspective.

<img width="1888" height="1060" alt="image" src="https://github.com/user-attachments/assets/0be1daa4-10dc-471b-8a70-dd6e01e8a354" />

## Installation

Ubuntu:

```sh
sudo apt-get install gcc make xorg libxext-dev libbsd-dev
make mlx
make bonus
./fdf_bonus <map_file>
```

## Usage example

FdF takes map files containing numerical values where each number represents an elevation point. The application renders these as a 3D wireframe model that you can interact with in real-time.

Example map format:

```text
0  0  0  0  0
0  1  1  1  0
0  1  2  1  0
0  1  1  1  0
0  0  0  0  0
```

Controls:

* Zoom: `+` (in), `-` (out)
* Rotation: `A` and `D`
* Translation: Arrow keys
* Projection: `O` (orthographic), `I` (isometric)
* Height: `Z` and `X`

## Development setup

```sh
# Install dependencies
sudo apt-get install gcc make xorg libxext-dev libbsd-dev

# Build the minilibx library and project
make mlx
make bonus

# Run with a test map
./fdf_bonus maps/pylone.fdf
```
