#include "DirectoryManager.hpp"

int main(int argc, char* argv[])
{
    auto test = "-b D:\\FinchRepos\\DiskUsage\\x64\\Release";
    auto parser = ArgsParser(test);
    auto dirManager = DirectoryManager(parser);

    dirManager.printInfo();
}
