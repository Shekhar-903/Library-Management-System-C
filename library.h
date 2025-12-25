#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdio.h>

/* Structure to store book details */
struct Book {
    int id;
    char title[50];
    char author[50];
    int copies;
};

/* Global count of books */
extern int bookCount;

/* Utility functions */
void clearBuffer();
int getValidInt(char message[]);

/* Book related functions */
void addDefaultBooks();
void loadBooks();
void addBook();
void viewBooks();
void searchBook();
void updateBook();
void deleteBook();
void issueBook();
void returnBook();

#endif
