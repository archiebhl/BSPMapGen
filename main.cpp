#include "include\BSPMapGen.h"

int main(){
    
    int mapWidth = 50;
    int mapHeight = 50;
    int minRoomSize = 10;
    int depth = 6;

    Map map(mapWidth, mapHeight, minRoomSize, depth);
    map.generate();
    map.printDungeonLayout(map.nodes, mapWidth, mapHeight);

    return 0;
}
