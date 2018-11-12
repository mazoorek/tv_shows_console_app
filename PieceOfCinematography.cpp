#include "PieceOfCinematography.h"

PieceOfCinematography::PieceOfCinematography(){
    numberOfOptions = 7;
}

int PieceOfCinematography::getDuration() const {
    return duration;
}

void PieceOfCinematography::setDuration(int duration) {
    this->duration = duration;
}

double PieceOfCinematography::getRating() const {
    return rating;
}

void PieceOfCinematography::setRating(double rating) {
    this->rating = rating;
}

string PieceOfCinematography::getTitle() const {
    return title;
}
void PieceOfCinematography::setTitle(string title) {
    this->title = title;
}

const vector<string> &PieceOfCinematography::getGenres() const {
    return genres;
}

void PieceOfCinematography::setGenres(const vector<string> &genres) {
    this->genres = genres;
}

int PieceOfCinematography::getNumberOfVotes() const {
    return numberOfVotes;
}
void PieceOfCinematography::setNumberOfVotes(int numberOfVotes){
    this->numberOfVotes=numberOfVotes;
}

int PieceOfCinematography::getYearProduced() const {
    return yearProduced;
}

void PieceOfCinematography::setYearProduced(int yearProduced) {
    this->yearProduced=yearProduced;
}

int PieceOfCinematography::getId() const {
    return id;
}

void PieceOfCinematography::setId(int id) {
    this->id = id;
}

bool PieceOfCinematography::isFollowed() const {
    return followed;
}

void PieceOfCinematography::setFollowed(bool followed) {
    this->followed = followed;
}


PieceOfCinematography::~PieceOfCinematography() = default;






