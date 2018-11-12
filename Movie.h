#ifndef TV_SHOWS_CONSOLE_APP_MOVIE_H
#define TV_SHOWS_CONSOLE_APP_MOVIE_H

# include "PieceOfCinematography.h"
class Movie : public PieceOfCinematography {
private:
    int imdbRanking;
public:
    Movie();
    int getImdbRanking() const;
    void setImdbRanking(int imdbRanking);
    ~Movie() override =default;
};


#endif //TV_SHOWS_CONSOLE_APP_MOVIE_H
