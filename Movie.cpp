#include "Movie.h"

Movie::Movie() : PieceOfCinematography() {}

int Movie::getImdbRanking() const {
    return imdbRanking;
}

void Movie::setImdbRanking(int imdbRanking) {
    this->imdbRanking = imdbRanking;
}


