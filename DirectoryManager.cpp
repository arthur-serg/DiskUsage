#include "DirectoryManager.hpp"

size_t DirectoryManager::getFileBlocks(const std::filesystem::path& path) const
{

}

size_t DirectoryManager::getFileSize(const std::filesystem::path& path) const
{
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
