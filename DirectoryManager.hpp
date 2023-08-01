#pragma once
#include "ArgsParser.hpp"
#include "ThreadPool.hpp"

class DirectoryManager
{
public:
    DirectoryManager(const ArgsParser& argsParser) : argsParser(argsParser)
    {
    }

    ~DirectoryManager() = default;
    void printInfo();

private:
    ArgsParser argsParser;
    int blockSizeInBytes = 512;

    size_t getFileBlocks(const std::filesystem::path& path) const;
    size_t getFileSize(const std::filesystem::path& path) const;
    size_t lookupDir(const std::filesystem::path& path, int depth) const;
};
