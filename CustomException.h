
#ifndef TV_SHOWS_CONSOLE_APP_CUSTOMEXCEPTION_H
#define TV_SHOWS_CONSOLE_APP_CUSTOMEXCEPTION_H
#include <iostream>
#include <string>
using namespace std;
class CustomException {
private:
    string message;
public:
    CustomException(string message) {this->message=message;}
    CustomException(){}
    string getMessage(){
        return message;
    }
};


#endif //TV_SHOWS_CONSOLE_APP_CUSTOMEXCEPTION_H
