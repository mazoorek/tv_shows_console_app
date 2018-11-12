#include <iostream>
#include <vector>

using namespace std;
#ifndef TV_SHOWS_CONSOLE_APP_PIECEOFCINEMATOGRAPHY_H
#define TV_SHOWS_CONSOLE_APP_PIECEOFCINEMATOGRAPHY_H
#include "CustomException.h"

class PieceOfCinematography {
private:
    int duration; //in minutes
    double rating;
    int numberOfVotes;
    string title;
    int yearProduced;
    vector <string> genres;
    int id;
    bool followed;
public:
    PieceOfCinematography();
    bool isFollowed() const;
    void setFollowed(bool followed);
    int getId() const;
    void setId(int id);
    int getDuration() const;
    void setDuration(int duration);
    double getRating() const;
    void setRating(double rating);
    string getTitle() const;
    void setTitle(string title);
    int getNumberOfVotes() const;
    void setNumberOfVotes(int numberOfVotes);
    int getYearProduced() const;
    void setYearProduced(int yearProduced);
    const vector<string> &getGenres() const;
    void setGenres(const vector<string> &genres);
    virtual void showOptions() {
        cout<<"(1)rating"<<endl;
        cout<<"(2)number of votes"<<endl;
        cout<<"(3)title"<<endl;
        cout<<"(4)year of production"<<endl;
        cout<<"(5)duration"<<endl;
        cout<<"(6)genres"<<endl;
        cout<<"(7)quit editing"<<endl;
    }
    virtual void edit(int optionNumber, bool &endOfEditing) {
        try {
            string inputValue="";
            if (optionNumber == 1) {
                double newRating = 0;
                cout << "set new rating:" << endl;
                cin >> inputValue;
                newRating = atof(inputValue.c_str());
                if(newRating>10 || newRating<0) throw CustomException("wrong rating");
                setRating(newRating);
            } else if (optionNumber == 2) {
                int newNumberOfVotes = 0;
                cout << "set new number of votes:" << endl;
                cin >> inputValue;
                newNumberOfVotes = atoi(inputValue.c_str());
                if(newNumberOfVotes<0) throw CustomException("Number of votes can not be lower than 0");
                setNumberOfVotes(newNumberOfVotes);
            } else if (optionNumber == 3) {
                string newTitle = "";
                cout << "set new title:" << endl;
                cin >> newTitle;
                setTitle(newTitle);
            } else if (optionNumber == 4) {
                int newYearOfProduction = 0;
                cout << "set new year of production:" << endl;
                cin >> inputValue;
                newYearOfProduction=atoi(inputValue.c_str());
                if(newYearOfProduction<0) throw CustomException("Year of production can not be lower than 0");
                setYearProduced(newYearOfProduction);
            } else if (optionNumber == 5) {
                int newDuration = 0;
                cout << "set new duration:" << endl;
                cin >> inputValue;
                newDuration=atoi(inputValue.c_str());
                if(newDuration<0) throw CustomException("Duration can not be lower than 0");
                setDuration(newDuration);
            } else if (optionNumber == 6) {
                string newGenre;
                vector<string> genres;
                cout << "set the genres of the piece of cinematography:" << endl;
                cout << "To set each genre type it and then press enter." << endl;
                cout << "To finish setting the genres type \"apply\" and press enter." << endl;
                while (cin >> newGenre) {
                    if (newGenre == "apply") break;
                    genres.push_back(newGenre);
                }
                setGenres(genres);
            } else if (optionNumber == 7) {
                endOfEditing = true;
            } else {
                if (optionNumber == 0 || optionNumber > numberOfOptions) {
                    cout << "wrong number" << endl;
                }
            }
        } catch(CustomException &e){
            cout<<e.getMessage()<<endl;
        }
    }

    virtual void getData(vector <string> data){
        int id = atoi(data[0].c_str());
        setId(id);
        data[1]=data[1].substr(data[1].size()-3,3); //avoiding some input bug connected with reading from file
        double rating = atof(data[1].c_str());
        setRating(rating);
        int numberOfVotes = atoi(data[2].c_str());
        setNumberOfVotes(numberOfVotes);
        string title = data[3];
        setTitle(title);
        int yearProduced = atoi(data[4].c_str());
        setYearProduced(yearProduced);
        int duration = atoi(data[5].c_str());
        setDuration(duration);
        vector <string> genres;
        int j=0;
        string genre;
        for(int i =0;i<data[6].size();i++){
            if(data[6][i]==','){
                genre = data[6].substr(j,i-j);
                j=i+1;
                genres.push_back(genre);
            }
        }
        genre = data[6].substr(j,data[6].size()-j);
        genres.push_back(genre);
        setGenres(genres);
        bool followed = (bool)atoi(data[7].c_str());
        setFollowed(followed);
    }
    virtual ~PieceOfCinematography();

protected:
    int numberOfOptions; //number of options in edit menu
};


#endif //TV_SHOWS_CONSOLE_APP_PIECEOFCINEMATOGRAPHY_H
