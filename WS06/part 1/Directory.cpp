#include "Directory.h"

namespace seneca {
    Directory::Directory(const std::string& dirName) {
        m_name = dirName;
    }

    void Directory::update_parent_path(const std::string& parentPath) {
        m_parent_path = parentPath;
        for (Resource* entry : m_entries) {
            entry->update_parent_path(path());
        }
    }

    NodeType Directory::type() const {
        return NodeType::DIR;
    }

    std::string Directory::path() const {
        return m_parent_path + m_name;
    }

    std::string Directory::name() const {
        return m_name;
    }

    int Directory::count() const {
        return static_cast<int>(m_entries.size());
    }

    size_t Directory::size() const {
        size_t totalSize = 0;
        for (const Resource* entry : m_entries) {
            totalSize += entry->size();
        }
        return totalSize;
    }

    Directory& Directory::operator+=(Resource* resource) {
        for (const Resource* entry : m_entries) {
            if (entry->name() == resource->name()) {
                throw "Resource already exists in the directory.";
            }
        }
        resource->update_parent_path(path());
        m_entries.push_back(resource);
        return *this;
    }

    Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flags) {
        bool recursive = !flags.empty() && flags[0] == OpFlags::RECURSIVE;

        for (Resource* entry : m_entries) {
            if (entry->name() == name) {
                return entry;
            }
            if (entry->type() == NodeType::DIR && recursive) {
                Resource* found = static_cast<Directory*>(entry)->find(name, flags);
                if (found) {
                    return found;
                }
            }
        }
        return nullptr;
    }

    Directory::~Directory() {
        for (Resource* entry : m_entries) {
            delete entry;
        }
    }
} // namespace seneca
