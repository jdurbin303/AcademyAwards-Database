/*  INDEX
36. Constructor
41. Read actors -- read actor file
146. Read pictures -- read picture file
199. Sort Actors -- sort actor vector (or 2ndary search vector) based on given field
249. Sort pictures -- sort pic vector (or 2ndary search vector) based on given field
276. Print Actors -- prints actor vector w headings
291. Print Pictures -- prints picture vector w headings
310. Complete Search Actors -- searches for actor based on exact field
379. Complete Search Pictures --searched for picture based on exact field
447. Partial Search Actors -- searches for actor based on partial input for a given field
519. Partial Search Pictures -- searched for pic based on partial input for a given field
588. Add actors -- prompts user to input actor info and pushes to vector
655. Add pictures -- prompts user to input pic info and pushes to vector
768. Delete actor -- gives option to modify or delete, deletes as necessary
899. Modify actor -- modifies a selected actor based on a given field
967. Delete picture -- gives option to modify or delete, deletes as necessary
1090. Modify picture -- modifies a selected picture based on a given field
1234. Write Actor File -- saves modified vector by writing to new file
1269. Write Picture File -- saves modified vector by writing to new file
1301. Start Menu -- prompts menu to enter in files for each database
1332. Main Menu -- go into picture menu or actor menu?
1362. Actor Menu -- options to sort, search, add, modify/delete, save, or return to main menu
1408. Sort Actor Menu -- what field to sort by?
1442. Search Actor Menu -- what field to search by
1567. Picture Menu -- options to sort, search, add, modify/delete, save, or return to main menu
1609. Sort Picture Menu -- what field to sort by?
1650. Search Picture Menu -- what field to search by
 */

#include <stdio.h>
#include <stdlib.h>
#include <istream>
#include "Database.h"

//default constructor
Database::Database()
{
    //intentionally empty
}
//===============================================================================================
bool Database::readActors(string path)
{
    bool fileRead;
    ifstream infile(path);
    
    //note to self: make ask again for new file
    //more resistant to user error
    if (!infile)
    {
        fileRead = false;
        cout << "\n\nFile could not be read. Goodbye.\n\n";
    }//if
    else
    {
        fileRead = true;
    }
    //temp variables to read in from file
    //and then we will use them to construct the actor
    string fullName; //edit
    string fname;
    string lname;
    string year;
    string award;
    string win;
    string film;
    
    string line;
    //must ignore first line
    getline(infile, line);
    //if the first character of the first line isn't y, we read the wrong file
    //maybe put in a picture file instead of an actor file
    //not foolproof but prevents that error
    //takes back to the start screen
    if (line[0] != 'Y' && line[0] != 'y')
    {
        cout << "\nIncompatible file read. Restarting program\n\n";
        startScreen();
    }//if
    
    
    //use while to read until end of file
    //read each variable and then loop restarts at the new line
    while(getline(infile, year, ','))
    {
        getline(infile, award, ',');
        getline(infile, win, ',');
        //use space as delimiter here to seperate first name and last name
        //getline(infile, fname, ' ');
        //getline(infile, lname, ',');
        getline(infile, fullName, ',');
        getline(infile, film, '\n');
        
        //gets rid of /r at end of film if it's there
        //warning here for multi character constant but it's some bs and does work as intended
        if (film.back() == '/r')
        {
            film.erase(film.length()-1);
        }//if
        
        //splice name into first and last
        stringstream ss(fullName);
        //see if there's a middle name or initial in there we need to worry about
        //i get a warning about losing int precision if i declare it as an int so whatever
        long counter = 0;
        for (int i = 0; i < fullName.size(); i++)
        {
            counter = count(fullName.begin(), fullName.end(), ' ');
        }//for
        getline(ss, fname, ' ');
        //if there's more than one space, we know that there is a middle name or initial in there
        //ex / Noriyuki 'Pat' Morita
        string mname;
        if (counter > 1)
        {
            getline(ss, mname, ' ');
            //add middle name to first name so it can properly sort by last name
            fname = fname + ' ' + mname;
        }//if
        //if the last character after the first name is not a space
        //we know it is a one word name (ex/ Cher)
        //(Cher makes everything difficult!!!! -- dammit Cher!)
        if (fullName[fname.size()] != ' ')
        {
            //to get it to sort correctly, have to act like first name is last name
            //this is for one name entries like "Cher" and "Topol"
            lname = fname;
            fname = " ";
        }//if
        else
        {
            getline(ss, lname);
        }//else
        
        //construct a temp actor
        Actor temp(year, award, win, fname, lname, film);
        //push into vector
        actors.push_back(temp);
    }//while
    
    //sort by name
    sort(actors.begin(), actors.end(), NameCompare());
    
    return fileRead;
}//read actors
//=========================================================================
bool Database::readPictures(string path)
{
    bool fileRead;
    ifstream infile(path);
    
    //note to self: make ask again for new file
    //more resistant to user error
    if (!infile)
    {
        fileRead = false;
        cout << "\n\nFile could not be read. Goodbye.\n\n";
    }//if
    else
    {
        fileRead = true;
    }//else
    
    //temp variables
    string name;
    string year;
    string noms;
    string rating;
    string duration;
    string genre1;
    string genre2;
    string release;
    string meta;
    string synopsis;
    
    string line;
    getline(infile, line);
    //must ignore first line
    //but use it to check if we accidentally put in the wrong file
    //for example, if we put in actor file instead of picture file
    if (line[0] != 'n' && line[0] != 'N')
    {
        cout << "\nIncompatible file read. Restarting program.\n\n";
        startScreen();
    }//if
    //use while to read until end of file
    //read each variable and then loop restarts at the new line
    while(getline(infile, name, ','))
    {
        getline(infile, year, ',');
        getline(infile, noms, ',');
        getline(infile, rating, ',');
        getline(infile, duration, ',');
        getline(infile, genre1, ',');
        getline(infile, genre2, ',');
        getline(infile, release, ',');
        getline(infile, meta, ',');
        getline(infile, synopsis, '\n');
        
        //Gets rid of extraneous space at beginning of string
        //messes with my exact search results
        //put an if to trim the name
        //look for trim function!!!! couldn't find a good one =(((
        if (name.front() == ' ')
        {
           name.erase(name.begin());
        }//if
        
        //construct picture
        Picture temp(name, year, noms, rating, duration, genre1, genre2, release, meta, synopsis);
        //push to vector
        pictures.push_back(temp);
    }//while
    //sort by name
    sort(pictures.begin(), pictures.end(), PicByName());

    return fileRead;
}// read pictures 
//===============================================================================================
void Database::sortActors(int field)
{
    //sorts based on a user selected field
    switch (field)
    {
            //first case sorts by name
        case 1: sort(actors.begin(), actors.end(), NameCompare());
            break;
            //second case sorts by year
        case 2: sort(actors.begin(), actors.end(), YearCompare());
            break;
            //third case sorts by win
        case 3: sort(actors.begin(), actors.end(), WinCompare());
            break;
            //fourth case sorts by award
        case 4: sort(actors.begin(), actors.end(), AwardCompare());
            break;
            //final case sorts by film
        case 5: sort(actors.begin(), actors.end(), FilmCompare());
            break;
        default: cout << "\nMust choose a number between 1 and 5.\n";
            break;
    }//switch
    
    //prints after it's done being sorted
    printActors(actors);
    
}//sort actors
//===========================================================================================================================================
void Database::sortPictures(int field)
{
    switch (field)
    {
            //first case sorts by name
        case 1: sort(pictures.begin(), pictures.end(), PicByName());
            break;
            //second case sorts by year
        case 2: sort(pictures.begin(), pictures.end(), PicByYear());
            break;
            //third case sorts by nominations
        case 3: sort(pictures.begin(), pictures.end(), PicByNoms());
            break;
            //four case sorts by Genre1
        case 4: sort(pictures.begin(), pictures.end(), PicByGenre());
            break;
            //fifth case sorts by rating
        case 5: sort(pictures.begin(), pictures.end(), PicByRating());
            break;
        default: cout << "\nMust choose a number between 1 and 5.\n";
            break;
    }//switch
    
    //prints after it's done being sorted
    printPictures(pictures);
    
}//sort pictures
//===========================================================================================================================================
void Database::printActors(vector<Actor> v)
{
    cout << endl << endl;
    cout << setw(5) << "Year";
    cout << setw(30) << "Award";
    cout << setw(5) << "Win";
    cout << setw(30) << "Name";
    cout << setw(40) << "Film";
    cout << endl;
    for (int i = 0; i < v.size(); i++)
    {
        v[i].printActor();
    }//for
}//print actors
//===========================================================================================================================================
void Database::printPictures(vector<Picture> v)
{
    cout << endl << endl;
    cout << setw(20) << "Name";
    cout << setw(10) << "Year";
    cout << setw(15) << "Nominations";
    cout << setw(10) << "Rating";
    cout << setw(10) << "Duration";
    cout << setw(15) << "Genre 1";
    cout << setw(15) << "Genre 2";
    cout << setw(15) << "Release";
    cout << setw(5) << "Meta" << endl;
    for (int i = 0; i < v.size(); i++)
    {
        v[i].printPicture();
    }//for
}//print pictures
//===========================================================================================================================================
vector<Actor> Database::completeSearchActors(string search, int field, vector<Actor>inputVector)
{
    //new vector for results
    vector<Actor> results;
    
    switch(field)
    {
            //first case searches by name
        case 1:
            for (int i = 0; i < inputVector.size(); i++)
            {
                if (search == (inputVector[i].getFirstName() + " " + inputVector[i].getLastName()))
                {
                    results.push_back(inputVector[i]);
                }//if
            }//for
            break;
            //second case searches by year
        case 2:
            for (int i = 0; i < inputVector.size(); i++)
            {
                if (search == inputVector[i].getYear())
                {
                    results.push_back(inputVector[i]);
                }//if
            }//for
            break;
            //third case searches by win
        case 3:
            for (int i = 0; i < inputVector.size(); i++)
            {
                if (search == inputVector[i].getWinner())
                {
                    results.push_back(inputVector[i]);
                }//if
            }//for
            break;
            //fourth case searches by award
        case 4:
            for (int i = 0; i < inputVector.size(); i++)
            {
                if (search == inputVector[i].getAward())
                {
                    results.push_back(inputVector[i]);
                }//if
            }//for
            break;
            //fifth case searches by film
        case 5:
            for (int i = 0; i < inputVector.size(); i++)
            {
                if (search == (inputVector[i].getFilm()))
                {
                    results.push_back(inputVector[i]);
                }//if
            }//for
            break;
        default: cout << "\nMust choose a number between 1 and 5.\n";
            break;
    }//switch
   
    cout << "\n\nSearch Results:\n\n";
    printActors(results);
    
    //returns the results vector so that we can run a secondary search if user chooses to
    return results;
    
}//complete search actors
//===========================================================================================================================================
vector<Picture> Database::completeSearchPictures(string search, int field, vector<Picture>inputVector)
{
    //new vector for results
    vector<Picture> results;
    
    switch(field)
    {
            //first case searches by name
        case 1:
            for (int i = 0; i < inputVector.size(); i++)
            {
                if (search == inputVector[i].getName())
                {
                    results.push_back(inputVector[i]);
                }//if
            }//for
            break;
            //second case searches by year
        case 2:
            for (int i = 0; i < inputVector.size(); i++)
            {
                if (search == inputVector[i].getYear())
                {
                    results.push_back(inputVector[i]);
                }//if
            }//for
            break;
            //third case searches by nominations
        case 3:
            for (int i = 0; i < inputVector.size(); i++)
            {
                if (search == inputVector[i].getNoms())
                {
                    results.push_back(inputVector[i]);
                }//if
            }//for
            break;
            //fourth case searches by genre1
        case 4:
            for (int i = 0; i < inputVector.size(); i++)
            {
                if (search == inputVector[i].getGenre1())
                {
                    results.push_back(inputVector[i]);
                }//if
            }//for
            break;
            //fifth case searches by rating
        case 5:
            for (int i = 0; i < inputVector.size(); i++)
            {
                if (search == inputVector[i].getRating())
                {
                    results.push_back(inputVector[i]);
                }//if
            }//for
            break;
        default: cout << "\nMust choose a number between 1 and 5.\n";
            break;
    }//switch
    cout << "\n\nSearch Results:\n\n";
    printPictures(results);
    
    //returns the results vector so that we can run a secondary search if user chooses to
    return results;
    
}//complete search pictures function
//===========================================================================================================================================
vector<Actor> Database::partialSearchActors(string search, int field, vector<Actor>inputVector)
{
    //new vector for results
    vector<Actor> results;
    
    switch(field)
    {
            //first case searches by name
        case 1:
            for (int i = 0; i < inputVector.size(); i++)
            {
                string fullName = inputVector[i].getFirstName() + " " + inputVector[i].getLastName();
                //string::npos means it did not find anything for the partial search
                //so if it found anything, add it to the results vector
                if (fullName.find(search) != string::npos)
                {
                    results.push_back(inputVector[i]);
                }//if
            }//for
            break;
            //second case searches by year
        case 2:
            for (int i = 0; i < inputVector.size(); i++)
            {
                if (inputVector[i].getYear().find(search) != string::npos)
                {
                    results.push_back(inputVector[i]);
                }//if
            }//for
            break;
            //third case searches by win
        case 3:
            for (int i = 0; i < inputVector.size(); i++)
            {
                if (inputVector[i].getWinner().find(search) != string::npos)
                {
                    results.push_back(inputVector[i]);
                }//if
            }//for
            break;
            //fourth case searches by award
        case 4:
            for (int i = 0; i < inputVector.size(); i++)
            {
                if (inputVector[i].getAward().find(search) != string::npos)
                {
                    results.push_back(inputVector[i]);
                }//if
            }//for
            break;
            //fifth case searches by film
        case 5:
            for (int i = 0; i < inputVector.size(); i++)
            {
                if (inputVector[i].getFilm().find(search) != string::npos)
                {
                    results.push_back(inputVector[i]);
                }//if
            }//for
            break;
        default: cout << "\nMust choose a number between 1 and 5.\n";
            break;
    }//switch
    
    cout << "\n\nSearch Results:\n\n";
    printActors(results);
    
    //returns the results vector so that we can run a secondary search if user chooses to
    return results;
    
}//partial search actors function
//===========================================================================================================================================
vector<Picture> Database::partialSearchPictures(string search, int field, vector<Picture>inputVector)
{
    //new vector for results
    vector<Picture> results;
    
    switch(field)
    {
            //first case searches by name
        case 1:
            for (int i = 0; i < inputVector.size(); i++)
            {
                if (inputVector[i].getName().find(search) != string::npos)
                {
                    results.push_back(inputVector[i]);
                }
            }//for
            break;
            //second case searches by year
        case 2:
            for (int i = 0; i < inputVector.size(); i++)
            {
                if (inputVector[i].getYear().find(search) != string::npos)
                {
                    results.push_back(inputVector[i]);
                }//if
            }//for
            break;
            //third case searches by nominations
        case 3:
            for (int i = 0; i < inputVector.size(); i++)
            {
                if (inputVector[i].getNoms().find(search) != string::npos)
                {
                    results.push_back(inputVector[i]);
                }//if
            }//for
            break;
            //fourth case searches by genre1
        case 4:
            for (int i = 0; i < inputVector.size(); i++)
            {
                if (inputVector[i].getGenre1().find(search) != string::npos)
                {
                    results.push_back(inputVector[i]);
                }//if
            }//for
            break;
            //fifth case searches by rating
        case 5:
            for (int i = 0; i < inputVector.size(); i++)
            {
                if (inputVector[i].getRating().find(search) != string::npos)
                {
                    results.push_back(inputVector[i]);
                }//if
            }//for
            break;
        default: cout << "\nMust choose a number between 1 and 5.\n";
            break;
    }//switch
    
    cout << "\n\nSearch Results:\n\n";
    printPictures(results);
    
    //returns the results vector so that we can run a secondary search if user chooses to
    return results;
    
}//partial search pictures function
//===========================================================================================================================================
void Database::addActors()
{
    //temp variables to create new instance of actor/actress
    string fName;
    string lName;
    string year;
    string award;
    string win;
    string film;
    
    cout << "\n\nTo add an actor to the database, enter the following information:\n";
    cout << "First name: ";
    getline(cin, fName);
    cout << "\nLast name: ";
    getline(cin, lName);
    cout << "\nYear: ";
    getline(cin, year);
    //makes sure user input is appropriate
    while (year < "1929" || year > "3000")
    {
        cout << "\nYear must be between 1929 and 3000. Try again: ";
        cin.clear();
        getline(cin, year);
    }//while
    cout << "\nAward: ";
    getline(cin, award);
    cout << "\nWin (type 0 or 1): ";
    getline(cin, win);
    //makes sure user input is appropriate
    while (win != "0" && win != "1")
    {
        cout << "Win must be 0 for no win or 1 for a win. Try again: ";
        cin.clear();
        getline(cin, win);
    }//while
    cout << "\nFilm: ";
    getline(cin, film);
    
    //creates a new instance of actor and pushes it into the vector
    Actor temp(year, award, win, fName, lName, film);
    actors.push_back(temp);
    //sort by name and print
    sort(actors.begin(), actors.end(), NameCompare());
    printActors(actors);
    //add more?
    string selection;
    cout << "1. Add another actor/actress\n";
    cout << "2. Return to main menu\n";
    cout << "Selection: ";
    getline(cin, selection);
    while (selection != "1" && selection != "2")
    {
        cout << "Must choose 1 or 2. Try again: ";
        cin.clear();
        getline(cin, selection);
    }//while
    if (selection == "1")
    {
        addActors();
    }//if
    if (selection == "2")
    {
        mainMenu();
    }//if
    
}//add actors
//===========================================================================================================================================
void Database::addPictures()
{
    //temp variables to create new instance of picture
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
    
    //To properly check for any integer values
    //we must first tkae them in as an integer and then convert into a string
    cout << "\n\nTo add a picture to the database, enter the following information...\n";
    cout << "Name: ";
    getline(cin, name);
    cout << "\nNominations: ";
    int noms;
    cin >> noms;
    //makes sure user enters an appropriate amount of nominations
    while(cin.fail() || noms < 0 || noms > 20)
    {
        cout << "Must enter a number from 0 to 20. Try again: ";
        cin.clear();
        cin.ignore();
        cin >> noms;
    }//while
    nominations = to_string(noms);
    
    int rate;
    cout << "\nRating: ";
    cin.ignore();
    cin >> rate;
    while(cin.fail()|| rate < 0 || rate > 10)
    {
        cout << "Must enter a number from 0 to 10. Try again: ";
        cin.clear();
        cin.ignore();
        cin >> rate;
    }//while
    rating = to_string(rate);
    
    int dur;
    cout << "\nDuration: ";
    cin >> dur;
    //checks for appropriate user input
    while(cin.fail() || dur < 0 || dur > 1000)
    {
        cout << "Must enter a number from 0 to 1000. Try again: ";
        cin.clear();
        cin.ignore();
        cin >> dur;
    }//while
    duration = to_string(dur);
    
    cin.ignore();
    cout << "\nGenre 1: ";
    getline(cin, genre1);
    cout << "\nGenre 2: ";
    getline(cin, genre2);
    cout << "\nMonth of Release: ";
    getline(cin, release);
    while ((release != "January") && (release != "February") && (release != "March") && (release != "April") && (release != "May") && (release != "June") && (release != "July") && (release != "August") && (release != "September") && (release != "October") && (release != "November") && (release != "December"))
    {
        cout << "Must enter a month name from January to December. Try again: ";
        cin.clear();
        getline(cin, release);
    }//while
    
    int meta;
    cout << "\nMetacritic: ";
    cin >> meta;
    while(cin.fail() || meta < 0 ||meta > 100)
    {
        cout << "Must enter a number from 0 to 100. Try again: ";
        cin.clear();
        cin.ignore();
        cin >> meta;
    }//while
    metacritic = to_string(meta);
    
    cout << "\nSynopsis: ";
    getline(cin, synopsis);
    
    //creates a new instance of picture for the picture added and puts it into the vector
    Picture temp(name, year, nominations, rating, duration, genre1, genre2, release, metacritic, synopsis);
    pictures.push_back(temp);
    
    //sort by name and print
    sort(pictures.begin(), pictures.end(), PicByName());
    printPictures(pictures);
    
    //add more?
    string selection;
    cout << "1. \n\nAdd another picture\n";
    cout << "2. Return to main menu\n";
    cout << "Selection: ";
    getline(cin, selection);
    while (selection != "1" && selection != "2")
    {
        cout << "Must choose 1 or 2. Try again: ";
        cin.clear();
        getline(cin, selection);
    }//while
    if (selection == "1")
    {
        addPictures();
    }//if
    if (selection == "2")
    {
        mainMenu();
    }//if
}//add pictures
//===========================================================================================================================================
void Database::deleteActor()
{
    cout << "\n\nTo modify or delete an actor, you must enter the EXACT FULL NAME of the actor you wish to modify or delete.\n";
    cout << "\nWould you like to:\n";
    cout << "1. Go back and search\n";
    cout << "2. Enter name of actor to modify/delete\n";
    cout << "Selection: ";
    
    string selection;
    getline(cin, selection);
    while (selection != "1" && selection != "2")
    {
        cout << "Must choose 1 or 2. Try again: ";
        cin.clear();
        getline(cin, selection);
    }//if
    if (selection == "1")
    {
        searchActorMenu(actors);
    }//if
    if (selection == "2")
    {
        cout << "\n\nFor entering in the first name of the actor/actress, keep the following in mind--\n";
        cout << "Put in a space if the actor/actress has a one word name ie/'Cher'.\n";
        cout << "Include any middle names with the first name of the actor/actress\n";
        cout << "Enter in the first name of the actor/actress: ";
        string fname;
        getline(cin, fname);
        
        cout << "\nIf the actor/actress has a one word name (ie/ 'Cher') enter this name in as the last name.";
        cout << "\nEnter the last name of the actor/actress: ";
        string lname;
        getline(cin, lname);
        
        cout << "\n1.Delete";
        cout << "\n2.Modify";
        cout << "\nSelection: ";
        string select;
        getline(cin, select);
        //check user input
        while (select != "1" && select != "2")
        {
            cout << "Must enter 1 or 2. Try again: ";
            cin.clear();
            getline(cin, select);
        }//while
        
        //delete
        if (select == "1")
        {
            string full = fname + " " + lname;
            int counter = 0;
            for (int i = 0; i < actors.size(); i++)
            {
                string fullName = actors[i].getFirstName() + " " + actors[i].getLastName();
                if (fullName == full)
                {
                    actors.erase(actors.begin() + i);
                    counter++;
                    sort(actors.begin(), actors.end(), NameCompare());
                }//if
            }//for
            //if there's no matches, display message
            if (counter == 0)
            {
                cout << "\nNo actor/actress found to delete.\n";
            }//if
        }//if
        //modify
        if (select == "2")
        {
            cout << "\nChoose one of the following fields to modify:\n";
            cout << "1. Year\n";
            cout << "2. Award\n";
            cout << "3. Winner\n";
            cout << "4. Name\n";
            cout << "5. Film\n";
            int selection;
            cin >> selection;
            while (cin.fail() || selection < 1 || selection > 5)
            {
                cout << "Must choose an option between 1 and 5. Try again: ";
                cin.ignore();
                cin >> selection;
            }//while
            string full = fname + " " + lname;
            int counter = 0;
            for (int i = 0; i < actors.size(); i++)
            {
                string fullName = actors[i].getFirstName() + " " + actors[i].getLastName();
                if (fullName == full)
                {
                    modifyActor(selection, i);
                    counter++;
                    sort(actors.begin(), actors.end(), NameCompare());
                }//if
            }//for
            //if there's no matches, display message
            if (counter == 0)
            {
                cout << "\nNo actor/actress found to modify.\n";
            }//if
        }//if
    }//if
    
    //delete more or print and return to main menu?
    cout << "\n1.Delete/modify another actor\n";
    cout << "2. Display current actors and return to main menu\n";
    cout << "Selection: ";
    string select;
    cin.clear();
    getline(cin, select);
    while (select != "1" && select != "2")
    {
        cout << "Must choose 1 or 2. Try again: ";
        cin.clear();
        getline(cin, select);
    }//if
    if (select == "1")
    {
        deleteActor();
    }//if
    if (select == "2")
    {
        printActors(actors);
        mainMenu();
    }//if

    
}//delete actor
//===========================================================================================================================================
void Database::modifyActor(int field, int index)
{
    switch(field)
    {
            //year
        case 1:
        {
            cout << "\nEnter new year: ";
            int year;
            cin >> year;
            while (cin.fail() || year < 1929 || year > 3000)
            {
                cout << "\nYear must between 1929 and 3000. Try again: ";
                cin.ignore();
                cin >> year;
            }//while
            string yr = to_string(year);
            actors[index].setYear(yr);
            break;
        }//case1
            //award
        case 2:
        {
            cout << "\nEnter an award: ";
            string award;
            getline(cin, award);
            actors[index].setAward(award);
            break;
        }//case2
            //win
        case 3:
        {
            cout << "\nEnter a win (0 or 1): ";
            int win;
            cin >> win;
            while(cin.fail() || win < 0 || win > 1)
            {
                cout << "\nMust enter a 0 or 1: ";
                cin.ignore();
                cin >> win;
            }//while
            break;
        }//case3
            //name
        case 4:
        {
            string fname;
            string lname;
            cout << "\nEnter a first name: ";
            getline(cin, fname);
            cout << "\nEnter a last name: ";
            getline(cin, lname);
            actors[index].setFirstName(fname);
            actors[index].setLastName(lname);
            break;
        }//case4
            //film
        case 5:
        {
            string film;
            cout << "\nEnter a film: ";
            getline (cin, film);
            actors[index].setFilm(film);
            break;
        }//case5
    }//switch
}//modify actor
//===========================================================================================================================================
void Database::deletePicture()
{
    cout << "\n\nTo delete/modify a picture, you must enter the EXACT NAME of the picture you wish to delete.\n";
    cout << "Would you like to:\n";
    cout << "1. Go back and search\n";
    cout << "2. Enter name of the picture to modify or delete\n";
    cout << "Selection: ";
    
    string selection;
    getline(cin, selection);
    while (selection != "1" && selection != "2")
    {
        cout << "Must choose 1 or 2. Try again: ";
        cin.clear();
        getline(cin, selection);
    }//if
    if (selection == "1")
    {
        searchPictureMenu(pictures);
    }//if
    if (selection == "2")
    {
        cout << "\n1. Delete";
        cout << "\n2. Modify";
        cout << "\nSelection: ";
        string select;
        cin.clear();
        getline(cin, select);
        while (select != "1" && select != "2")
        {
            cout << "Must select 1 or 2. Try again: ";
            cin.clear();
            getline(cin, select);
        }//while
        
        //delete
        if (select == "1")
        {
            cout << "\n\nEnter the EXACT NAME of the picture to delete: ";
            string name;
            getline(cin, name);
            int counter = 0;
            for (int i = 0; i < pictures.size(); i++)
            {
                if (pictures[i].getName() == name)
                {
                    pictures.erase(pictures.begin() + i);
                    sort(pictures.begin(), pictures.end(), PicByName());
                    counter ++;
                }//if
            }//for
            if (counter == 0)
            {
                cout << "\nNo picture found to delete.\n\n";
            }//if
        }//if
        //modify
        if (select == "2")
        {
            cout << "\n\nEnter the EXACT NAME of the picture to modify: ";
            string name;
            getline(cin, name);
            int counter = 0;
            for (int i = 0; i < pictures.size(); i++)
            {
                if (pictures[i].getName() == name)
                {
                    //need code here, duh!
                    counter ++;
                    cout << "Select a field to modify:\n";
                    cout << "1. Name\n";
                    cout << "2. Year\n";
                    cout << "3. Nominations\n";
                    cout << "4. Rating\n";
                    cout << "5. Duration\n";
                    cout << "6. Genre 1\n";
                    cout << "7. Genre 2\n";
                    cout << "8. Release Month\n";
                    cout << "9. Metacritic Rating\n";
                    cout << "10. Synopsis\n";
                    cout << "Selection: ";
                    int field;
                    cin >> field;
                    while (cin.fail() || field < 1 || field > 10)
                    {
                        cout << "\nMust select a number between 1 and 10. Try again: ";
                        cin.ignore();
                        cin >> field;
                    }//while
                    modifyPicture(field, i);
                    sort(pictures.begin(), pictures.end(), PicByName());
                }//if
            }//for
            if (counter == 0)
            {
                cout << "\nNo picture found to modify.\n\n";
            }//if
        }//if
    }//if
    
    cout << "\n1.Delete or modify another picture\n";
    cout << "2. Print current pictures and return to main menu\n";
    cout << "Selection: ";
    cin.ignore();
    string select;
    getline(cin, select);
    while (select != "1" && select != "2")
    {
        cout << "Must choose 1 or 2. Try again: ";
        cin.clear();
        getline(cin, select);
    }//if
    if (select == "1")
    {
        deletePicture();
    }//if
    if (select == "2")
    {
        printPictures(pictures);
        mainMenu();
    }//if
}//delete picture
//===========================================================================================================================================
void Database::modifyPicture(int field, int index)
{
    //for whatever reason, this function works best with plenty of cin.ignores w/ each selection
    switch(field)
    {
            //name
        case 1:
        {
            string name;
            cin.ignore();
            cout << "\nEnter a new name: ";
            getline(cin, name);
            pictures[index].setName(name);
            break;
        }//case1
            //year
        case 2:
        {
            int year;
            cin.ignore();
            cout << "\nEnter a new year: ";
            cin >> year;
            while(cin.fail() || year < 1929 || year > 3000)
            {
                cout << "\nYear must between 1929 and 3000. Try again: ";
                cin.ignore();
                cin >> year;
            }//while
            string yr = to_string(year);
            pictures[index].setYear(yr);
            break;
        }//case2
            //nomations
        case 3:
        {
            int noms;
            cin.ignore();
            cout << "\nEnter a new number of nominations: ";
            cin >> noms;
            //makes sure user enters an appropriate amount of nominations
            while(cin.fail() || noms < 0 || noms > 20)
            {
                cout << "Must enter a number from 0 to 20. Try again: ";
                cin.ignore();
                cin >> noms;
            }//while
            string nominations = to_string(noms);
            pictures[index].setNoms(nominations);
            break;
        }//case3
            //rating
        case 4:
        {
            float rating;
            cin.ignore();
            cout << "\nEnter a new rating: ";
            cin >> rating;
            //makes sure user enters an appropriate amount of nominations
            while(cin.fail() || rating < 0.0 || rating > 10.0)
            {
                cout << "Must enter a number from 0 to 10. Try again: ";
                cin.ignore();
                cin >> rating;
            }//while
            string rate = to_string(rating);
            pictures[index].setRating(rate);
            break;
        }//case4
            //duration
        case 5:
        {
            int dur;
            cin.ignore();
            cout << "\nEnter a new duration: ";
            cin >> dur;
            while(cin.fail() || dur < 1 || dur > 1000)
            {
                cout << "Must enter a number from 1 to 1000. Try again: ";
                cin.ignore();
                cin >> dur;
            }//while
            string duration = to_string(dur);
            pictures[index].setDuration(duration);
            break;
        }//case5
            //genre1
        case 6:
        {
            string genre;
            cout << "\nEnter a new genre 1: ";
            cin.ignore();
            getline(cin, genre);
            pictures[index].setGenre1(genre);
            break;
        }//case6
            //genre2
        case 7:
        {
            string genre;
            cout << "\nEnter a new genre 2: ";
            cin.ignore();
            getline(cin, genre);
            pictures[index].setGenre2(genre);
            break;
        }//case7
            //release
        case 8:
        {
            string release;
            cin.ignore();
            cout << "\nEnter a new release month: ";
            getline(cin, release);
            while ((release != "January") && (release != "February") && (release != "March") && (release != "April") && (release != "May") && (release != "June") && (release != "July") && (release != "August") && (release != "September") && (release != "October") && (release != "November") && (release != "December"))
            {
                cout << "Must enter a month name from January to December. Try again: ";
                cin.clear();
                getline(cin, release);
            }//while
            pictures[index].setRelease(release);
            break;
        }//case8
            //metacritic
        case 9:
        {
            int meta;
            cin.ignore();
            cout <<"\nEnter a new metacritic rating: ";
            cin >> meta;
            while(cin.fail() || meta < 0 || meta > 100)
            {
                cout << "\nMust enter a number from 0 to 100. Try again: ";
                cin.ignore();
                cin >> meta;
            }//while
            string metacritic = to_string(meta);
            pictures[index].setMeta(metacritic);
            break;
        }//case9
            //synopsis
        case 10:
        {
            string synopsis;
            cin.ignore();
            cout <<"\nEnter a new synopsis: ";
            getline(cin, synopsis);
            pictures[index].setSynopsis(synopsis);
            break;
        }//case10
    }//switch
    
    
}//modify pictures
//===========================================================================================================================================
void Database::writeActorFile()
{
    ofstream outFile;
    outFile.open("./NewActorDatabase.csv");
    //checks if it opened or not
    if (outFile.fail())
    {
        cout << "\nOutput file failed to open. Returning to main menu.\n";
        mainMenu();
    }//if
    
    outFile << "Year,Award,Winner,Name,Film\n";
    for (int i = 0; i < actors.size(); i++)
    {
        outFile << actors[i].getYear() << ",";
        outFile << actors[i].getAward() << ",";
        outFile << actors[i].getWinner() << ",";
        outFile << actors[i].getFirstName() << " " << actors[i].getLastName() << ",";
        outFile << actors[i].getFilm() << "\n";
    }//for
    
    outFile.close();
    cout << "\n\nFile successfully saved\n\n";
    mainMenu();
}//write actor file
//===========================================================================================================================================
void Database::writePictureFile()
{
    ofstream outFile;
    outFile.open("NewPictureDatabase.csv");
    outFile << "Name,Year,Nominations,Rating,Duration,Genre1,Genre2,Release,Metacritic,Synopsis\n";
    
    for (int i = 0; i < pictures.size(); i++)
    {
        outFile << pictures[i].getName() << ",";
        outFile << pictures[i].getYear() << ",";
        outFile << pictures[i].getNoms() << ",";
        outFile << pictures[i].getRating() << ",";
        outFile << pictures[i].getDuration() << ",";
        outFile << pictures[i].getGenre1() << ",";
        outFile << pictures[i].getGenre2() << ",";
        outFile << pictures[i].getRealease() << ",";
        outFile << pictures[i].getMeta() << ",";
        outFile << pictures[i].getSynopsis() << "\n";
    }//for
    
    outFile.close();
    cout << "\n\nFile successfully saved\n\n";
    mainMenu();
    
}//write picture file
//===========================================================================================================================================
//===========================================================================================================================================
//===========================================================================================================================================
//===========================================================================================================================================
//MENU RELATED FUNCTIONS!!!===================================================
//NOTE TO SELF: edit this function -- do we need to ask user for the filepaths?
//what stops user from entering actors as pictures and vice versa?
void Database::startScreen()
{
    cout << endl << endl << "Welcome to the Academy Award Database!" << endl << endl;
    cout << "This database contains information on actors/actresses, pictures, and their associated academy awards"  << endl;
    
    //ask user for file!!!! don't hardcode path
    string actorpath;
    string picturepath;
    cout << "\nEnter in a file path for the actor database: ";
    getline(cin, actorpath);
    cout << "\nEnter in a file path for the picture database: ";
    getline(cin, picturepath);
    
    
    //put return to start in main menu
    bool file1read = readActors(actorpath);
    //readActors("/Users/juliedurbin/Desktop/actor-actress_shortversion.csv");
    bool file2read = readPictures(picturepath);
    //readPictures("/Users/juliedurbin/Desktop/pictures_shortversion.csv");
    
    if (file1read && file2read)
    {
        mainMenu();
    }//if
    else
    {
        cout << "Failed to read files. Restarting program\n\n";
        startScreen();
    }//
}//startScreen
//===========================================================================================================================================
void Database::mainMenu()
{
    cout << "\nMAIN MENU\n\n";
    cout << "1. Enter Actor/Actress Database\n";
    cout << "2. Enter Picture Database\n";
    cout << "3. Quit\n";
    
    cout << "To proceed, type '1' , '2' , or '3' into console: ";
    string selection;
    getline(cin, selection);

    //makes sure user enters correct input
    while (selection != "1" && selection != "2" && selection != "3")
    {
        cout << "\nMust enter '1' or '2' to proceed. Try again: ";
        cin.clear();
        getline(cin, selection);
    }//while
    
    if (selection == "1")
    {
        actorMenu();
    }//if
    if (selection == "2")
    {
        pictureMenu();
    }//if
    if (selection == "3")
    {
        cout << "\n\nYou have chosen to quit. Goodbye.\n\n";
        exit(0);
    }//if
}//main menu
//===========================================================================================================================================
void Database::actorMenu()
{
    cout << "\n\nACTOR/ACTRESSES MENU\n\n";
    cout << "1. Sort\n";
    cout << "2. Search\n";
    cout << "3. Add\n";
    cout << "4. Modify/Delete\n";
    cout << "5. Save\n";
    cout << "6. Main Menu\n\n";
    cout << "To proceed, type a number from '1' to '6': ";
    
    //take in user input
    string selection;
    getline(cin, selection);
    while (selection != "1" && selection != "2" && selection != "3" && selection != "4" && selection != "5" && selection != "6")
    {
        cout << "Must enter a number from '1' to '6' to proceed. Try again: ";
        cin.clear();
        getline(cin, selection);
    }//while
    
    int select = stoi(selection);
    switch (select)
    {
        case 1: sortActorMenu();
            break;
        case 2: searchActorMenu(actors);
            break;
        case 3: addActors();
            break;
        case 4: deleteActor();
            break;
        case 5: writeActorFile();
            break;
        case 6: mainMenu();
            break;
        default: cout << "Error. Terminating Program\n";
            exit (-1);
            break;
    }//switch
}//actor menu
//===========================================================================================================================================
void Database::sortActorMenu()
{
    cout << "\n\nSelect a field to sort by:\n\n";
    cout << "1. Name\n";
    cout << "2. Year\n";
    cout << "3. Winner\n";
    cout << "4. Award\n";
    cout << "5. Film\n";
    cout << "6. Main Menu\n";
    
    //take in user input
    string selection;
    getline(cin, selection);
    while (selection != "1" && selection != "2" && selection != "3" && selection != "4" && selection != "5" && selection != "6")
    {
        cout << "Must enter a number from '1' to '6' to proceed. Try again: ";
        cin.clear();
        getline(cin, selection);
    }//while
    
    int select = stoi(selection);
    if (select == 6)
    {
        mainMenu();
    }//if
    else
    {
        sortActors(select);
    }//else
    
    //returns to this menu unless they select to return to main menu
    sortActorMenu();
}
//===========================================================================================================================================
void Database::searchActorMenu(vector<Actor> v)
{
    cout << "1. Complete Search\n";
    cout << "2. Partial Search\n";
    string type;
    getline(cin, type);
    if (type == "1")
    {
        cout << "\n\nSelect a field to run a complete search by:\n\n";
        cout << "1. Name\n";
        cout << "2. Year\n";
        cout << "3. Winner (0 or 1)\n";
        cout << "4. Award\n";
        cout << "5. Film\n";
        cout << "6. Main Menu\n";
        cout << "Selection: ";
        
        //gets user input
        string selection;
        getline(cin, selection);
        while (selection != "1" && selection != "2" && selection != "3" && selection != "4" && selection != "5" && selection != "6")
        {
            cout << "Must enter a number from '1' to '6' to proceed. Try again: ";
            cin.clear();
            getline(cin, selection);
        }//while
        int select = stoi(selection);
        
        //gets search query
        string query;
        cout << "\n\nSearch for: ";
        getline(cin, query);
        //searches using the search query, the field, and the vector
        vector<Actor>results = completeSearchActors(query, select, v);
        cout << "\nRun a secondary search?";
        cout << "\n1. Yes";
        cout << "\n2. Return to search";
        cout << "\n4/Users/juliedurbin/Desktop/DS&PD/FinalProjectv1/FinalProjectv1/DurbinJulie_FinalProject/actor-actress.csv. Return to main menu";
        cout << "\nSelection: ";
        string selection2;
        getline(cin, selection2);
        //protects agains bad input
        while (selection2 != "1" && selection2 != "2" && selection2 != "3")
        {
            cout << "Must enter a number from '1' to '3' to proceed. Try again: ";
            cin.clear();
            getline(cin, selection2);
        }//while
        int select2 = stoi(selection2);
        switch(select2)
        {
            case 1: searchActorMenu(results);
                break;
            case 2: searchActorMenu(actors);
                break;
            case 3: mainMenu();
                break;
        }//switch
    }//if
    if (type == "2")
    {
        cout << "\n\nSelect a field to run a partial search by:\n\n";
        cout << "1. Name\n";
        cout << "2. Year\n";
        cout << "3. Winner\n (0 or 1)";
        cout << "4. Award\n";
        cout << "5. Film\n";
        cout << "6. Main Menu\n";
        cout << "Selection: ";
        
        //gets user input
        string selection;
        getline(cin, selection);
        while (selection != "1" && selection != "2" && selection != "3" && selection != "4" && selection != "5" && selection != "6")
        {
            cout << "Must enter a number from '1' to '6' to proceed. Try again: ";
            cin.clear();
            getline(cin, selection);
        }//while
        
        int select = stoi(selection);
        //gets search query
        string query;
        cout << "\n\nSearch for: ";
        getline(cin, query);
        //searches using the search query, the field, and the vector
        vector<Actor>results = partialSearchActors(query, select, v);
        cout << "\nRun a secondary search?";
        cout << "\n1. Yes";
        cout << "\n2. Return to search";
        cout << "\n3. Delete an actor";
        cout << "\n4. Return to main menu";
        string selection2;
        getline(cin, selection2);
        //protects agains bad input
        while (selection2 != "1" && selection2 != "2" && selection2 != "3" && selection2 != "4")
        {
            cout << "Must enter a number from '1' to '4' to proceed. Try again: ";
            cin.clear();
            getline(cin, selection2);
        }//while
        int select2 = stoi(selection2);
        switch(select2)
        {
            case 1: searchActorMenu(results);
                break;
            case 2: searchActorMenu(actors);
                break;
            case 3: deleteActor();
                break;
            case 4: mainMenu();
                break;
        }//switch */ 
    }//if
    
    while (type != "1" && type != "2")
    {
        cout << "Must enter a number from '1' to '2' to proceed. Try again: ";
        cin.clear();
        getline(cin, type);
    }//while
    
}//search actor menu

//===========================================================================================================================================
void Database::pictureMenu()
{
    cout << "\n\nPICTURES MENU\n\n";
    cout << "1. Sort\n";
    cout << "2. Search\n";
    cout << "3. Add\n";
    cout << "4. Modify/Delete\n";
    cout << "5. Save\n";
    cout << "6. Main Menu\n\n";
    cout << "To proceed, type a number from '1' to '6': ";
    
    //take in user input
    string selection;
    getline(cin, selection);
    while (selection != "1" && selection != "2" && selection != "3" && selection != "4" && selection != "5" && selection != "6")
    {
        cout << "Must enter a number from '1' to '6' to proceed. Try again: ";
        cin.clear();
        getline(cin, selection);
    }//while
    
    int select = stoi(selection);
    switch (select)
    {
        case 1: sortPictureMenu();
            break;
        case 2: searchPictureMenu(pictures);
            break;
        case 3: addPictures();
            break;
        case 4: deletePicture();
            break;
        case 5: writePictureFile();
            break;
        case 6: mainMenu(); 
            break;
        default: cout << "Error. Terminating Program\n";
            exit (-1);
            break;
    }//switch
}//picture menu
//===========================================================================================================================================
void Database::sortPictureMenu()
{
    cout << "\n\nSelect a field to sort by:\n\n";
    cout << "1. Name\n";
    cout << "2. Year\n";
    cout << "3. Nominations\n";
    cout << "4. Genre1\n";
    cout << "5. Rating\n";
    cout << "6. Main Menu\n";
    
    //take in user input
   // string selection;
    //getline(cin, selection);
    //while (selection != "1" && selection != "2" && selection != "3" && selection != "4" && selection != "5" && selection != "6")
    int selection;
    cin >> selection;
    while (cin.fail() || selection < 1 || selection > 6)
    {
        cout << "Must enter a number from '1' to '6' to proceed. Try again: ";
        //cin.clear();
        //getline(cin, selection);
        cin.ignore();
        cin >> selection;
    }//while
    
    //int select = stoi(selection);
    //if (select == 6)
    if (selection == 6)
    {
        mainMenu();
    }//if
    else
    {
        //sortPictures(select);
        sortPictures(selection);
    }//else
    
    //returns to this menu unless they select to return to main menu
    sortPictureMenu();
}//sort picture menu
//===========================================================================================================================================
void Database::searchPictureMenu(vector<Picture> v)
{
    cout << "1. Complete Search\n";
    cout << "2. Partial Search\n";
    string type;
    getline(cin, type);
    if (type == "1")
    {
        cout << "\n\nSelect a field to run a complete search by:\n\n";
        cout << "1. Name\n";
        cout << "2. Year\n";
        cout << "3. Nominations\n";
        cout << "4. Genre1\n";
        cout << "5. Rating\n";
        cout << "6. Main Menu\n";
        cout << "Selection: ";
        
        //gets user input
        string selection;
        getline(cin, selection);
        while (selection != "1" && selection != "2" && selection != "3" && selection != "4" && selection != "5" && selection != "6")
        {
            cout << "Must enter a number from '1' to '6' to proceed. Try again: ";
            cin.clear();
            getline(cin, selection);
        }//while
        int select = stoi(selection);
        
        //gets search query
        string query;
        cout << "\n\nSearch for: ";
        getline(cin, query);
        //searches using the search query, the field, and the vector
        vector<Picture>results = completeSearchPictures(query, select, v);
        cout << "\nRun a secondary search?";
        cout << "\n1. Yes";
        cout << "\n2. Return to search";
        cout << "\n3. Modify/Delete a picture";
        cout << "\n3. Return to main menu";
        cout << "\nSelection: ";
        string selection2;
        getline(cin, selection2);
        //protects agains bad input
        while (selection2 != "1" && selection2 != "2" && selection2 != "3" && selection2 != "4")
        {
            cout << "Must enter a number from '1' to '4' to proceed. Try again: ";
            cin.clear();
            getline(cin, selection2);
        }//while
        int select2 = stoi(selection2);
        switch(select2)
        {
            case 1: searchPictureMenu(results);
                break;
            case 2: searchPictureMenu(pictures);
                break;
            case 3: deletePicture();
                break;
            case 4: mainMenu();
                break;
        }//switch
    }//if
    if (type == "2")
    {
        cout << "\n\nSelect a field to run a partial search by:\n\n";
        cout << "1. Name\n";
        cout << "2. Year\n";
        cout << "3. Nominations\n";
        cout << "4. Genre1\n";
        cout << "5. Rating\n";
        cout << "6. Main Menu\n";
        cout << "Selection: ";
        
        //gets user input
        string selection;
        getline(cin, selection);
        while (selection != "1" && selection != "2" && selection != "3" && selection != "4" && selection != "5" && selection != "6")
        {
            cout << "Must enter a number from '1' to '6' to proceed. Try again: ";
            cin.clear();
            getline(cin, selection);
        }//while
        
        int select = stoi(selection);
        //gets search query
        string query;
        cout << "\n\nSearch for: ";
        getline(cin, query);
        //searches using the search query, the field, and the vector
        vector<Picture>results = partialSearchPictures(query, select, v);
        cout << "\nRun a secondary search?";
        cout << "\n1. Yes";
        cout << "\n2. Return to search";
        cout << "\n3. Modify/delete";
        cout << "\n4. Return to main menu";
        cout << "\nSelection";
        string selection2;
        getline(cin, selection2);
        //protects agains bad input
        while (selection2 != "1" && selection2 != "2" && selection2 != "3" && selection2 != "4")
        {
            cout << "\nMust enter a number from '1' to '4' to proceed. Try again: ";
            cin.clear();
            getline(cin, selection2);
        }//while
        int select2 = stoi(selection2);
        switch(select2)
        {
            case 1: searchPictureMenu(results);
                break;
            case 2: searchPictureMenu(pictures);
                break;
            case 3: deletePicture();
                break;
            case 4: mainMenu();
                break;
        }//switch */
    }//if
    
    while (type != "1" && type != "2")
    {
        cout << "Must enter a number from '1' to '2' to proceed. Try again: ";
        cin.clear();
        getline(cin, type);
    }//while
}//search picture menu
