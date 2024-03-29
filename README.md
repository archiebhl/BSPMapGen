# BSPMapGen
A C++ library that provides functionality for generating dungeon maps using the Binary Space Partitioning algorithm. It allows developers to create randomized dungeon layouts with customizable parameters.

## Usage
1. **Include the Library**:
   - Copy the header file `BSPMapGen.h` and the DLL `libBSPMapGen.dll` into your project folder.

2. **Compilation**:
   - Compile your source file(s) along with the necessary options to link the DLL:
     ```
     g++ main.cpp -o main.exe -L. -lBSPMapGen
     ```

3. **Run the Program**:
   - Execute the generated executable:
     ```
     ./main.exe
     ```

## Example usage
```cpp
#include "BSPMapGen.h"
#include <iostream>

int main() {
    // Initialize variables
    int mapWidth = 50;
    int mapHeight = 50;
    int minRoomSize = 10;
    int depth = 6;

    // Create an instance of the map
    Map map(mapWidth, mapHeight, minRoomSize, depth);
    
    // Generate the dungeon layout
    map.generate();
    
    // Print the dungeon layout
    map.printDungeonLayout(map.nodes, mapWidth, mapHeight);
    
    return 0;
}
```

## To Do
1. Implement automatic generation of pathways between rooms.
2. Add more functionality to improve usage and customisability. 
3. Add support for generating more complex dungeon layouts.
4. Explore options for optimizing the BSP algorithm for better performance on larger maps.
