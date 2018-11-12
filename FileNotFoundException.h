
#ifndef TV_SHOWS_CONSOLE_APP_FILENOTFOUNDEXCEPTION_H
#define TV_SHOWS_CONSOLE_APP_FILENOTFOUNDEXCEPTION_H
#include "CustomException.h"
#include <sstream>
class FileNotFoundException : public CustomException {
private:
    std::string filename;
public:
    FileNotFoundException( string filename ){this->filename=filename;}
    string getFilename() {
        return filename;
    }
    string getMessage() {
        stringstream ss;
        ss << filename<< " not found\n";
        return ss.str();
    }
};

#endif //TV_SHOWS_CONSOLE_APP_FILENOTFOUNDEXCEPTION_H
