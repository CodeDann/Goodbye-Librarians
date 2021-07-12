//
// Created by Jake Noar on 16/02/2021.
//

#ifndef PPCW1_USER_MANAGEMENT_H
#define PPCW1_USER_MANAGEMENT_H

#endif //PPCW1_USER_MANAGEMENT_H


//definition of structure of each user
struct User{
    char name[30];
    char email[30];
    char password[30];
    int admin;
};

//function to setup a new account with user inputted parameters
//returns 0 if username is already taken
//returns 1 when setup correctly
int register_account(char username[30], char password[30], char email[30]);

//function to log a pre-existing user in
//returns 1 for successful log in
//returns 0 for unsuccessful log in
int login(char username[30], char password[30]);

//function to load all users from a text file "user_store.txt" to ensure persistence
//returns 1 if there are no users saved
//returns 0 when done loading
int load_users(FILE *file);

//function to store all users into a text file "user_store.txt" to ensure persistence
//returns 1 if there are no users to store
//returns 0 when done storing the users
int store_users(FILE *file);


//global variables to allow for users to be accessed across functions
extern struct User * userArray[ ];
extern int userArray_index;