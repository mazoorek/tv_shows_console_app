#ifndef TV_SHOWS_CONSOLE_APP_SERIES_H
#define TV_SHOWS_CONSOLE_APP_SERIES_H
#include "PieceOfCinematography.h"

class Series : public PieceOfCinematography{
private:
    int yearTheShowEnded;
public:
    int getYearTheShowEnded() const;

    int getNumberOfSeasons() const;

private:
    int numberOfSeasons;
public:
    Series();
    void setYearTheShowEnded(int yearTheShowEnded);
    void setNumberOfSeasons(int numberOfSeasons);
    void showOptions() override {
        PieceOfCinematography::showOptions();
        cout<<"(8)year the show ended"<<endl;
    }
    void edit(int optionNumber, bool &endOfEditing) override {
        try {
            string inputValue="";
            PieceOfCinematography::edit(optionNumber, endOfEditing);
            if (optionNumber == 8) {
                int newYearTheShowEnded = 0;
                cout << "Set the year the show ended" << endl;
                cin >> inputValue;
                newYearTheShowEnded = atoi(inputValue.c_str());
                if (newYearTheShowEnded < 0) throw CustomException("Year the show ended can not be lower than 0");
                setYearTheShowEnded(newYearTheShowEnded);
                setNumberOfSeasons(getYearTheShowEnded() - getYearProduced() + 1);
            }
        } catch(CustomException &e){
            cout<<e.getMessage()<<endl;
        }
    }
    void getData(vector <string> data) override {
        PieceOfCinematography::getData(data);
        int yearTheShowEnded = atoi(data[8].c_str());
        setYearTheShowEnded(yearTheShowEnded);
        setNumberOfSeasons(getYearTheShowEnded()-getYearProduced()+1);
    }
    ~Series() override = default;

};


#endif //TV_SHOWS_CONSOLE_APP_SERIES_H
