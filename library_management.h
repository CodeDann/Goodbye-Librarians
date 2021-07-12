//
// Created by Jake Noar on 27/02/2021.
//

#ifndef PPCW1_LIBRARY_MANAGEMENT_H
#define PPCW1_LIBRARY_MANAGEMENT_H

#endif //PPCW1_LIBRARY_MANAGEMENT_H


struct Loan{
    int id;
    char *title;
    char *borrowed_by;
};

//function to borrow books based on id
//returns 0 if there was an error borrowing
//returns -1 if the user has already borrowed the book
//returns 1 if book was borrowed correctly
int borrow_book(int id);

//function to return a book that the user has already borrowed
//returns 1 if successful
//returns 0 if not
int return_book(int id);

//function to store any outstanding loans into a text file "loan_store.txt" to ensure persistence
//returns 0 when finished
int store_loans(FILE *file);

//function to load all loans from a store in a text file "loan_store.txt" ensuring persistence
//returns 1 if there are no loans
//returns 0 when done loading
int load_loans(FILE *file);

//function to display all outstanding loans a particular user has
void display_loans();

//global variables for storing all borrowed books
extern struct Loan * borrowedBooks[ ];
extern int borrowedBooks_index;