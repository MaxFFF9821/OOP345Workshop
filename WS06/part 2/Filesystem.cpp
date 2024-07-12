//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
//Name: Max Feng
//Student ID:136141231
//Date:2024/07/05
#include "Filesystem.h"
#include "File.h"
#include <fstream>
#include <vector>
#include <stdexcept>

namespace seneca {
    std::string Filesystem::trim_string(const std::string& str) {
        size_t start = str.find_first_not_of(" \r\n\t");
        size_t end = str.find_last_not_of(" \r\n\t");

        if (start == std::string::npos) start = 0;
        if (end == std::string::npos) end = str.length() - 1;

        return str.substr(start, end - start + 1);
    }

    Filesystem::Filesystem(const std::string& fileName, const std::string& rootName) {
        root = new Directory(rootName);
        current = root;

        std::ifstream file(fileName);
        if (!file) {
            delete root;
            root = nullptr;
            throw std::runtime_error("Cannot open file.");
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) {
                continue;
            }

            size_t pos = line.find_first_of('|');
            bool isDir = pos == std::string::npos;

            std::string dirName = isDir ? trim_string(line) : trim_string(line.substr(0, pos));

            std::vector<std::string> paths;
            size_t start = 0;
            while (start < dirName.length()) {
                size_t end = dirName.find_first_of('/', start);
                if (end == std::string::npos) {
                    paths.push_back(trim_string(dirName.substr(start)));
                    break;
                }
                paths.push_back(trim_string(dirName.substr(start, end - start + 1)));
                start = end + 1;
            }

            for (const std::string& path : paths) {
                Resource* res = current->find(path);

                if (res) {
                    if (res->type() == NodeType::DIR) {
                        current = dynamic_cast<Directory*>(res);
                    } else {
                        throw std::runtime_error("File " + path + " already exists!");
                    }
                } else {
                    if (isDir || &path != &paths.back()) {
                        Directory* newDir = new Directory(path);
                        newDir->update_parent_path(current->path());
                        *current += newDir;
                        current = newDir;
                    } else {
                        File* newFile = new File(path, trim_string(line.substr(pos + 1)));
                        newFile->update_parent_path(current->path());
                        *current += newFile;
                    }
                }
            }
            current = root;
        }
    }

    Filesystem::Filesystem(Filesystem&& other) noexcept : root(other.root), current(other.current) {
        other.root = nullptr;
        other.current = nullptr;
    }

    Filesystem& Filesystem::operator=(Filesystem&& other) noexcept {
        if (this != &other) {
            delete root;
            root = other.root;
            current = other.current;
            other.root = nullptr;
            other.current = nullptr;
        }
        return *this;
    }

    Filesystem& Filesystem::operator+=(Resource* resource) {
        *current += resource;
        return *this;
    }

    Directory* Filesystem::change_directory(const std::string& dirName) {
        if (dirName.empty()) {
            current = root;
            return current;
        }
        Resource* res = current->find(dirName);
        if (!res || res->type() != NodeType::DIR) {
            throw std::invalid_argument("Cannot change directory! " + dirName + " not found!");
        }
        current = dynamic_cast<Directory*>(res);
        return current;
    }

    Directory* Filesystem::get_current_directory() const { return current; }

    Filesystem::~Filesystem() {
        delete root;
    }
} // namespace seneca
