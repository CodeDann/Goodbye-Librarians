//
// Created by Jake Noar on 16/02/2021.
//

#ifndef PPCW1_INTERFACE_H
#define PPCW1_INTERFACE_H

#endif //PPCW1_INTERFACE_H

//function to call the mainMenu which is the CLI that runs the program
void mainMenu();

//function that calls search menu to allow users to search for books
void search_books();

//function that simply displays all the books in the library
void display_books();


//global variables that allow other functions to know the currently logged in user and to allow admin more features
extern int logged_in_index;
extern int admin_logged_in;
