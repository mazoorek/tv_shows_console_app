#ifndef TV_SHOWS_CONSOLE_APP_LIVESTREAM_H
#define TV_SHOWS_CONSOLE_APP_LIVESTREAM_H

# include "PieceOfCinematography.h"

class Livestream : public PieceOfCinematography {
private:
    int month;
    int day;
    string hour;
public:
    Livestream();

    int getMonth() const;

    void setMonth(int month);

    int getDay() const;

    void setDay(int day);

    string getHour() const;

    void setHour(string hour);

    void showOptions() override {
        PieceOfCinematography::showOptions();
        cout << "(8)month" << endl;
        cout << "(9)day" << endl;
        cout << "(10)hour" << endl;
    }

    void edit(int optionNumber, bool &endOfEditing) override {
        try {
            string inputValue = "";
            PieceOfCinematography::edit(optionNumber, endOfEditing);
            if (optionNumber == 8) {
                int newMonth;
                cout << "Set new month:" << endl;
                cin >> inputValue;
                newMonth = atoi(inputValue.c_str());
                if (newMonth < 1 || newMonth > 12) { throw CustomException("Invalid month"); }
                setMonth(newMonth);
            } else if (optionNumber == 9) {
                int newDay;
                cout << "Set new day:" << endl;
                cin >> inputValue;
                newDay = atoi(inputValue.c_str());
                if (newDay < 1 || newDay > 31) throw CustomException("Invalid day");
                setMonth(newDay);
            } else if (optionNumber == 10) {
                string newHour;
                cout << "Set new hour:" << endl;
                cin >> newHour;
                if (newHour.size() > 5 || atoi(newHour.substr(0, 2).c_str()) > 23 ||
                    atoi(newHour.substr(3, 2).c_str()) > 59 || newHour[2] != ':') {
                    throw CustomException("Invalid hour");
                }
                setHour(newHour);
            }
        } catch (CustomException &e) {
            cout << e.getMessage() << endl;
        }
    }

    void getData(vector<string> data) override {
        PieceOfCinematography::getData(data);
        int month = atoi(data[8].c_str());
        setMonth(month);
        int day = atoi(data[9].c_str());
        setDay(day);
        string hour = data[10];
        setHour(hour);
    }

    ~Livestream() override = default;
};


#endif //TV_SHOWS_CONSOLE_APP_LIVESTREAM_H
