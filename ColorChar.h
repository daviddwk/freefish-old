#pragma once
#include <string>
#include <iostream>


struct colorChar{
    char color;
    char character;
};

static std::ostream& operator<<(std::ostream& os, const colorChar c) {
    return os << "\033[" << std::to_string((int)c.color) << "m" << c.character;
}
