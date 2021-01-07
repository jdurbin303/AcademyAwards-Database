/*
 Name: Julie Durbin
 Class: CSCI2421-001
 Description: This program creates a picture database and an actor/actress database based on the academy awards. Either database may be sorted, searched, added to, deleted from, otherwise modified, and saved.
 Status: Works perfectly on XCode. Compiles and runs successfully on CSE grid.
 File: This is the database.h file, which declares a vector of actors and a vector of pictures for use in the database. It declarations for all of the member functions needed to interact with the vectors, which represent the data stored in the database. The database.cpp file follows, and contains definition for all of these functions. In place of this description, there is an index at the top of that file because it is rather lengthy
 */
#ifndef Database_h
#define Database_h
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sstream>
//everything works fine in xcode without including the algorithm header
//but csegrid needs it!!!
#include <algorithm>
#include "Pictures.h"
#include "Actors.h"
using namespace std;

class Database
{
private:
    vector<Actor> actors;
    vector<Picture> pictures;
    
public:
    //Default constructor
    Database();
    
    //member functions
    //typical get/set doesn't really make sense here
    bool readActors(string filepath);
    bool readPictures(string filepath);

    //sorts vector by the field provided by the user
    void sortActors(int field);
    void sortPictures(int field);
    
    //prints all of the actors or all of the pictures
    void printActors(vector<Actor> v);
    void printPictures(vector<Picture> v);
    
    //performs a complete search of actors or pictures based on user input
    //returns the result vector so that we can do a secondary search as necessary
    vector<Actor> completeSearchActors(string search, int field, vector<Actor>inputVector);
    vector<Picture> completeSearchPictures(string search, int field, vector<Picture>inputVector);
    
    //performs a partial search of actors or pictures based on user input
    //returns the result vector so that we can do a secondary search as necessary
    vector<Actor> partialSearchActors(string search, int field, vector<Actor>inputVector);
    vector<Picture> partialSearchPictures(string search, int field, vector<Picture>inputVector);
    
    //adds a picture or actor to the vector based on user input
    void addActors();
    void addPictures(); 
    
    //engages search to look for picture or actor to delete or modify
    //user must enter exact name of picture or actor to delete or modify that field
    void deleteActor();
    void deletePicture();
    void modifyActor(int field, int index);
    void modifyPicture(int field, int index);
    
    
    //writes picture and/or actor database to new csv file
    void writeActorFile();
    void writePictureFile();
    
    //Display/traverse menu functions
    void startScreen();
    void mainMenu();
    
    //actor submenus
    void actorMenu();
    void sortActorMenu();
    void searchActorMenu(vector<Actor> v);
    
    //picture submenus
    void pictureMenu();
    void sortPictureMenu();
    void searchPictureMenu(vector<Picture> v);
    
    
};

#endif /* Database_h */
