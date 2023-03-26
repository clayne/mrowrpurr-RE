#pragma once

#include <filesystem>
#include <string>

namespace ModdingFramework::Runtime {

    class Mod {
        std::string           _name;
        std::string           _version;
        std::string           _type;
        std::string           _source;
        std::filesystem::path _path;
        bool                  _loaded = true;

    public:
        Mod(const std::string& name, const std::string& version, const std::string& type,
            const std::string& source, const std::filesystem::path& path)
            : _name(name), _version(version), _type(type), _source(source), _path(path) {}

        const std::string&           GetName() const { return _name; }
        const std::string&           GetVersion() const { return _version; }
        const std::string&           GetType() const { return _type; }
        const std::string&           GetSource() const { return _source; }
        const std::filesystem::path& GetPath() const { return _path; }
        bool                         IsLoaded() const { return _loaded; }
        void                         SetLoaded(bool loaded = true) { _loaded = loaded; }
    };
}
