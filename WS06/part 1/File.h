#ifndef SENECA_FILE_H
#define SENECA_FILE_H

#include "Resource.h"
#include "Flags.h"
#include <string>

namespace seneca {
    class File : public Resource {
            std::string m_content;
        public:
            File(const std::string &name, const std::string &content = "");

            void update_parent_path(const std::string &path) override;

            NodeType type() const override;

            std::string name() const override;

            std::string path() const override;

            int count() const override;
            
            size_t size() const override;
    };
}

#endif