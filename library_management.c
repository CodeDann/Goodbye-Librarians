//
// Created by Jake Noar on 27/02/2021.
//
#include "interface.h"
#include "book_management.h"
#include "user_management.h"
#include "library_management.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//setup an array of borrowed books
struct Loan * borrowedBooks[20];
//and and index for it
int borrowedBooks_index = -1;

int borrow_book(int id){
    if(bookArray_index < 0){
        FILE *file;
        load_books(file);
    }
    if( id > (bookArray_index+1) ){
        printf("The ID you entered does not corrolate to any books in the library\n");
    }
    for( int i = 0; i <= borrowedBooks_index; ++i){
        if( (borrowedBooks[i]->id == id) && ((strcmp(borrowedBooks[i]->borrowed_by, userArray[logged_in_index]->name) ) == 0)){
            printf("You have already borrowed a copy of this book!\n");
            return -1;
        }
    }
    for( int i = 0; i <= bookArray_index; i++){
        if( storedbookArray[i]->id == id ){
            borrowedBooks_index += 1;
            borrowedBooks[borrowedBooks_index] = (struct Loan *) malloc(sizeof(struct Loan));
            borrowedBooks[borrowedBooks_index]->id = storedbookArray[i]->id;
            borrowedBooks[borrowedBooks_index]->title = (char *) malloc(30*sizeof(char));
            strcpy(borrowedBooks[borrowedBooks_index]->title, storedbookArray[i]->title);
            borrowedBooks[borrowedBooks_index]->borrowed_by = (char *) malloc(30*sizeof(char));
            strcpy(borrowedBooks[borrowedBooks_index]->borrowed_by, userArray[logged_in_index]->name);
            if(storedbookArray[i]->copies > 0){
                storedbookArray[i]->copies -= 1;
            }
            else {
                printf("There are no copies of that book left in the library\n");
                return 0;
            }
        }
    }
    if( borrowedBooks_index == -1 ){
        printf("No books found with that id\n");
        return 0;
    }
    else{
        printf("You have successfully borrowed a book!\n");
        return 1;
    }
}
//returns a loaned book to the library
//returns 1 if book is correctly returned
//returns 0 if book was not found in the borrowed books array
int return_book(int id) {
    for (int i = 0; i <= borrowedBooks_index; ++i) {
        if ((borrowedBooks[i]->id == id) &&
            ((strcmp(borrowedBooks[i]->borrowed_by, userArray[logged_in_index]->name)) == 0)) {
            free(borrowedBooks[i]);
            borrowedBooks_index -= 1;
            for (int i = 0; i <= bookArray_index; i++) {
                if (storedbookArray[i]->id == id) {
                    storedbookArray[i]->copies += 1;
                }
            }
            printf("Book was successfully returned to the library!\n");
            return 1;
        }
    }
    printf("Error: Loan was not found to be on record! Reloading menu...\n");
    return 0;
}

int store_loans(FILE *file){
    file = fopen("loans_store.txt", "w");
    for( int i = 0; i <= borrowedBooks_index ; i++){
        fprintf(file,"%i,",borrowedBooks[i]->id);
        fprintf(file,"%s,",borrowedBooks[i]->title);
        fprintf(file,"%s\n",borrowedBooks[i]->borrowed_by);
    }
    fclose(file);
    return 0;
}

int load_loans(FILE *file){
    file = fopen("loans_store.txt", "r");
    //check that the file exists and is not empty
    if (!file) {
        printf("There are no loans in the library!\n");
        return 1;
    }
    char bookLine[100];
    const char * comma = ",";
    char *token;
    int MAX_USERS = 100;
    for(int i = 0; i < MAX_USERS; i++) {
        while (fgets(bookLine, 100, file) != NULL) {
            //want to set up new book so incremenent index
            borrowedBooks_index += 1;
            //for first book we need to allocate correct amount of space before storing values
            borrowedBooks[borrowedBooks_index] = (struct Loan *) malloc(sizeof(struct Loan));

            //split each line into tokens
            token = strtok(bookLine, comma);
            //store current book id
            int tmpId = atoi(token);
            borrowedBooks[borrowedBooks_index]->id = tmpId;
            //move to next token
            token = strtok(NULL, comma);

            //store current book title
            borrowedBooks[borrowedBooks_index]->title = (char *) malloc(50*sizeof(char));
            strcpy(borrowedBooks[borrowedBooks_index]->title, token);
            //move to next token
            token = strtok(NULL, comma);

            //store current book author
            borrowedBooks[borrowedBooks_index]->borrowed_by = (char *) malloc(50*sizeof(char));
            strcpy(borrowedBooks[borrowedBooks_index]->borrowed_by, token);
        }
    }
    fclose(file);
    return 0;
}
void display_loans(){
    //check that there are books in the library, if not load from the file
    if(borrowedBooks_index == -1){
        FILE *file;
        load_loans(file);
    }
    printf("Here is a list of all the books you are currently borrowing...\n");
    //print the headers
    printf("\nId, Title\n");
    //print the books
    for( int i = 0; i <= borrowedBooks_index; i++){
        if( (strcmp(borrowedBooks[i]->borrowed_by, userArray[logged_in_index]->name) == 0) ) {
            //print id
            printf("%i, ", storedbookArray[i]->id);
            //print title
            printf("%s\n", storedbookArray[i]->title);
        }
    }
}