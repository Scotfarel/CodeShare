#include "headers/File.h"
#include <utility>

File::File(std::string idfile, std::string filename, std::string owner, std::string timestamp)
        : _idfile(std::move(idfile)), _timestamp(std::move(timestamp)) {}

std::string File::ToString() const {
    return getidfile() + gettimestamp();
}

std::string File::getidfile() const {
    return _idfile;
}

std::string File::gettimestamp() const {
    return _timestamp;
}
