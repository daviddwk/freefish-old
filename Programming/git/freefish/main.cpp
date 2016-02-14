#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ostream>
#include <unistd.h>
#include <random>
#include <time.h>
#include <stdexcept>
#include "ColorChar.h"
#include "Fish.h"
#include "ReadFile.h"

void help(){
    std::cout << "--help    -h  displays this help menu\n";
    std::cout << "--list    -l  lists avaliable fish and tanks\n";
    std::cout << "--speed   -s  sets the legnth of each frame in microseconds\n";
    std::cout << "--tank    -t  uses single following argument as fishtank file\n";
    std::cout << "--fish    -f  uses following arguments as fish foiles\n              typing a fish multiple times will load it multiple times\n";
}

int main(int argc, char* argv[]){

    srand(time(NULL));

    std::vector<Fish> fishies;
    std::vector<std::vector<std::vector<colorChar>>> background;
    std::vector<std::vector<std::vector<colorChar>>> foreground;

    int frameSpeed = 250000;

    if(argc == 1){
        help();
        return 0;
    }
    for(int i = 1; i < argc; i++){
        if(std::string(argv[i]) == "--help" || std::string(argv[i]) == "-h"){
            help();
            return 0;
        }
        else if(std::string(argv[i]) == "--list" || std::string(argv[i]) == "-l"){
            std::cout << "fish\n\n";
            system("ls /usr/share/freefish/fish");
            std::cout << "\ntanks\n\n";
            system("ls /usr/share/freefish/background");
            std::cout <<"\nthis function does not check for errors, missing flips, or missing foreground\n";
            return 0;
        }
        else if(std::string(argv[i]) == "--speed" || std::string(argv[i]) == "-s"){
            i++;
            if(i < argc){
                try{
                    frameSpeed = std::stoi(std::string(argv[i]));
                }
                catch(std::invalid_argument e){
                    std::cout << "speed not a valid integer\n";
                    return 0;
                }
            }
            else{
            help();
            return 0;
            }
        }
        else if(std::string(argv[i]) == "--tank" || std::string(argv[i]) == "-t" ){
            i++;
            if(i < argc){
                std::string input(argv[i]);
                background = readFile("/usr/share/freefish/background/" + input);
                foreground = readFile("/usr/share/freefish/foreground/" + input);
                if(!checkFile(background, "background", input) || !checkFile(foreground, "foreground", input)){
                    return 0;
                }
                if(background[0].size() != foreground[0].size() || background[0][0].size() != foreground[0][0].size()){
                    std::cout << "tank " << input << " mismatching background and foreground sizes\n";
                    return 0;
                }
            }
            else{
                help();
                return 0;
            }
        }
        else if(std::string(argv[i]) == "--fish" || std::string(argv[i]) == "-f"){
            Fish fish;
            i++;
            while(argc > i && argv[i][0] != '-'){
                std::string input(argv[i]);
                if(!fish.load("/usr/share/freefish/fish/" + input, "/usr/share/freefish/flip/" + input, input)){
                    return 0;
                }
                fishies.push_back(fish);
                i++;
            }
            i--;
        }
        else{
            help();
            return 0;
        }
    }
    if(background.size() == 0){
        help();
        return 0;
    }

    for(int i = 0; i < fishies.size(); i++){
        if (!fishies[i].init(background[0].size(), background[0][0].size())){
            return 0;
        }
    }

    bool fishThere = false;
    int backgroundFrame = 0;
    int foregroundFrame = 0;

    system("clear");

    while(true){
        for(int y = 0; y < background[backgroundFrame].size(); y++){
                //std::cout << y;
            for(int x = 0; x < background[backgroundFrame][y].size(); x++){
                if(foreground[foregroundFrame][y][x].character != ' '){
                    std::cout << foreground[foregroundFrame][y][x];
                }
                else{
                    fishThere = false;
                    for(int f = 0; f < fishies.size(); f++){
                        Fish fish = fishies[f];
                        if(!fish.flip && x >= fish.x && x < fish.x + fish.width && y >= fish.y && y < fish.y + fish.height && fish.fishChars[fish.frame][y - fish.y][x - fish.x].character != ' '){
                            fishThere = true;
                            std::cout << fish.fishChars[fish.frame][y-fish.y][x-fish.x];
                            break;
                        }
                        if(fish.flip && x >= fish.x && x < fish.x + fish.width && y >= fish.y && y < fish.y + fish.height && fish.flipChars[fish.frame][y - fish.y][x - fish.x].character != ' '){
                            fishThere = true;
                            std::cout << fish.flipChars[fish.frame][y-fish.y][x-fish.x];
                            break;
                        }
                    }
                    if(!fishThere){
                        std::cout << background[backgroundFrame][y][x];
                    }
                }
            }
            std::cout << '\n';
        }
        usleep(frameSpeed);
        std::cout << "\033[1;1H";
        std::cout.flush();

        for(int i = 0; i < fishies.size(); i++){
            fishies[i].updatePosition(background[0].size(), background[0][0].size());
        }

        foregroundFrame++;
        backgroundFrame++;
        for(int i = 0; i < fishies.size(); i++){
            fishies[i].frame++;
        }

        if(foregroundFrame >= foreground.size()){
            foregroundFrame = 0;
        }
        if(backgroundFrame >= background.size()){
            backgroundFrame = 0;
        }
        for(int i = 0; i < fishies.size(); i++){
            if (fishies[i].frame >= fishies[i].fishChars.size())
                fishies[i].frame = 0;
        }
    }
    return 0;
}
