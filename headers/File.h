#ifndef HEADERS_FILE_H_
#define HEADERS_FILE_H_

#include <string>

class File {
 private:
    std::string _idfile;
    std::string _timestamp;
 public:
    File(std::string idfile, std::string filename, std::string owner, std::string timestamp);
    std::string ToString() const;
    std::string getidfile() const;
    std::string gettimestamp() const;
};
#endif  // HEADERS_FILE_H_
