#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

int bookCount = 0;

/* Add some books only once */
void addDefaultBooks() {
    FILE *file = fopen("books.dat", "rb");

    if (file != NULL) {
        fclose(file);
        return;
    }

    file = fopen("books.dat", "wb");

    struct Book books[5] = {
        {1, "C Programming", "Dennis Ritchie", 5},
        {2, "Data Structures", "Seymour Lipschutz", 4},
        {3, "Operating Systems", "Silberschatz", 3},
        {4, "Computer Networks", "Tanenbaum", 6},
        {5, "Database Systems", "Elmasri", 2}
    };

    for (int i = 0; i < 5; i++) {
        fwrite(&books[i], sizeof(struct Book), 1, file);
    }

    fclose(file);
    bookCount = 5;
}

/* Count books from file */
void loadBooks() {
    FILE *file = fopen("books.dat", "rb");
    struct Book temp;

    if (file == NULL)
        return;

    bookCount = 0;
    while (fread(&temp, sizeof(temp), 1, file)) {
        bookCount++;
    }

    fclose(file);
}

void addBook() {
    struct Book book;
    book.id = ++bookCount;

    printf("Enter book title: ");
    fgets(book.title, 50, stdin);
    book.title[strcspn(book.title, "\n")] = 0;

    printf("Enter author name: ");
    fgets(book.author, 50, stdin);
    book.author[strcspn(book.author, "\n")] = 0;

    book.copies = getValidInt("Enter number of copies: ");

    FILE *file = fopen("books.dat", "ab");
    fwrite(&book, sizeof(book), 1, file);
    fclose(file);

    printf("Book added successfully.\n");
}

void viewBooks() {
    FILE *file = fopen("books.dat", "rb");
    struct Book book;

    if (file == NULL) {
        printf("No books found.\n");
        return;
    }

    printf("\nBook List:\n");
    while (fread(&book, sizeof(book), 1, file)) {
        printf("ID: %d | %s | %s | Copies: %d\n",
               book.id, book.title, book.author, book.copies);
    }

    fclose(file);
}

void searchBook() {
    int id = getValidInt("Enter book ID: ");
    FILE *file = fopen("books.dat", "rb");
    struct Book book;

    while (fread(&book, sizeof(book), 1, file)) {
        if (book.id == id) {
            printf("Book found: %s by %s\n", book.title, book.author);
            fclose(file);
            return;
        }
    }

    printf("Book not found.\n");
    fclose(file);
}

void updateBook() {
    int id = getValidInt("Enter book ID to update: ");
    FILE *file = fopen("books.dat", "rb+");
    struct Book book;

    while (fread(&book, sizeof(book), 1, file)) {
        if (book.id == id) {
            printf("Enter new title: ");
            fgets(book.title, 50, stdin);
            book.title[strcspn(book.title, "\n")] = 0;

            printf("Enter new author: ");
            fgets(book.author, 50, stdin);
            book.author[strcspn(book.author, "\n")] = 0;

            book.copies = getValidInt("Enter new copies: ");

            fseek(file, -sizeof(book), SEEK_CUR);
            fwrite(&book, sizeof(book), 1, file);
            fclose(file);

            printf("Book updated.\n");
            return;
        }
    }

    printf("Book not found.\n");
    fclose(file);
}

void deleteBook() {
    int id = getValidInt("Enter book ID to delete: ");
    FILE *file = fopen("books.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    struct Book book;
    int found = 0;

    while (fread(&book, sizeof(book), 1, file)) {
        if (book.id == id)
            found = 1;
        else
            fwrite(&book, sizeof(book), 1, temp);
    }

    fclose(file);
    fclose(temp);

    remove("books.dat");
    rename("temp.dat", "books.dat");

    if (found)
        printf("Book deleted.\n");
    else
        printf("Book not found.\n");
}

void issueBook() {
    int id = getValidInt("Enter book ID: ");
    FILE *file = fopen("books.dat", "rb+");
    struct Book book;

    while (fread(&book, sizeof(book), 1, file)) {
        if (book.id == id && book.copies > 0) {
            book.copies--;
            fseek(file, -sizeof(book), SEEK_CUR);
            fwrite(&book, sizeof(book), 1, file);
            fclose(file);

            printf("Book issued.\n");
            return;
        }
    }

    printf("Book not available.\n");
    fclose(file);
}

void returnBook() {
    int id = getValidInt("Enter book ID: ");
    FILE *file = fopen("books.dat", "rb+");
    struct Book book;

    while (fread(&book, sizeof(book), 1, file)) {
        if (book.id == id) {
            book.copies++;
            fseek(file, -sizeof(book), SEEK_CUR);
            fwrite(&book, sizeof(book), 1, file);
            fclose(file);

            printf("Book returned.\n");
            return;
        }
    }

    printf("Book not found.\n");
    fclose(file);
}
