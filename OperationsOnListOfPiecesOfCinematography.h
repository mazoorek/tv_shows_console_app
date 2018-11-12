#ifndef TV_SHOWS_CONSOLE_APP_LISTOFPIECESOFCINEMATOGRAPHY_H
#define TV_SHOWS_CONSOLE_APP_LISTOFPIECESOFCINEMATOGRAPHY_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include "PieceOfCinematography.h"
#include "Movie.h"
#include "Series.h"
#include "Livestream.h"
#include "CustomException.h"

using namespace std;

template<class T = PieceOfCinematography>
class OperationsOnListOfPiecesOfCinematography {
public:
    OperationsOnListOfPiecesOfCinematography() = default;

    template<typename Base, typename U>
    static bool instanceof(const U *ptr) {
        return dynamic_cast<const Base *>(ptr) != nullptr;
    }

    static int searchForIndexById(int id, vector<T *> list) {
        for (int i = 0; i < list.size(); i++) {
            if (list[i]->getId() == id) {
                return i;
            }
        }
        return -1;
    }
    static void addPiece(T *piece, vector<PieceOfCinematography *> &list) {
        string title;
        double rating;
        int numberOfVotes, yearProduced, duration;
        string genre;
        string inputValue;
        vector<string> genres;
        try {
            piece->setFollowed(0);
            piece->setId(list.size() + 1);
            cout << "set the title of the piece of cinematography:" << endl;
            cin >> title;
            piece->setTitle(title);
            cout << "set the rating for the piece of cinematography:" << endl;
            cin >> inputValue;
            rating = atof(inputValue.c_str());
            if(rating>10 || rating<0) throw CustomException("wrong rating");
            piece->setRating(rating);
            cout << "set the number of votes for the piece of cinematography:" << endl;
            cin >> inputValue;
            numberOfVotes = atoi(inputValue.c_str());
            if(numberOfVotes<0) throw CustomException("Number of votes can not be lower than 0");
            piece->setNumberOfVotes(numberOfVotes);
            cout << "set the year of production for the piece of cinematography:" << endl;
            cin >> inputValue;
            yearProduced=atoi(inputValue.c_str());
            if(yearProduced<0) throw CustomException("Year of production can not be lower than 0");
            piece->setYearProduced(yearProduced);
            cout << "set the duration of the piece of cinematography:" << endl;
            cin >> inputValue;
            duration=atoi(inputValue.c_str());
            if(duration<0) throw CustomException("Duration can not be lower than 0");
            piece->setDuration(duration);
            cout << "set the genres of the piece of cinematography:" << endl;
            cout << "To set each genre type it and then press enter." << endl;
            cout << "To finish setting the genres type \"apply\" and press enter." << endl;
            while (cin >> genre) {
                if (genre == "apply") break;
                genres.push_back(genre);
            }
            piece->setGenres(genres);
            list.push_back(dynamic_cast<T *>(piece));
            if (instanceof<Series>(list[list.size() - 1])) {
                Series *s = dynamic_cast<Series *>(list[list.size() - 1]);
                int yearTheShowEnded = 0;
                cout << "set the year the show ended:" << endl;
                cin >> inputValue;
                yearTheShowEnded = atoi(inputValue.c_str());
                if(yearTheShowEnded<0){
                    list.pop_back();
                    throw CustomException("Year the show ended can not be lower than 0");
                }
                s->setYearTheShowEnded(yearTheShowEnded);
                s->setNumberOfSeasons(yearTheShowEnded - yearProduced + 1);
            } else if (instanceof<Livestream>(list[list.size() - 1])) {
                Livestream *l = dynamic_cast<Livestream *>(list[list.size() - 1]);
                int month;
                cout << "set the month of livestream: " << endl;
                cin >> inputValue;
                month = atoi(inputValue.c_str());
                if(month<1 || month >12){
                    list.pop_back();
                    throw CustomException("Invalid month");
                }
                l->setMonth(month);
                cout << "set the day of livestream: " << endl;
                int day;
                cin >> inputValue;
                day = atoi(inputValue.c_str());
                if(day<1 || day >31){
                    list.pop_back();
                    throw CustomException("Invalid day");
                }
                l->setDay(day);
                string hour;
                cout << "set hour of livestream hh:mm e. g. \"21:37\"" << endl;
                cin >> hour;
                if(hour.size()>5 || atoi(hour.substr(0,2).c_str())>23 || atoi(hour.substr(3,2).c_str())>59 || hour[2]!=':'){
                    list.pop_back();
                    throw CustomException("Invalid hour");
                }
                l->setHour(hour);
            }
        } catch(CustomException &e){
            cout<<e.getMessage()<<endl<<endl;
        }
    }

    static void delPiece(int index, vector<T *> &list) {
        list.erase(list.begin() + index);
    }

    static void editPiece(int index, vector<T *> &list) {
        bool endOfEditing = false;
        while (!endOfEditing) {
            cout << "Choose which parameter do you wish to edit:" << endl;
            list[index]->showOptions();
            string option;
            cin >> option;
            int optionNumber = atoi(option.c_str());
            list[index]->edit(optionNumber, endOfEditing);
        }
    }

    static void showingPool(vector<T *> list) {
        if (list.size() == 0) {
            cout << "there are no elements in pool to show" << endl;
            return;
        }
        cout<<setw(10)<<"Id";
        cout<<setw(20)<<"Type";
        cout<<setw(50)<<"Title";
        cout<<setw(10)<<"Rating";
        cout<<setw(20)<<"Number of Votes";
        cout<<setw(15)<<"IMDB ranking";
        cout<<setw(20)<<"Year produced";
        cout<<setw(20)<<"Year ended";
        cout<<setw(20)<<"number of seasons";
        cout<<setw(20)<<"Duration of video";
        cout<<setw(35)<<"Genres";
        cout<<setw(7)<<"Month";
        cout<<setw(6)<<"Day";
        cout<<setw(6)<<"Hour";
        cout<<endl;
        for (int i = 0; i < list.size(); i++) {
            cout<<setw(10)<<list[i]->getId();
            Movie *movie = dynamic_cast<Movie *> (list[i]);
            Livestream *livestream = dynamic_cast<Livestream *> (list[i]);
            Series *series = dynamic_cast<Series *> (list[i]);
            if (movie)cout<<setw(20)<<"movie";
            else if (livestream)cout<<setw(20)<<"livestream";
            else if (series)cout<<setw(20)<<"series";
            cout<<setw(50)<<list[i]->getTitle();
            cout<<setw(10)<<list[i]->getRating();
            cout<<setw(20)<<list[i]->getNumberOfVotes();
            if (movie) cout <<setw(15)<< movie->getImdbRanking();
            else cout <<setw(15)<<"-";
            cout << setw(20)<<list[i]->getYearProduced();
            if (series) cout << setw(20)<<series->getYearTheShowEnded();
            else cout <<setw(20)<< "-";
            if (series) cout << setw(20)<<series->getNumberOfSeasons();
            else cout <<setw(20)<< "-";
            cout << setw(20)<<list[i]->getDuration();
            vector<string> genres = list[i]->getGenres();
            string g;
            for (int j = 0; j < genres.size() - 1; j++) {
                g+=genres[j];
                g+=",";
            }
            g+=genres[genres.size() - 1];
            cout<<setw(35)<<g;
            if (livestream) cout << setw(7)<<livestream->getMonth();
            else cout <<setw(7)<< "-";
            if (livestream) cout << setw(6)<<livestream->getDay();
            else cout <<setw(6)<< "-";
            if (livestream) cout << setw(6)<<livestream->getHour();
            else cout <<setw(6)<< "-";
            cout << endl;
        }
    }

    static bool sortByRating(T *a, T *b) {
        if (a->getRating() > b->getRating()) return true;
        if (a->getRating() < b->getRating()) return false;
        return a->getNumberOfVotes() > b->getNumberOfVotes();
    }

    static void showAverageTime(vector<T*> list){
        cout<<setw(10)<<"Id";
        cout<<setw(50)<<"Title";
        cout<<setw(20)<<"Average Time";
        cout<<endl;
        for(const auto &piece:list){
            cout<<setw(10)<<piece->getId();
            cout<<setw(50)<<piece->getTitle();
            cout<<setw(20)<<piece->getDuration();
            cout<<endl;
        }
    }

    static void showFutureLivestreams(vector<T*> list){
        vector<Livestream*>futureLivestreams;
        time_t now = time(0);
        tm* localtm = localtime(&now);
        int year = localtm->tm_year + 1900;
        int month = localtm->tm_mon + 1;
        int day = localtm->tm_mday;
        string timeString = asctime(localtm);
        string fullHour = timeString.substr(11,5);
        int hour = atoi(fullHour.substr(0,2).c_str());
        int minute = atoi(fullHour.substr(3,2).c_str());
        for(const auto &piece:list){
            Livestream *live = dynamic_cast<Livestream*>(piece);
            if(live){
                if(year<live->getYearProduced()) {
                    futureLivestreams.push_back(live);
                } else if(year==live->getYearProduced()){
                    if(month<live->getMonth()){
                        futureLivestreams.push_back(live);
                    }else if(month==live->getMonth()){
                        if(day<live->getDay()){
                            futureLivestreams.push_back(live);
                        }
                        else if(day==live->getDay()){
                            string liveFullHour = live->getHour();
                            int liveHour = atoi(liveFullHour.substr(0,2).c_str());
                            int liveMinute = atoi(liveFullHour.substr(3,2).c_str());
                            if(hour<liveHour){
                                futureLivestreams.push_back(live);
                            } else if(hour == liveHour){
                                if( minute<liveMinute){
                                    futureLivestreams.push_back(live);
                                }
                            }
                        }
                    }
                }
            }
        }
        cout<<setw(10)<<"Id";
        cout<<setw(80)<<"Title";
        cout<<setw(10)<<"Year";
        cout<<setw(10)<<"Month";
        cout<<setw(10)<<"Day";
        cout<<setw(10)<<"Hour";
        cout<<endl;
        for(const auto &live:futureLivestreams){
            cout<<setw(10)<<live->getId();
            cout<<setw(80)<<live->getTitle();
            cout<<setw(10)<<live->getYearProduced();
            cout<<setw(10)<<live->getMonth();
            cout<<setw(10)<<live->getDay();
            cout<<setw(10)<<live->getHour();
            cout<<endl;
        }
    }

    ~OperationsOnListOfPiecesOfCinematography() = default;
};


#endif //TV_SHOWS_CONSOLE_APP_LISTOFPIECESOFCINEMATOGRAPHY_H
