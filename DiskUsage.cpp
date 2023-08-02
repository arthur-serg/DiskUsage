#include "DirectoryManager.hpp"

int main(int argc, char* argv[])
{
    auto parser = ArgsParser(argc, argv);
    auto dirManager = DirectoryManager(parser);

    dirManager.printInfo();
}
