#ifndef SENECA_FILESYSTEM_H
#define SENECA_FILESYSTEM_H

#include "Directory.h"
#include <string>

namespace seneca {
    class Filesystem {
    private:
        Directory* root;
        Directory* current;

        std::string trim_string(const std::string& str);

    public:
        Filesystem(const std::string& fileName, const std::string& rootName = "");

        Filesystem& operator+=(Resource* resource);

        Directory* change_directory(const std::string& dirName = "");

        Directory* get_current_directory() const;

        ~Filesystem();

        Filesystem(const Filesystem&) = delete;
        Filesystem& operator=(const Filesystem&) = delete;

        Filesystem(Filesystem&&) noexcept;
        Filesystem& operator=(Filesystem&&) noexcept;
    };
} // namespace seneca

#endif // SENECA_FILESYSTEM_H
