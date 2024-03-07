#ifndef BSPMAPGEN_H
#define BSPMAPGEN_H

#include <vector>
#include <cstdlib>

class Node{
    public:
        int x, y, width, height;
        Node* left;
        Node* right;;

        Node(int _x, int _y, int _width, int _height);
        ~Node();
        void split(int minRoomSize, int depth, std::vector<Node*>& nodes);
};

class Map{
    public:
        std::vector<Node*> nodes;
        int width, height, minRoomSize, depth;

        Map(int _width, int _height, int _minRoomSize, int _depth);
        ~Map();
        
        void generate();
        void printTreeLeafs(const std::vector<Node*>& nodes);
        void printDungeonLayout(const std::vector<Node*>& nodes, int width, int height);
};

#endif