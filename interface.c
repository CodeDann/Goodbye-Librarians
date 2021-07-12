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
#include "library_management.h"
#include "regex.h"

#define MAX_NAME_LENGTH 30

int logged_in_index = -1;
int admin_logged_in = 0;



void mainMenu(){
    if(logged_in_index >= 0) {
        if (admin_logged_in == 1) {
            printf("\nLogged in as: %s", userArray[logged_in_index]->name);
            printf("\nPlease Choose an Option:\n1) Add Book\n2) Remove Book\n3) Search for books\n4) Display all books\n5) Logout\n Option:");
            int menuChoice = 0;
            char enter;
            //validation on menu_choice to ensure its an integer
            if (scanf("%i%c", &menuChoice, &enter) != 2 || enter != '\n') {
                printf("\nSorry, the option you entered was invalid, please try again.\n");
                fflush(stdin);
                mainMenu();
            } else {
                if (menuChoice == 1) {
                    //UNDER HERE IS pre add_book
                    struct Book newBook;
                    //the next id will always be 2 ahead of bookArray_index
                    newBook.id = (bookArray_index + 2);
                    //get newBook title from user and store into newBook
                    printf("\nPlease enter book title: ");
                    char newBookTitle[30];
                    fgets(newBookTitle, 30, stdin);
                    //remove trailing newline
                    if ((strlen(newBookTitle) > 0) && (newBookTitle[strlen(newBookTitle) - 1] == '\n'))
                        newBookTitle[strlen(newBookTitle) - 1] = '\0';
                    newBook.title = (char *) malloc(sizeof(newBookTitle));
                    strcpy(newBook.title, newBookTitle);

                    //get newBook author from user and store into newBook
                    printf("Please enter book author(s) (NB authors are seperated with |): ");
                    char newBookAuthor[30];
                    fgets(newBookAuthor, 30, stdin);
                    //remove trailing newline
                    if ((strlen(newBookAuthor) > 0) && (newBookAuthor[strlen(newBookAuthor) - 1] == '\n'))
                        newBookAuthor[strlen(newBookAuthor) - 1] = '\0';
                    newBook.authors = (char *) malloc(sizeof(newBookAuthor));
                    for( int i = 0; i < strlen(newBookAuthor); ++i){
                        if( isalpha(newBookAuthor[i]) == 0) {
                            printf("invalid character in author book was not added\n");
                            mainMenu();
                        }
                    }
                    strcpy(newBook.authors, newBookAuthor);
                    //get newBook year from user and store into newBook
                    printf("Please enter book year: ");
                    if (scanf("%u%c", &newBook.year, &enter) != 2 || enter != '\n') {
                        printf("\nSorry, the option you entered was invalid, book was not added.\n");
                        fflush(stdin);
                        mainMenu();
                    }
                    //get newBook copies from user and store into newBook
                    printf("Please enter number of book copies: ");
                    if (scanf("%u%c", &newBook.copies, &enter) != 2 || enter != '\n') {
                        printf("\nSorry, the option you entered was invalid, book was not added.\n");
                        fflush(stdin);
                        mainMenu();
                    }
                    add_book(newBook);
                } else if (menuChoice == 2) {
                    //remove book
                    printf("\nPlease enter book title: ");
                    char bookToRemoveTitle[30];
                    fgets(bookToRemoveTitle, 30, stdin);
                    //remove trailing newline
                    if ((strlen(bookToRemoveTitle) > 0) && (bookToRemoveTitle[strlen(bookToRemoveTitle) - 1] == '\n'))
                        bookToRemoveTitle[strlen(bookToRemoveTitle) - 1] = '\0';
                    struct BookArray removals = find_book_by_title(bookToRemoveTitle);
                    int chooseToRemove = 0;
                    if( removals.length >= 0){
                        printf("Are these the book(s) you want to remove?\n1) Yes\n2) No\n Option: ");
                        scanf("%i", &chooseToRemove);
                        fflush(stdin);
                    }
                    if (chooseToRemove == 1) {
                        for (int i = 0; i <= removals.length; ++i) {
                            remove_book(removals.array[i]);
                        }
                    } else {
                        printf("Those books will not be removed. Reloading menu...\n");
                        mainMenu();
                    }
                } else if (menuChoice == 3) { search_books(); }
                else if (menuChoice == 4) { display_books(); }
                else if (menuChoice == 5) {
                    logged_in_index = -1;
                    admin_logged_in = 0;
                    printf("Successfully logged out. Reloading menu...\n");
                    mainMenu(); }
            }
        } else if (admin_logged_in == 0) {
            printf("\nLogged in as: %s", userArray[logged_in_index]->name);
            printf("\nPlease Choose an Option:\n1) Borrow a book\n2) Return a book\n3) Search for books\n4) Display all books\n5) Logout\n Option:");
            int menuChoice = 0;
            char enter;
            //validation on menu_choice to ensure its an integer
            if (scanf("%i%c", &menuChoice, &enter) != 2 || enter != '\n') {
                printf("\nSorry, the option you entered was invalid, please try again.\n");
                fflush(stdin);
                mainMenu();
            } else {
                if (menuChoice == 1) {
                    printf("\nPlease enter the ID of the book you want to borrow: ");
                    int usrInp;
                    scanf("%u", &usrInp);
                    borrow_book(usrInp);
                }
                else if (menuChoice == 2) {
                    display_loans();
                    printf("\nPlease enter the ID of the book you want to return: ");
                    int usrInp;
                    scanf("%u", &usrInp);
                    return_book(usrInp);
                }
                else if (menuChoice == 3) { search_books(); }
                else if (menuChoice == 4) { display_books(); }
                else if (menuChoice == 5) {
                    FILE *fileloans;
                    store_loans(fileloans);
                    logged_in_index = -1;
                    printf("Successfully logged out. Reloading menu...\n");
                    mainMenu();
                }
            }
        }
    }
    else if(logged_in_index == -1) {
            printf("\nPlease Choose an Option:\n1) Register an account\n2) Login\n3) Search for books\n4) Display all books\n5) Quit\n Option:");
            int menuChoice = 0;
            char enter;
            //validation on menu_choice to ensure its an integer
            if (scanf("%i%c", &menuChoice, &enter) != 2 || enter != '\n') {
                printf("\nSorry, the option you entered was invalid, please try again.\n");
                fflush(stdin);
                mainMenu();
            } else {
                if (menuChoice == 1) {
                    //pre register setup

                    //name setup
                    printf("\nPlease enter your name (NB letters only, max length 30): ");
                    char name[MAX_NAME_LENGTH];
                    fgets(name, MAX_NAME_LENGTH, stdin);
                    //remove trailing newline
                    if ((strlen(name) > 0) && (name[strlen(name) - 1] == '\n')) {
                        name[strlen(name) - 1] = '\0';
                    }
                    int name_ok = 1;
                    int p = strlen(name);
                    for (int i = 0; i < p; ++i) {
                        if (isalpha(name[i]) == 0) { name_ok = 0; }
                    }
                    if (name_ok == 0) {
                        printf("Inputted name was invalid! Reloading menu...\n");
                        mainMenu();
                    }
                    //maybe validate password?
                    printf("Please enter a password (NB all characters allowed, max length 30): ");
                    char password[30];
                    fgets(password, 30, stdin);
                    //remove trailing newline
                    if ((strlen(password) > 0) && (password[strlen(password) - 1] == '\n')) {
                        password[strlen(password) - 1] = '\0';
                    }
                    //setup email input
                    printf("Please enter a email address (NB please use name@example.com format): ");
                    char email[30];
                    fgets(email, 30, stdin);
                    //remove trailing newline
                    if ((strlen(email) > 0) && (email[strlen(email) - 1] == '\n')) {
                        email[strlen(email) - 1] = '\0';
                    }
                    //setup regex
                    regex_t regex;
                    int compile;
                    compile = regcomp(&regex, ".+@.+\\..+", REG_EXTENDED);
                    if( compile ){
                        printf("Regex could not be compiled... Exiting menu...");
                        mainMenu();
                    }
                    //validate email
                    compile = regexec(&regex, email, 0, NULL, 0); //should return 0 if matches
                    if( compile != 0 ){
                        printf("Error: Email is invalid. Restarting Menu...\n");
                        mainMenu();
                    }
                    char * registerName = &name[0];
                    char * registerPassword = &password[0];
                    char * registerEmail = &email[0];
                    if (register_account(registerName, registerPassword, registerEmail) == 1) {
                        printf("Successfully logged in! Reloading menu...\n");
                        logged_in_index = userArray_index;
                        mainMenu();
                    } else if (register_account(name, password, email) == 0) {
                        printf("Register unsuccessful! The username you entered already exists. Reloading menu...\n");
                    }
                } else if (menuChoice == 2) {
                    //pre login setup

                    printf("\nPlease enter your username: ");
                    char username[30];
                    fgets(username, 30, stdin);
                    //remove trailing newline
                    if ((strlen(username) > 0) && (username[strlen(username) - 1] == '\n')) {
                        username[strlen(username) - 1] = '\0';
                    }
                    printf("Please enter a password: ");
                    char password[30];
                    fgets(password, 30, stdin);
                    //remove trailing newline
                    if ((strlen(password) > 0) && (password[strlen(password) - 1] == '\n')) {
                        password[strlen(password) - 1] = '\0';
                    }
                    int success = login(username, password);
                    if (success == 0) {
                        printf("No user found with that login info.\n");
                        printf("Login unsuccessful! Reloading Menu\n");
                        mainMenu();
                    }
                    else if (success == 1) {
                        printf("Successfully logged in...\n");
                    }
                }
                else if (menuChoice == 3) { search_books(); }
                else if (menuChoice == 4) { display_books(); }
                else if (menuChoice == 5) {
                    FILE *file;
                    store_users(file);
                    exit(0);
                }
            }
        }
    //if get to the end of menu without exit we should reload menu
    mainMenu();
}

void search_books(){
    //check that there are books in the library, if not load from the file
    if(bookArray_index == -1){
        FILE *file;
        load_books(file);
    }
    printf("\n\nLoading search menu...\n\n");
    printf("Please choose an option:\n1) Find books by title\n2) Find books by author\n3) Find books by year\n4) Return to previous menu\n Option: ");
    int menuChoice;
    char enter;
    //validation on menu_choice to ensure its an integer
    if(scanf("%i%c", &menuChoice, &enter) != 2 || enter != '\n'){
        printf("\nSorry, the option you entered was invalid, please try again.\n");
    }
    else{
        if(menuChoice == 1){
            printf("\nPlease enter title (NB Exact matches only): ");
            char usrImp[30];
            fgets(usrImp, 30, stdin);
            //remove trailing newline
            if ((strlen(usrImp) > 0) && (usrImp[strlen (usrImp) - 1] == '\n'))
                usrImp[strlen (usrImp) - 1] = '\0';
            find_book_by_title(usrImp);
        }
        else if (menuChoice == 2){
            printf("\nPlease enter author (NB Exact matches only): ");
            char usrImp[30];
            fgets(usrImp, 30, stdin);
            //remove trailing newline
            if ((strlen(usrImp) > 0) && (usrImp[strlen (usrImp) - 1] == '\n'))
                usrImp[strlen (usrImp) - 1] = '\0';
            find_book_by_author(usrImp);
        }
        else if (menuChoice == 3){
            printf("\nPlease enter year (NB Exact matches only): ");
            unsigned int usrInp;
            scanf("%u", &usrInp);
            find_book_by_year(usrInp);
        }
        else if (menuChoice == 4){mainMenu();}
    }
}

void display_books(){
    //check that there are books in the library, if not load from the file
    if(bookArray_index == -1){
        FILE *file;
        load_books(file);
    }
    //print the headers
    printf("\nId, Title, Authors, Year, Copies\n");
    //print the books
    for( int i = 0; i <= bookArray_index; i++){
        //print id
        printf("%i, ", storedbookArray[i]->id);
        //print title
        printf("%s, ", storedbookArray[i]->title);
        //print authors
        printf("%s, ", storedbookArray[i]->authors);
        //print year
        printf("%d, ", storedbookArray[i]->year);
        //print copies
        printf("%d\n", storedbookArray[i]->copies);
    }
    printf("\nReturning to main menu... \n");
    mainMenu();
}
