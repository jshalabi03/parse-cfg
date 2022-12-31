#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <string>
#include <vector>
#include "CFG.h"

// return vector of lines in file
std::vector<std::string> readLines(std::string filename);

// THE FOLLOWING ARE FOR USE IN CLEANING ASM CODE

// returns true if line is a comment
bool isComment(std::string line);
// returns true if line is a label
bool isLabel(std::string line);
// extracts ".LBB2_1" from ".LBB2_1:"
std::string getLabel(std::string line);
// returns true if line is a jump instruction
bool isJumpInstruction(std::string line);

// extracts "b" from "	b	LBB2_1"
// extracts "cbnz" from "	cbnz	w8, LBB2_4"
std::string getInstruction(std::string line);

// extracts "LBB2_1" from "	b	LBB2_1"
// extracts "LBB2_4" from "	cbnz	w8, LBB2_4"
std::string getJumpDestination(std::string line);

#endif