//
// Created by Jake Noar on 16/02/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "interface.h"
#include "book_management.h"
#include "user_management.h"

//setup global array of users
struct User * userArray[100];
//index set at -1 initially as the array dosen't contain any users
int userArray_index = -1;

int register_account(char *username, char *password, char *email){
    for( int i = 0; i <= userArray_index; ++i){
        if( ((strcmp(userArray[i]->name, username) ) == 0)){
            return 0;
        }
    }
    userArray_index += 1;
    userArray[userArray_index] = (struct User *) malloc(sizeof(struct User));
    strcpy(userArray[userArray_index]->name, username);
    strcpy(userArray[userArray_index]->password, password);
    strcpy(userArray[userArray_index]->email, email);
    userArray[userArray_index]->admin = 0;
    return 1;
}

int login(char *username, char *password){
    for( int i = 0; i <= userArray_index; ++i){
        if( ((strcmp(userArray[i]->name, username) ) == 0) && ((strcmp(userArray[i]->password, password) ) == 0)){
            if( userArray[i]->admin == 1){ admin_logged_in = 1; }
            logged_in_index = i;
            return 1;
        }
    }
    return 0;
}

int store_users(FILE *file){
    file = fopen("user_store.txt", "w");
    //check that the file exists and is not empty
    if (!file) {
        printf("There are no users registered in the library!\n");
        return 1;
    }
    for( int i = 0; i <= userArray_index; i++){
        fprintf(file,"%s,",userArray[i]->name);
        fprintf(file,"%s,",userArray[i]->password);
        fprintf(file,"%s,",userArray[i]->email);
        fprintf(file,"%i\n",userArray[i]->admin);
    }
    fclose(file);
    return 0;
}

int load_users(FILE *file){
    file = fopen("user_store.txt", "r");
    //check that the file exists and is not empty
    if (!file) {
        printf("There are no users in the library!\n");
        return 1;
    }
    char bookLine[100];
    const char * comma = ",";
    char *token;
    int MAX_USERS = 100;
    for(int i = 0; i < MAX_USERS; i++) {
        while (fgets(bookLine, 100, file) != NULL) {
            //want to set up new book so incremenent index
            userArray_index += 1;
            //for first book we need to allocate correct amount of space before storing values
            userArray[userArray_index] = (struct User *) malloc(sizeof(struct User));

            //split each line into tokens
            token = strtok(bookLine, comma);

            //store current user name
            strcpy(userArray[userArray_index]->name, token);
            //move to next token
            token = strtok(NULL, comma);

            //store current user password
            strcpy(userArray[userArray_index]->password, token);
            //move to next token
            token = strtok(NULL, comma);

            //store current user email
            strcpy(userArray[userArray_index]->email, token);
            //move to next token
            token = strtok(NULL, comma);

            //store current user admin
            int tmpAdmin = atoi(token);
            userArray[userArray_index]->admin = tmpAdmin;
        }
    }
    fclose(file);
    return 0;
}