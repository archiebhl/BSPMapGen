#include "../include/BSPMapGen.h"
#include <vector>
#include <iostream>
#include <random>
#include <chrono>
using namespace std;

Node::Node(int _x, int _y, int _width, int _height) : x(_x), y(_y), width(_width), height(_height), left(nullptr), right(nullptr) {
}
Node::~Node(){
    if (left) delete left;
    if (right) delete right;
    left = nullptr;
    right = nullptr;
}

Map::Map(int _width, int _height, int _minRoomSize, int _depth) : width(_width), height(_height), minRoomSize(_minRoomSize), depth(_depth){
    nodes.push_back(new Node(0, 0, width, height)); // adding root node
}
Map::~Map(){
    nodes.clear();
}

void Map::generate(){
    for (Node* node : nodes){
        node->split(minRoomSize, depth, nodes);
    }
}

std::random_device rd;
std::mt19937 gen(time(nullptr));

/*
Splits the root node recursively, until the the tree reaches the user-defined depth
*/
void Node::split(int minRoomSize, int depth, std::vector<Node*>& nodes){

    if (this == nullptr || depth <= 0) return;

    // generating split specifics
    bool splitHorizontally = (rand() % 2 == 0);
    int max = (splitHorizontally ? this->height - minRoomSize : this->width - minRoomSize);
    
    std::uniform_int_distribution<> distr(minRoomSize, max);
    
    int splitSize = distr(gen);

    if (splitSize > 500 || splitSize < -500){
        return;
    }

    // performing split
    if (splitHorizontally){
        this->left = new Node(this->x, this->y, this->width, splitSize);
        this->right = new Node(this->x, this->y + splitSize, this->width, this->height - splitSize);
    } else{
        this->left = new Node(this->x, this->y, splitSize, this->height);
        this->right = new Node(this->x + splitSize, this->y, this->width - splitSize, this->height);
    }

    // Adding the nodes to the vector
    nodes.push_back(this->left);
    nodes.push_back(this->right);

    this->left->split(minRoomSize, depth - 1, nodes);
    this->right->split(minRoomSize, depth - 1, nodes);
}

void Map::printTreeLeafs(const std::vector<Node*>& nodes) {
    std::cout << "Leaf Nodes:\n";
    
    for (Node* node : nodes) {
        if (node->left == nullptr && node->right == nullptr) {
            std::cout << "x=" << node->x << ", y=" << node->y << ", width=" << node->width << ", height=" << node->height << std::endl;
        }
    }
}

/*
Printing methods
*/
void Map::printDungeonLayout(const std::vector<Node*>& nodes, int width, int height) {
    std::vector<std::vector<char>> dungeon(height, std::vector<char>(width, '.')); // Initialize dungeon with '.'
    
    for (Node* node : nodes) {
        if (node->left == nullptr && node->right == nullptr) {
            // Mark the perimeter of the leaf node in the dungeon layout
            // Top and bottom borders
            for (int x = node->x; x < node->x + node->width; ++x) {
                dungeon[node->y][x] = '#';
                dungeon[node->y + node->height - 1][x] = '#';
            }
            // Left and right borders
            for (int y = node->y; y < node->y + node->height; ++y) {
                dungeon[y][node->x] = '#';
                dungeon[y][node->x + node->width - 1] = '#';
            }
        }
    }
    
    // Print out the dungeon layout
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::cout << dungeon[y][x] << ' ';
        }
        std::cout << std::endl;
    }
}

