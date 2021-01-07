    /*
     Name: Julie Durbin
     Class: CSCI2421-001
     Description: This program creates a picture database and an actor/actress database based on the academy awards. Either database may be sorted, searched, added to, deleted from, otherwise modified, and saved.
     Status: Works perfectly on XCode. Compiles and runs successfully on CSE grid.
     File: This is the pictures.cpp file, which includes constructor for picture and print picture function
     */

#include <stdio.h>
#include "Pictures.h"
using namespace std;

Picture::Picture(string newName, string newYear, string nom, string newRating, string newDuration, string g1, string g2, string newRelease, string meta, string newSynopsis)
{
    name = newName;
    year = newYear;
    nominations = nom;
    rating = newRating;
    duration = newDuration;
    genre1 = g1;
    genre2 = g2;
    release = newRelease;
    metacritic = meta;
    synopsis = newSynopsis;
}//constructor

void Picture::printPicture()
{
    cout << setw(20) << name;
    cout << setw(10) << year;
    cout << setw(15) << nominations;
    cout << setw(10) << rating;
    cout << setw(10) << duration;
    cout << setw(15) << genre1;
    cout << setw(15) << genre2;
    cout << setw(15) << release;
    cout << setw(5) << metacritic;
    cout << endl << synopsis << endl << endl;
    cout << endl;
    
}//print picture

