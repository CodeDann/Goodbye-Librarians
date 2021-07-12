#include <stdio.h>
#include <string.h>
#include "user_management.h"
#include "interface.h"
#include "book_management.h"
#include "library_management.h"

int main(){
    //setup the library from stores
    FILE *filebooks;
    FILE *fileusers;
    FILE *fileloans;
    load_books(filebooks);
    load_users(fileusers);
    load_loans(fileloans);
    // now run the main menu

    mainMenu();
}

