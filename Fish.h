#pragma once
#include <vector>
#include <random>
#include "ColorChar.h"

class Fish
{
    public:
        int x;
        int y;
        int toX;
        int toY;
        int height;
        int width;
        int frame;
        std::vector<std::vector<std::vector<colorChar>>> fishChars;
        std::vector<std::vector<std::vector<colorChar>>> flipChars;
        bool load(std::string fileNameFish, std::string fileNameFlip, std::string name);
        bool init(int tankHeight, int tankWidth);
        bool flip;//flips the fish's colorChars at render time
        void updatePosition(int tankHeight, int tankWidth);//moves the fish x y coordinates according to ai

};
