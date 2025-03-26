# DigiSlate: An Interactive Board

## Overview
The Digital Board is a Qt-based Digital board application that provides multiple shape drawing tools, color selection, and an intuitive UI for easy interaction. It allows users to create, edit, and save your educational board data as pages efficiently.

## Features
- Supports Shapes **Free Hand, Lines, Circles, Ellipses, Polygons, Polyline, Arcs, Rectangles, Points, and Text**.
- Includes a **color picker** and adjustable **pen width**.
- **Undo/Redo functionality** in private branchs.
- **Select and Drag** shapes.
- Shapes data save/load functionality for accesible in future or for future references.
- **Intuitive UI with a toolbar and a floating shape menu**.

## Installation
### Prerequisites
- Qt 5.x or Qt 6.x
- CMake or QMake
- A C++ Compiler (GCC/Clang/MSVC)
- Git

### Steps
```sh
git clone https://github.com/ashvin-parmar/DigiSlate.git
cd digital-board
mkdir build && cd build
cmake ..
make
./DigiSlate

