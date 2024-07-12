//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
//Name: Max Feng
//Student ID:136141231
//Date:2024/07/05
#include "Directory.h"
#include <iomanip>
#include <algorithm>

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

    void Directory::remove(const std::string& name, const std::vector<OpFlags>& flags) {
        auto it = std::find_if(m_entries.begin(), m_entries.end(),
            [&name](Resource* entry) { return entry->name() == name; });

        if (it == m_entries.end()) {
            throw std::string(name + " does not exist in " + m_name);
        }

        Resource* res = *it;
        if (res->type() == NodeType::DIR && std::find(flags.begin(), flags.end(), OpFlags::RECURSIVE) == flags.end()) {
            throw std::invalid_argument(name + " is a directory. Pass the recursive flag to delete directories.");
        }

        delete res;
        m_entries.erase(it);
    }

    void Directory::display(std::ostream& out, const std::vector<FormatFlags>& fmtFlags) const {
        out << "Total size: " << size() << " bytes\n";

        bool longFmt = !fmtFlags.empty() && fmtFlags[0] == FormatFlags::LONG;
        for (const Resource* res : m_entries) {
            bool isDir = res->type() == NodeType::DIR;
            
            out << (isDir ? "D | " : "F | ");
            out.width(15);
            out << std::left << res->name() << " |";

            if (longFmt) {
                out << " ";
                if (isDir) {
                    out.width(2);
                    out << std::right << res->count() << " | ";
                } else {
                    out << "   | ";
                }
                out.width(4);
                out << std::right << res->size() << " bytes | ";
            }
            out << "\n";
        }
    }

        
} 
