/*
 Name: Julie Durbin
 Class: CSCI2421-001
 Description: This program creates a picture database and an actor/actress database based on the academy awards. Either database may be sorted, searched, added to, deleted from, otherwise modified, and saved.
 Status: Works perfectly on XCode. Compiles and runs successfully on CSE grid.
 File: This is the actors.h file, which defines actor class. Includes structs for third parameter of stl sort, allowing user to sort based on different fields
 */

#ifndef Actors_h
#define Actors_h

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Actor
{
private:
    string year;
    string award;
    string winner;
    string firstName;
    string lastName;
    string film;
    
    
public:
    //Constructor
    Actor(string year, string award, string winner, string fname, string lname, string film);
    
    //get/set functions
    void setYear(string yr){year = yr;}
    string getYear(){return year;}
    
    void setAward(string newAward){award = newAward;}
    string getAward(){return award;}
    
    void setWinner(string win){winner = win;}
    string getWinner(){return winner;}
    
    void setFirstName(string newName){firstName = newName;}
    string getFirstName(){return firstName;}
    
    void setLastName(string newName){lastName = newName;}
    string getLastName(){return lastName;}
    
    void setFilm(string newFilm){film = newFilm;}
    string getFilm(){return film;}
    
    //member functions
    void printActor();
};
//===========================================================================================================================================
//struct becomes a third parameter for STL sort to sort by name
struct NameCompare
{
    bool operator()(Actor first, Actor second)
    {
        if ((first.getLastName()+first.getFirstName()) < (second.getLastName()+second.getFirstName()))
        {
            return true;
        }//if
        else
        {
            return false;
        }
    }
};
//===========================================================================================================================================
//struct becomes a third parameter for STL sort to sort by year
struct YearCompare
{
  bool operator()(Actor first, Actor second)
    {
        if (first.getYear() < second.getYear())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};
//===========================================================================================================================================
//struct becomes a third parameter for STL to sort by winner
struct WinCompare
{
  bool operator()(Actor first, Actor second)
    {
        if (first.getWinner() < second.getWinner())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};
//===========================================================================================================================================
//struct becomes a third parameter for STL to sort by award
struct AwardCompare
{
    bool operator()(Actor first, Actor second)
    {
        if (first.getAward() < second.getAward())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};
//===========================================================================================================================================
//struct becomes a third parameter for STL to sort by film
struct FilmCompare
{
  bool operator()(Actor first, Actor second)
    {
        if (first.getFilm() < second.getFilm())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};
//===========================================================================================================================================
#endif /* Actors_h */
