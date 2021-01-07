/*
 Name: Julie Durbin
 Class: CSCI2421-001
 Description: This program creates a picture database and an actor/actress database based on the academy awards. Either database may be sorted, searched, added to, deleted from, otherwise modified, and saved.
 Status: Works perfectly on XCode. Compiles and runs successfully on CSE grid.
 File: This is the actors.cpp file, which includes constructor for actors and print actor function
 */

#include <stdio.h>
#include "Actors.h"
using namespace std;

Actor::Actor(string newYear, string newAward , string newWinner, string fName, string lName, string newFilm)
{
    year = newYear;
    award = newAward;
    winner = newWinner;
    firstName = fName;
    lastName = lName;
    film = newFilm;
}

void Actor::printActor()
{
    cout << setw(5) << year;
    cout << setw(30) << award;
    cout << setw(5) << winner;
    cout << setw(30) << firstName + " " + lastName;
    cout << setw(40) << film;
    cout << endl;
}
