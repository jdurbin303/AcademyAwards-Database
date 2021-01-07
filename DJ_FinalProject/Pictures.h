/*
 Name: Julie Durbin
 Class: CSCI2421-001
 Description: This program creates a picture database and an actor/actress database based on the academy awards. Either database may be sorted, searched, added to, deleted from, otherwise modified, and saved.
 Status: Works perfectly on XCode. Compiles and runs successfully on CSE grid.
 File: This is the pictures.h file, which defines picture class. Includes structs for third parameter of stl sort, allowing user to sort based on different fields
 */
#ifndef Pictures_h
#define Pictures_h

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Picture
{

private:
    //Private member variables
    string name;
    string year;
    string nominations;
    string rating;
    string duration;
    string genre1;
    string genre2;
    string release;
    string metacritic;
    string synopsis;
    
public:
    //constructor
    Picture(string name, string year, string nominations, string rating, string duration, string genre1, string genre2, string release, string metacritic, string synopsis);
    
    //get/set functions
    void setName(string newName){name = newName;}
    string getName(){return name;}
    
    void setYear(string newYear){year = newYear;}
    string getYear(){return year;}
    
    void setNoms(string nomNum){nominations = nomNum;}
    string getNoms(){return nominations;}
    
    void setRating(string rate){rating = rate;}
    string getRating(){return rating;}
    
    void setDuration(string dur){duration = dur;}
    string getDuration(){return duration;}
    
    void setGenre1(string genre){genre1 = genre;}
    string getGenre1(){return genre1;}
    
    void setGenre2(string genre){genre2 = genre;}
    string getGenre2(){return genre2;}
    
    void setRelease(string rel){release = rel;}
    string getRealease(){return release;}
    
    void setMeta(string meta){metacritic = meta;}
    string getMeta(){return metacritic;}
    
    void setSynopsis(string newSynopsis){synopsis = newSynopsis;}
    string getSynopsis(){return synopsis;}
    
    //member functions
    void printPicture();
};
//===========================================================================================================================================
//struct becomes a third parameter for STL to sort picture by name
struct PicByName
{
  bool operator()(Picture first, Picture second)
    {
        if (first.getName() < second.getName())
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
//struct becomes a third parameter for STL to sort picture by year
struct PicByYear
{
    bool operator()(Picture first, Picture second)
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
//struct becomes a third parameter for STL to sort picture by nominations
//error here
//need to add a 0 to the front of the nominations
//otherwise it sorts by the first character ex 10 is infront of 9 because 1 < 9
struct PicByNoms
{
  bool operator()(Picture first, Picture second)
    {
        //have to convert to integer to get it to sort correctly
        //check this for other sorting and make sure I don't have the same error
        int firstNom;
        int secNom;
        //these if statements protect against a stoi error
        //but it could still throw an error if the input file is wonky
        //but i'm going to assume that the input file is fine
        //not cool that in some fields empty means 0 and here - means here!
        //lame!!!
        if (first.getNoms() == "-")
        {
            firstNom = 0;
        }//if
        else
        {
            firstNom = stoi(first.getNoms());
        }//else
        if (second.getNoms() == "-")
        {
            secNom = 0;
        }//if
        else
        {
            secNom = stoi(second.getNoms());
        }//else
        if (firstNom < secNom)
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
//struct becomes a third parameter for STL to sort picture by genre1
struct PicByGenre
{
    bool operator()(Picture first, Picture second)
    {
        if (first.getGenre1() < second.getGenre1())
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
//struct becomes a third parameter for STL to sort by rating
struct PicByRating
{
  bool operator()(Picture first, Picture second)
    {
        if (first.getRating() < second.getRating())
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
#endif /* Pictures_h */
