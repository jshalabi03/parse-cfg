#include "FileUtil.h"

#include <fstream>
#include <list>

std::vector<std::string> readLines(std::string filename) {
    std::ifstream file(filename);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

bool isComment(std::string line) {
    return line.find("//") == 0 || line.find(";") == 0;
}

bool isLabel(std::string line) {
    return line.find(":") != std::string::npos;
}

std::string getLabel(std::string line) {
    return line.substr(0, line.find(":"));
}

bool isJumpInstruction(std::string line) {
    std::string instruction = getInstruction(line);
    if (instruction.find("cb") == 0) { return true; }
    if (instruction.find("tb") == 0) { return true; }
    return instruction.find("b") == 0;
}

std::string getInstruction(std::string line) {
    int start = line.find("\t") + 1;
    int end = line.find(" ", start);
    return line.substr(start, end - start);
}

std::string getJumpDestination(std::string line) {
    std::string instruction = getInstruction(line);
    if (instruction.find("cb") == 0 || instruction.find("tb") == 0) {
        return line.substr(line.find_last_of(' ') + 1);
    }
    return line.substr(line.find_last_of('\t') + 1);
}