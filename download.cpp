
#include <iostream>
#include "Downloader.h"

int main(int argc, char **argv)
{
    if (argc < 3) {
        return 1;
    }

    Downloader downloader{argv[1]};

    const auto place = downloader.download(argv[2]);
    std::cout << place << std::endl;
    return 0;
}
