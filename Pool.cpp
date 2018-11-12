#include "Pool.h"
#include "FileNotFoundException.h"
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>

Pool::Pool() {
    typesOfCinematography = {"movie", "series", "livestream"};
}

void Pool::showMenu() {
    cout << "MENU:" << endl << endl;
    cout << "(1)Add a piece of cinematography" << endl;
    cout << "(2)Edit a piece of cinematography" << endl;
    cout << "(3)Delete a piece of cinematography" << endl;
    cout << "(4)Show all pieces of cinematography" << endl;
    cout << "(5)Show recommendations" << endl;
    cout << "(6)Filter pieces of cinematography" << endl;
    cout << "(7)Manage the pieces of cinematography that you follow" << endl;
    cout << "(8)Save pool and exit the application" << endl << endl;
}

void Pool::chooseMenuOption(char option) {
    switch (option) {
        case '1':
            adding();
            break;
        case '2':
            editing();
            break;
        case '3':
            deleting(list);
            break;
        case '4':
            OperationsOnListOfPiecesOfCinematography<>::showingPool(list);
            break;
        case '5':
            recommendations();
            break;
        case '6':
            filtering();
            break;
        case '7':
            manageFollowedPieces();
            break;
        case '8':
            savePool();
            exit(0);
        default:
            cin.ignore(1000,'\n');
            cout << "wrong option" << endl;
    }
}

void Pool::menu() {
    while (true) {
        showMenu();
        cout << "Choose option from 1 to 8" << endl;
        char option;
        cin >> option;
        cin.ignore(1000,'\n');
        chooseMenuOption(option);
    }
}

Pool::~Pool(){
    std::vector<PieceOfCinematography*>::iterator it;
    for(it = list.begin(); it != list.end(); ++it) {
        delete *it;
    }
}

void Pool::adding() {
    string type = "";
    while (true) {
        cout << "which type of piece of cinematography would you like to add?" << endl << endl;
        cout << "possible types are:" << endl;
        for (const auto &i : typesOfCinematography) {
            cout << i << endl;
        }
        cout << endl << "type one of them:" << endl;
        cin >> type;
        if (type == "movie") {
            Movie *piece = new Movie();
            OperationsOnListOfPiecesOfCinematography<Movie>::addPiece(piece, list);
            setFilmRanking();
            break;
        } else if (type == "series") {
            Series *piece = new Series();
            OperationsOnListOfPiecesOfCinematography<Series>::addPiece(piece, list);
            break;
        } else if (type == "livestream") {
            Livestream *piece = new Livestream();
            OperationsOnListOfPiecesOfCinematography<Livestream>::addPiece(piece, list);
            break;
        } else {
            cout << "wrong type!" << endl << endl;
        }
    }
    savePool();
}

void Pool::editing() {
    string inputId;
    int index = -1;
    while (index == -1) {
        cout << "Type id of a piece you wish to edit:" << endl;
        cin >> inputId;
        int id = atoi(inputId.c_str());
        index = OperationsOnListOfPiecesOfCinematography<>::searchForIndexById(id, list);
        if (index == -1) {
            cout << "There is no such an id in the pool" << endl;
        } else {
            OperationsOnListOfPiecesOfCinematography<>::editPiece(index, list);
        }
    }
    setFilmRanking();
    savePool();
}

void Pool::deleting(vector<PieceOfCinematography*> &pieces) {
    if (pieces.empty()) {
        cout << "there are no elements in list to delete" << endl;
        return;
    }
    string inputId;
    int index = -1;
    while (index == -1) {
        cout << "Type an id of a piece you wish to delete:" << endl;
        cin >> inputId;
        int id = atoi(inputId.c_str());
        index = OperationsOnListOfPiecesOfCinematography<>::searchForIndexById(id, pieces);
        if (index == -1) {
            cout << "There is no an id in the pool" << endl;
        } else {
            OperationsOnListOfPiecesOfCinematography<>::delPiece(index, pieces);
        }
    }

}

void Pool::recommendations() {
    cout<<setw(10)<<"Id";
    cout<<setw(80)<<"Title";
    cout<<setw(10)<<"Rating";
    cout<<setw(20)<<"Number of Votes";
    cout<<endl;
    vector<PieceOfCinematography *> recommendationList = list;
    sort(recommendationList.begin(), recommendationList.end(),
         OperationsOnListOfPiecesOfCinematography<>::sortByRating);
    for (int i = 0; i < recommendationList.size(); i++) {
        if (i >= 10) break;
        cout<<setw(10)<<recommendationList[i]->getId();
        cout<<setw(80)<<recommendationList[i]->getTitle();
        cout<<setw(10)<<recommendationList[i]->getRating();
        cout<<setw(20)<<recommendationList[i]->getNumberOfVotes();
        cout<<endl;
    }
}

void Pool::savePool() {
    for (const auto &filename : filenames) {
        ofstream file;
        file.open(filename);
        for (const auto &piece : list) {
            if (filename == "movies.txt") {
                if (OperationsOnListOfPiecesOfCinematography<>::instanceof<Movie>(piece)) {
                    Movie *m = dynamic_cast<Movie *>(piece);
                    file << fixed << setprecision(1) << m->getRating() << '\t' << m->getNumberOfVotes() << '\t';
                    file << m->getTitle() << '\t'<< m->getYearProduced() << '\t' << m->getDuration() << '\t';
                    const vector<string> &genres = m->getGenres();
                    for (int i = 0; i < genres.size(); i++) {
                        if (i == genres.size() - 1) file << genres[i] << '\t';
                        else file << genres[i] << ',';
                    }
                    file << m->isFollowed()<<'\t';
                    file << endl;
                }
            } else if (filename == "tv_shows.txt") {
                if (OperationsOnListOfPiecesOfCinematography<>::instanceof<Series>(piece)) {
                    Series *s = dynamic_cast<Series *>(piece);
                    file << fixed << setprecision(1) << s->getRating() << '\t' << s->getNumberOfVotes() << '\t';
                    file << s->getTitle() << '\t' << s->getYearProduced() << '\t' << s->getDuration() << '\t';
                    const vector<string> &genres = s->getGenres();
                    for (int i = 0; i < genres.size(); i++) {
                        if (i == genres.size() - 1) file << genres[i] << '\t';
                        else file << genres[i] << ',';
                    }
                    file << s->isFollowed()<<'\t';
                    file << s->getYearTheShowEnded();
                    file << endl;
                }
            } else if (filename == "livestreams.txt") {
                if (OperationsOnListOfPiecesOfCinematography<>::instanceof<Livestream>(piece)) {
                    Livestream *l = dynamic_cast<Livestream *>(piece);
                    file << fixed << setprecision(1) << l->getRating() << '\t' << l->getNumberOfVotes() << '\t';
                    file << l->getTitle() << '\t' << l->getYearProduced() << '\t' << l->getDuration() << '\t';
                    const vector<string> &genres = l->getGenres();
                    for (int i = 0; i < genres.size(); i++) {
                        if (i == genres.size() - 1) file << genres[i] << '\t';
                        else file << genres[i] << ',';
                    }
                    file << l->isFollowed()<<'\t';
                    file << l->getMonth() << '\t'<<l->getDay() <<'\t' << l->getHour();
                    file << endl;
                }
            }
        }
        file.close();
    }
}

const vector<string> &Pool::getTypesOfCinematography() const {
    return typesOfCinematography;
}

void Pool::setTypesOfCinematography(const vector<string> &typesOfCinematography) {
    this->typesOfCinematography = typesOfCinematography;
}

void Pool::loadPool(vector<string> filenames) {
    setFilenames(filenames);
    int id = 1;
    for (const auto &filename : filenames) {
        try {
            ifstream file;
            file.open(filename);
            if(!file.good()) throw FileNotFoundException(filename);
            string line;
            string delimiter = "\t";
            vector<string> data;
            while (file.good()) {
                getline(file, line);
                if (line == "")break;
                int pos = 0;
                string pieceOfData;
                data.push_back(to_string(id));
                while ((pos = line.find(delimiter)) != string::npos) {
                    pieceOfData = line.substr(0, pos);
                    data.push_back(pieceOfData);
                    line.erase(0, pos + delimiter.length());
                }
                data.push_back(line);
                if (filename == "movies.txt") {
                    Movie *movie = new Movie();
                    movie->getData(data);
                    list.push_back(dynamic_cast<Movie *>(movie));
                    id++;
                } else if (filename == "tv_shows.txt") {
                    Series *series = new Series();
                    series->getData(data);
                    list.push_back(dynamic_cast<Series *>(series));
                    id++;
                } else if (filename == "livestreams.txt") {
                    Livestream *livestream = new Livestream();
                    livestream->getData(data);
                    list.push_back(dynamic_cast<Livestream *>(livestream));
                    id++;
                }
                data.clear();
            }
            file.close();
        }
        catch(FileNotFoundException &e){
            cout<<"Error: "<<e.getMessage()<<endl;
            exit(1);
        }
    }
    setFilmRanking();
    loadFollowedPieces();
}

const vector<string> &Pool::getFilenames() const {
    return filenames;
}

void Pool::setFilenames(const vector<string> &filenames) {
    Pool::filenames = filenames;
}

void Pool::setFilmRanking() {
    vector<Movie *> movieList;
    for (const auto &piece: list) {
        if (OperationsOnListOfPiecesOfCinematography<>::instanceof<Movie>(piece)) {
            movieList.push_back(dynamic_cast<Movie *>(piece));
        }
    }
    sort(movieList.begin(), movieList.end(), OperationsOnListOfPiecesOfCinematography<Movie>::sortByRating);
    for (int i = 0; i < movieList.size(); i++) {
        movieList[i]->setImdbRanking(i + 1);
    }
}

void Pool::showFilterOptions() {
    cout<<"Choose what do you wish to filter:"<<endl;
    cout<<"(1)Show average time you need to spend on piece of cinematography(in minutes)."<<endl;
    cout<<"(2)Show future livestreams."<<endl;
    cout<<"(3)Sort the pieces of cinematography by rating(descending)."<<endl;
    cout<<"(4)Finish filtering."<<endl;
}

void Pool::filtering() {
    bool endOfFiltering = false;
    while(!endOfFiltering){
        showFilterOptions();
        cout << "Choose option from 1 to 4" << endl;
        char option;
        cin >> option;
        cin.ignore(1000,'\n');
        chooseFilterOption(option,endOfFiltering);
    }
}
void Pool::chooseFilterOption(char option, bool& endOfFiltering) {
    switch (option) {
        case '1':
            OperationsOnListOfPiecesOfCinematography<>::showAverageTime(list);
            break;
        case '2':
            OperationsOnListOfPiecesOfCinematography<>::showFutureLivestreams(list);
            break;
        case '3': {
            vector<PieceOfCinematography *> listByRating = list;
            sort(listByRating.begin(), listByRating.end(),
                 OperationsOnListOfPiecesOfCinematography<>::sortByRating);
            OperationsOnListOfPiecesOfCinematography<>::showingPool(listByRating);
            break;
        }
        case '4':
            endOfFiltering = true;
            break;
        default:
            cout << "wrong option" << endl;
    }
}

void Pool::chooseManageOption(char option, bool &endOfManaging) {
    switch (option) {
        case '1':{
            int id;
            int index = -1;
            bool alreadyFollowed = false;
            while (index == -1) {
                cout << "Type an id of a piece you wish to delete:" << endl;
                cin >> id;
                index = OperationsOnListOfPiecesOfCinematography<>::searchForIndexById(id, list);
                if (index == -1) {
                    cout << "There is no such an id in the pool" << endl;
                }
                else {
                    for(const auto &piece:followedPieces){
                        if(piece->getId()==id){
                            cout<<"piece already followed"<<endl;
                            alreadyFollowed=true;
                        }
                    }
                    if(!alreadyFollowed) {
                        list[index]->setFollowed(true);
                        followedPieces.push_back(list[index]);
                    }
                }
            }
            break;
        }
        case '2':
            deleting(followedPieces);
            break;
        case '3':
            if(!followedPieces.empty()) OperationsOnListOfPiecesOfCinematography<>::showingPool(followedPieces);
            else cout<<"The list of followed pieces is empty"<<endl<<endl;
            break;
        case '4':
            endOfManaging = true;
            break;
        default:
            cout << "wrong option" << endl;
    }
}

void Pool::showManageOptions() {
    cout<<"(1)Add to followed pieces of cinematography"<<endl;
    cout<<"(2)Remove from followed pieces of cinematography"<<endl;
    cout<<"(3)Show list of followed pieces of cinematography"<<endl;
    cout<<"(4)Exit managing."<<endl;
}

void Pool::manageFollowedPieces() {
    bool endOfManaging = false;
    while(!endOfManaging){
        showManageOptions();
        cout << "Choose option from 1 to 4" << endl;
        char option;
        cin >> option;
        cin.ignore(1000,'\n');
        chooseManageOption(option,endOfManaging);
    }
}

void Pool::loadFollowedPieces() {
    for(const auto &piece:list){
        if (piece->isFollowed()) followedPieces.push_back(piece);
    }
}
