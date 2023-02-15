#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <string>

namespace filemanager {
    std::string getCurrentDirectory();
    std::vector<std::string> listFilesFrom(const std::string &path, const std::string extension = "*");
    std::vector<unsigned char> readFileBinary(const std::string &filepath);
}

#endif
