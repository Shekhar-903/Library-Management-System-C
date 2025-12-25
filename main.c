#include <stdlib.h>
#include "library.h"

int main() {
    int choice;

    addDefaultBooks();
    loadBooks();

    while (1) {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. View Books\n");
        printf("3. Search Book\n");
        printf("4. Update Book\n");
        printf("5. Delete Book\n");
        printf("6. Issue Book\n");
        printf("7. Return Book\n");
        printf("8. Exit\n");

        choice = getValidInt("Enter your choice: ");

        switch (choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: searchBook(); break;
            case 4: updateBook(); break;
            case 5: deleteBook(); break;
            case 6: issueBook(); break;
            case 7: returnBook(); break;
            case 8: exit(0);
            default: printf("Invalid choice.\n");
        }
    }
}
