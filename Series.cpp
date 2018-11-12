#include "Series.h"

Series::Series() : PieceOfCinematography() {
    this->numberOfOptions=numberOfOptions+=1;
}

int Series::getYearTheShowEnded() const {
    return yearTheShowEnded;
}

int Series::getNumberOfSeasons() const {
    return numberOfSeasons;
}

void Series::setYearTheShowEnded(int yearTheShowEnded) {
    this->yearTheShowEnded = yearTheShowEnded;
}

void Series::setNumberOfSeasons(int numberOfSeasons) {
    this->numberOfSeasons = numberOfSeasons;
}




