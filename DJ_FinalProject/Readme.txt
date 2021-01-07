*******************************************************
*  Name      : Julie Durbin         
*  Student ID: 109019017
*  Class     :  CSC 2421-001           
*  HW#       :  FINAL PROJECT               
*  Due Date  :  DEC. 11, 2019
*******************************************************


                 Read Me


*******************************************************
*  Description of the program
*******************************************************
This program creates a database for pictures and actors/actresses in the academy awards.

Each database can be searched, sorted, added to, deleted from, otherwise modified, and saved.

*******************************************************
*  Source files
*******************************************************

Name:  main.cpp
Name:  Database.h
Name:  Database.cpp
Name:  Pictures.h
Name:  Pictures.cpp
Name:  Actors.h
Name:  Actors.cpp


   
*******************************************************
*  Circumstances of programs
*******************************************************

   The program runs successfully. There is one nominal warning about a multiple character constant ('\r'). However, using this multiple character char works to get rid of the \r at the end of the line present on the csv file. 
   
   The program was developed and tested on XCode on a 2018 Macbook Pro.
	 It was compiled, run, and tested on csegrid.

*******************************************************
*  How to build and run the program
*******************************************************

1. Uncompress the homework.  The homework file is compressed.  
   To uncompress it use the following commands 
       % unzip [DurbinJulie_FinalProject]

   Now you should see a directory named homework with the files:
        main.cpp
	Database.h
	Database.cpp
	Pictures.h
	Pictures.cpp
	Actors.h
	Actors.cpp


2. Build the program.

    Change to the directory that contains the file by:
    % cd [DurbinJulie_FinalProject] 

    Compile the program by:
    % make

3. Run the program by:
   % ./database

4. Delete the obj files, executables, and core dump by
   %./make clean
