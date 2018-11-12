#include "Livestream.h"

Livestream::Livestream() : PieceOfCinematography() {
    this->numberOfOptions=numberOfOptions+=3;
}

int Livestream::getMonth() const {
    return month;
}

void Livestream::setMonth(int month) {
    this->month = month;
}

int Livestream::getDay() const {
    return day;
}

void Livestream::setDay(int day) {
    this->day = day;
}

string Livestream::getHour() const {
    return hour;
}

void Livestream::setHour(string hour) {
    this->hour = hour;
}



