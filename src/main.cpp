#include <iostream>
#include <unistd.h>
#include "CFG.h"

using namespace std;

int main(int argc, char *argv[]) {

    int option;
    std::string input_path;
    std::string output_path;
    while ((option = getopt(argc, argv, "f:o:")) != -1) {
        switch (option) {
            case 'f':
                input_path = optarg;
                break;
            case 'o':
                output_path = optarg;
                break;
            default:
                cout << "Usage: " << argv[0] << " -f <input file> -o <output file>" << endl;
                exit(EXIT_FAILURE);
        }
    }

    int result;
    std::string command;

    command = "clang++ -S -mllvm --x86-asm-syntax=intel -o data/index.s " + input_path;
    result = std::system(command.c_str());
    if (result != 0) {
        cout << "Invalid input: '" << input_path << "' must be a valid C++ source file." << endl;
        exit(EXIT_FAILURE);
    }

    CFG cfg("data/index.s");
    cfg.toDot(output_path);

    return 0;
}