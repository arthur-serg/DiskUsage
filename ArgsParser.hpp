#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <filesystem>
#include <sstream>

class ArgsParser
{
public:
    explicit ArgsParser(int argc, char* argv[]) noexcept;
    ~ArgsParser() noexcept = default;

private:
    const std::string args;
    std::filesystem::path dirPath;
    void process(const std::string& args);
    bool isParam(const std::string& arg);
    std::string argvToString(int argc, char* argv[]);
    bool printBytes = false;
    bool printEachFileInfo = false;
    bool printTotal = false;
};
