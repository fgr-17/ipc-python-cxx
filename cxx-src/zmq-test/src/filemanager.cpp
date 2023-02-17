#include "filemanager.h"
#include <vector>
#include <string>
#include <fstream>
#include <unistd.h>
#include <dirent.h>

namespace  filemanager {
    std::string getCurrentDirectory() {
        char tmp[256];
        return getcwd(tmp, 256);
    }

    std::vector<std::string> listFilesFrom(const std::string &path, const std::string extension) {
        std::vector<std::string> files;
        std::string fullpath = path;
        if (path[0] != '/') {
            fullpath = getCurrentDirectory() + std::string("/") + path;
        }
        DIR *dirp = opendir(fullpath.c_str());
        struct dirent *dp;
        while ((dp = readdir(dirp)) != NULL) {
            std::string filename(dp->d_name);
            std::string fileext(filename.substr(filename.rfind(".") + 1));
            if (extension == "*" || fileext == extension) {
                files.push_back(dp->d_name);
            }
        }

        return files;
    }

    std::vector<unsigned char> readFileBinary(const std::string &filepath) {
        std::ifstream input(filepath, std::ios::binary);
        return std::vector<unsigned char>(std::istreambuf_iterator<char>(input), {});
    }
}


