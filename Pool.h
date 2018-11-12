
#ifndef TV_SHOWS_CONSOLE_APP_POOL_H
#define TV_SHOWS_CONSOLE_APP_POOL_H
#include "OperationsOnListOfPiecesOfCinematography.h"
#include <cstdlib>
class Pool {
private:
    vector <PieceOfCinematography*> list;
    vector <string> typesOfCinematography;
    vector <string> filenames;
    vector <PieceOfCinematography*> followedPieces;
public:
    void showMenu();
    void chooseMenuOption(char option);
    void menu();
    void loadPool(vector <string> filenames);
    void adding();
    void editing();
    void deleting(vector <PieceOfCinematography*> &pieces);
    void recommendations();
    void filtering();
    void savePool();
    const vector<string> &getTypesOfCinematography() const;
    void setTypesOfCinematography(const vector<string> &typesOfCinematography);
    const vector<string> &getFilenames() const;
    void setFilenames(const vector<string> &filenames);
    void setFilmRanking();
    void showFilterOptions();
    void chooseFilterOption(char option, bool& endOfFiltering);
    void manageFollowedPieces();
    void chooseManageOption(char option, bool &endOfManaging);
    void showManageOptions();
    void loadFollowedPieces();
    void operator+=(vector <string> filenames) {
        loadPool(filenames);
    }
    Pool();
    ~Pool();

};


#endif //TV_SHOWS_CONSOLE_APP_POOL_H
