#include "DirectoryManager.hpp"

void DirectoryManager::printInfo()
{
    size_t totalSize = lookupDir(argsParser.getPath(), 0);

    if (argsParser.needPrintTotal())
    {
        std::cout << totalSize << "\t" << argsParser.getPath().string() << std::endl;
    }
}

size_t DirectoryManager::getFileBlocks(const std::filesystem::path& path) const
{
    size_t sizeOfFile = getFileSize(path);
    return static_cast<size_t>(std::ceil(static_cast<double>(sizeOfFile) / blockSizeInBytes));
}

size_t DirectoryManager::getFileSize(const std::filesystem::path& path) const
{
    if (std::filesystem::is_regular_file(path))
    {
        size_t size = std::filesystem::file_size(path);
        std::cout << "File: " << path.string() << ", Size: " << size << " bytes" << std::endl;
        return size;
    }
    if (std::filesystem::is_directory(path))
    {
        size_t size = 0;
        for (const auto& item : std::filesystem::directory_iterator(path))
        {
            if (std::filesystem::is_regular_file(item.path()))
            {
                size_t fileSize = std::filesystem::file_size(item.path());
                std::cout << "File: " << item.path().string() << ", Size: " << fileSize << " bytes" << std::endl;
                size += fileSize;
            }
            else if (std::filesystem::is_directory(item.path()))
            {
                size += getFileSize(item.path());
            }
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
                ThreadPool threadPool(std::thread::hardware_concurrency());
                std::vector<std::pair<size_t, std::string>> fileSizes;
                for (const auto& item : std::filesystem::directory_iterator(path))
                {
                    if (std::filesystem::is_directory(item.path()))
                    {
                        threadPool.enqueue([&]()
                        {
                            totalSize += lookupDir(item.path(), depth - 1);
                        });
                    }

                    if (argsParser.needPrintEachFileInfo() && !std::filesystem::is_directory(item.path()))
                    {
                        if (argsParser.needPrintInBytes())
                        {
                            size_t size = getFileSize(item.path());
                            std::cout << size << "\t" << item.path().string() << std::endl;
                            fileSizes.emplace_back(size, item.path().string());
                            totalSize += size;
                        }
                        else
                        {
                            size_t size = getFileSize(item.path()) / blockSizeInBytes;
                            std::cout << size << "\t" << item.path().string() << std::endl;
                            fileSizes.emplace_back(size, item.path().string());
                            totalSize += size;
                        }
                    }
                }
                for (const auto& fileInfo : fileSizes)
                {
                    std::cout << fileInfo.first << "\t" << fileInfo.second << std::endl;
                }
            }
        }
    }

    return totalSize;
}
