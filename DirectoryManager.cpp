#include "DirectoryManager.hpp"

size_t DirectoryManager::getFileBlocks(const std::filesystem::path& path) const
{

size_t DirectoryManager::getFileBlocks(const std::filesystem::path& path) const
{
    size_t sizeOfFile = getFileSize(path);
    return static_cast<size_t>(std::ceil(static_cast<double>(sizeOfFile) / blockSizeInBytes));
}

size_t DirectoryManager::getFileSize(const std::filesystem::path& path) const
{
    if (std::filesystem::is_regular_file(path))
    {
        return std::filesystem::file_size(path);
    }
    else if (std::filesystem::is_directory(path))
    {
        size_t size = 0;
        for (const auto& item : std::filesystem::directory_iterator(path))
        {
            size += getFileSize(item.path());
        }

        return size;
    }

    return 0;
}

size_t DirectoryManager::lookupDir(const std::filesystem::path& path, int depth) const
{
    size_t totalSize = 0;
    if (std::filesystem::exists(path))
    {
        if (depth >= 0)
        {
            totalSize = argsParser.needPrintInBytes() ? getFileSize(path) : getFileBlocks(path);

            if (std::filesystem::is_directory(path))
            {
                for (const auto& item : std::filesystem::directory_iterator(path))
                {
                    totalSize += lookupDir(item.path(), depth - 1);
                }
            }
        }
    }

    if (argsParser.needPrintEachFileInfo())
    {
        std::cout << totalSize << " " << path.string() << std::endl;
    }

    return totalSize;
}
