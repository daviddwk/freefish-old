#include "Fish.h"
#include "ColorChar.h"
#include "ReadFile.h"

bool Fish::load(std::string fileNameFish, std::string fileNameFlip, std::string name){

    fishChars = readFile(fileNameFish);
    flipChars = readFile(fileNameFlip);

    if(!checkFile(fishChars, "fish", name) || !checkFile(flipChars, "flip", name)){
        return false;
    }
    if(fishChars.size() != flipChars.size() || fishChars[0].size() != flipChars[0].size() || fishChars[0][0].size() != flipChars[0][0].size()){
        std::cout << "mismatching fish and flip " << name << " frame count or size\n";
        return false;
    }

    frame = rand() % fishChars.size();
    flip = false;
    height = fishChars[0].size();
    width = fishChars[0][0].size();

    return true;
}

bool Fish::init(int tankHeight, int tankWidth){

    if(tankHeight - height < 0 || tankWidth - width < 0){
        std::cout << "fish too large or tank too small";
        return false;
    }

    x = rand() % (tankWidth - width);
    y = rand() % (tankHeight - height);
    toX = rand() % (tankWidth - width);
    toY = rand() % (tankHeight - height);

    return true;
}

void Fish::updatePosition(int tankHeight, int tankWidth){
    if(x == toX && y == toY){
        toX = rand() % (tankWidth - width);
        toY = rand() % (tankHeight - height);
    }
    if(x < toX){
        x++;
        flip = false;
    }
    else if(x > toX){
        x--;
        flip = true;
    }
    if(y < toY){
        y++;
    }
    else if(y > toY){
        y--;
    }
}
