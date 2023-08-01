#include "ArgsParser.hpp"


ArgsParser::ArgsParser(int argc, char* argv[]) noexcept
{
    auto args = argvToString(argc, argv);
    process(args);
}

ArgsParser::ArgsParser(const std::string& argv) noexcept
{
    process(argv);
}


void ArgsParser::process(const std::string& args)
{
    std::vector<std::string> params;
    std::istringstream strStream(args);

    std::vector arguments((std::istream_iterator<std::string>(strStream)),
                          std::istream_iterator<std::string>());

    for (auto it = arguments.begin(); it != arguments.end(); ++it)
    {
        if (const std::string arg = *it; isParam(arg))
        {
            params.push_back(arg);
        }
        else
        {
            dirPath = arg;
        }
    }

    for (const auto& param : params)
    {
        switch (param[1])
        {
        case 'b':
            {
                printBytes = true;
                break;
            }
        case 'a':
            {
                printEachFileInfo = true;
                break;
            }
        case 'c':
            {
                printTotal = true;
                break;
            }
        case 's':
            {
                printEachFileInfo = false;
                printTotal = true;
                break;
            }
        default:
            {
                std::cerr << "Unknown parameter" << std::endl;
                break;
            }
        }
    }
}

bool ArgsParser::isParam(const std::string& arg)
{
    return !arg.empty() && arg[0] == '-';
}

std::string ArgsParser::argvToString(int argc, char* argv[])
{
    std::string result;
    for (int i = 1; i < argc; ++i)
    {
        result += argv[i];
        if (i < argc - 1)
        {
            result += " ";
        }
    }
    return result;
}
