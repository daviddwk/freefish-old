#pragma once

#include <vector>
#include <fstream>
#include "ColorChar.h"

static std::vector<std::vector<std::vector<colorChar>>> readFile(std::string fileName){
	std::vector<std::vector<std::vector<colorChar>>> output;

	std::ifstream file(fileName);

	if(!file){
		std::cout << "Can not open file \"" << fileName << "\"!\n";
		return output;
	}

	colorChar current;
	bool lastNew = false;

	std::vector<std::vector<colorChar>> currentFrame;
	std::vector<colorChar> currentLine;

	while(file.get(current.character)){
		if(current.character == '\033'){
			file.get(current.character);
			std::string colorS;
			for(file.get(current.character); current.character != 'm'; file.get(current.character)){
				colorS += current.character;
			}
			current.color = std::stoi(colorS);
		}
		else if(current.character == '\n'){
			if(lastNew){
				output.push_back(currentFrame);
				currentFrame.clear();
			}
			else{
				currentFrame.push_back(currentLine);
				currentLine.clear();
			}
			lastNew = true;
		}
		else{
			lastNew = false;
			currentLine.push_back(current);
		}
	}

    if(currentLine.size() > 0){
        currentFrame.push_back(currentLine);
    }
    if(currentFrame.size() > 0){
        output.push_back(currentFrame);
    }

	return output;
}

static bool checkFile(std::vector<std::vector<std::vector<colorChar>>> file, std::string fileType, std::string fileName){
    if(file.size() == 0 || file[0].size() == 0 || file[0][0].size() == 0){
        std::cout << fileType << ' '<< fileName << " does not exsist or has no size\n";
        return false;
    }

    for(int f = 0; f < file.size(); f++){
        if(file[f].size() != file[0].size()){
            std::cout << fileType << ' ' << fileName << " mismatching number of lines per frame\n";
            return false;
        }
        for(int y = 0; y < file[f].size(); y++){
            if(file[f][y].size() != file[0][0].size()){
                std::cout << fileType << ' ' << fileName << " mismatching number of charcters per line\n";
                return false;
            }
        }
    }
    return true;
}
