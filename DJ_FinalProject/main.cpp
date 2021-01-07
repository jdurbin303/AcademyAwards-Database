/*
 Name: Julie Durbin
 Class: CSCI2421-001
 Description: This program creates a picture database and an actor/actress database based on the academy awards. Either database may be sorted, searched, added to, deleted from, otherwise modified, and saved. 
 Status: Works perfectly on XCode. Compiles and runs successfully on CSE grid.
 File: This is the main.cpp file, declares an instance of the database and initiates the interface with the start screen.
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "Database.h"

int main() {

    //declare an instance of database
    Database database;

    //start with the start menu
    //goes into all other menus and functions from there
    database.startScreen();
    
    cout << endl;
  
    return 0;
}
