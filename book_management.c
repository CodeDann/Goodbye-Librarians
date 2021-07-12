//
// Created by Jake Noar on 16/02/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book_management.h"
#include "interface.h"

//setup global array of books
struct Book * storedbookArray[100];
//index set at -1 initially as the array dosen't contain any books
int bookArray_index = -1;

int add_book(struct Book book){
    bookArray_index += 1;
    storedbookArray[bookArray_index] = (struct Book *) malloc(sizeof(struct Book));
    storedbookArray[bookArray_index] = &book;
    printf("Book has been successfully added!\n");
    return 0;
}

int remove_book(struct Book bookToDelete){
    for( int i = 0; i <= bookArray_index; ++i){
        if( storedbookArray[i]->id == bookToDelete.id){
            bookArray_index -= 1;
            printf("Book has been deleted from the library.\n");
            return 0;
        }
    }
    printf("Could not find book in library so it was not deleted.\n");
    return 1;
}

int load_books(FILE *file) {
    file = fopen("book_store.txt", "r");
    //check that the file exists and is not empty
    if (!file) {
        printf("There are no books in the library!\n");
        return 1;
    }

    char bookLine[200];
    const char * comma = ",";
    char *token;
    int MAX_BOOKS = 100;
    for(int i = 0; i < MAX_BOOKS; i++) {
        while (fgets(bookLine, 200, file) != NULL) {
            //want to set up new book so incremenent index
            bookArray_index += 1;
            //for first book we need to allocate correct amount of space before storing values
            storedbookArray[bookArray_index] = (struct Book *) malloc(sizeof(struct Book));

            //split each line into tokens
            token = strtok(bookLine, comma);
            //store current book id
            int tmpId = atoi(token);
            storedbookArray[bookArray_index]->id = tmpId;
            //move to next token
            token = strtok(NULL, comma);

            //store current book title
            storedbookArray[bookArray_index]->title = (char *) malloc(50*sizeof(char));
            strcpy(storedbookArray[bookArray_index]->title, token);
            //move to next token
            token = strtok(NULL, comma);

            //store current book author
            storedbookArray[bookArray_index]->authors = (char *) malloc(50*sizeof(char));
            strcpy(storedbookArray[bookArray_index]->authors, token);
            //move to next token
            token = strtok(NULL, comma);

            //store current book year
            char *strtoul1;
            unsigned int tmpYear = strtoul(token, &strtoul1, 10);
            storedbookArray[bookArray_index]->year = tmpYear;
            //move to next token
            token = strtok(NULL, comma);

            //store current book copies
            char *strtoul2;
            unsigned int tmpCopies = strtoul(token, &strtoul2, 10);
            storedbookArray[bookArray_index]->copies = tmpCopies;
        }
    }
    fclose(file);
    return 0;
}

int store_books(FILE *file){
    file = fopen("book_store.txt", "w");
    //check that the file exists and is not empty
    if (!file) {
        printf("There are no books in the library!\n");
        return 1;
    }
    for( int i = 0; i <= bookArray_index; i++){
        fprintf(file,"%i,",storedbookArray[i]->id);
        fprintf(file,"%s,",storedbookArray[i]->title);
        fprintf(file,"%s,",storedbookArray[i]->authors);
        fprintf(file,"%u,",storedbookArray[i]->year);
        fprintf(file,"%u\n",storedbookArray[i]->copies);
    }
    fclose(file);
    return 0;
}

struct BookArray find_book_by_title (const char *title){
    //setup the BookArray
    struct BookArray foundBookArray;
    foundBookArray.array = (struct Book *)malloc(sizeof (struct Book));
    //setup an array of found
    struct Book * booksFoundByTitle[20];
    int booksFound_index = -1;

    if(bookArray_index < 0){
        FILE *file;
        load_books(file);
    }
    //print the headers
    printf("\nId, Title, Authors, Year, Copies\n");
    for( int i = 0; i <= bookArray_index; i++){
        if( (strcmp(storedbookArray[i]->title, title) ) == 0){
            booksFound_index += 1;
            booksFoundByTitle[booksFound_index] = (struct Book *) malloc(sizeof(struct Book));
            booksFoundByTitle[booksFound_index] = storedbookArray[i];
            printf("%i, %s, %s, %d, %d\n", storedbookArray[i]->id, storedbookArray[i]->title, storedbookArray[i]->authors, storedbookArray[i]->year, storedbookArray[i]->copies);
        }
    }
    if( booksFound_index == -1 ){
        printf("No books found with that title\n");
        return foundBookArray;
    }
    else{
        foundBookArray.array = booksFoundByTitle[0];
        foundBookArray.length = booksFound_index;
        return foundBookArray;
    }
}

struct BookArray find_book_by_author (const char *title){
    //setup the BookArray
    struct BookArray foundBookArray;
    foundBookArray.array = (struct Book *)malloc(sizeof (struct Book));
    //setup an array of found
    struct Book * booksFoundByAuthor[20];
    int booksFound_index = -1;

    if(bookArray_index < 0){
        FILE *file;
        load_books(file);
    }
    //print the headers
    printf("\nId, Title, Authors, Year, Copies\n");
    for( int i = 0; i <= bookArray_index; i++){
        if( (strcmp(storedbookArray[i]->authors, title) ) == 0){
            booksFound_index += 1;
            booksFoundByAuthor[booksFound_index] = (struct Book *) malloc(sizeof(struct Book));
            booksFoundByAuthor[booksFound_index] = storedbookArray[i];
            printf("%i, %s, %s, %d, %d\n", storedbookArray[i]->id, storedbookArray[i]->title, storedbookArray[i]->authors, storedbookArray[i]->year, storedbookArray[i]->copies);
        }
    }
    if( booksFound_index == -1 ){
        printf("No books found with that Author\n");
        return foundBookArray;
    }
    else{
        foundBookArray.array = booksFoundByAuthor[0];
        foundBookArray.length = booksFound_index;
        return foundBookArray;
    }
}

struct BookArray find_book_by_year (unsigned int year){
    //setup the BookArray
    struct BookArray foundBookArray;
    foundBookArray.array = (struct Book *)malloc(sizeof (struct Book));
    //setup an array of found
    struct Book * booksFoundByYear[20];
    int booksFound_index = -1;

    if(bookArray_index < 0){
        FILE *file;
        load_books(file);
    }
    //print the headers
    printf("\nId, Title, Authors, Year, Copies\n");
    for( int i = 0; i <= bookArray_index; i++){
        if( storedbookArray[i]->year == year){
            booksFound_index += 1;
            booksFoundByYear[booksFound_index] = (struct Book *) malloc(sizeof(struct Book));
            booksFoundByYear[booksFound_index] = storedbookArray[i];
            printf("%i, %s, %s, %d, %d\n", storedbookArray[i]->id, storedbookArray[i]->title, storedbookArray[i]->authors, storedbookArray[i]->year, storedbookArray[i]->copies);
        }
    }
    if( booksFound_index == -1 ){
        printf("No books found with that Year\n");
        return foundBookArray;
    }
    else{
        foundBookArray.array = booksFoundByYear[0];
        foundBookArray.length = booksFound_index;
        return foundBookArray;
    }
}