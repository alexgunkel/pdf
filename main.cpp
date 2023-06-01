#include <iostream>
#include "PdfExtractor.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 1;
    }

    try {
        PdfExtractor extractor;
        std::cout << extractor.parseFile(argv[1]);
    } catch (std::runtime_error& ex) {
        std::cerr << ex.what() << std::endl;
        return -1;
    }
    return 0;
}
