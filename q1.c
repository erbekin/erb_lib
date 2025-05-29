#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TITLE_LEN 100
#define AUTHOR_LEN 100

typedef struct {
    int book_id;
    char title[TITLE_LEN];
    char author[AUTHOR_LEN];
    bool is_checked_out;
} Book;

// Part 1
int findBookIndex(Book *catalog, int count, int id);
void addBook(Book **catalog, int *count);
void viewBook(Book *catalog, int count);
void checkoutBook(Book *catalog, int count);
void returnBook(Book *catalog, int count);
// Part 2
void saveToFile(Book *catalog, int count, const char *filename);
void loadFromFile(Book **catalog, int *count, const char *filename);

int main() {
    int choice;
    Book *catalog = NULL;
    int count = 0;

    while (1) {
        printf("\n=== Library Catalog Menu ===\n");
        printf("1. Add Book\n");
        printf("2. View Book\n");
        printf("3. Check Out Book\n");
        printf("4. Return Book\n");
        printf("5. Save Catalog to File\n");
        printf("6. Load Catalog from File\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // buffer temizliği

        switch (choice) {
            case 1:
                addBook(&catalog, &count);
                break;
            case 2:
                viewBook(catalog, count);
                break;
            case 3:
                checkoutBook(catalog, count);
                break;
            case 4:
                returnBook(catalog, count);
                break;
            case 5:
                saveToFile(catalog, count, "catalog.txt");
                break;
            case 6:
                loadFromFile(&catalog, &count, "catalog.txt");
                break;
            case 7:
                free(catalog);
                return EXIT_SUCCESS;
            default:
                printf("Invalid choice.\n");
        }
    }
}

void addBook(Book **catalog, int *count) {
    Book newBook;
    printf("Enter book ID: ");
    scanf("%d", &newBook.book_id);
    getchar();
    printf("Enter title: ");
    fgets(newBook.title, TITLE_LEN, stdin);
    newBook.title[strcspn(newBook.title, "\n")] = '\0'; // newline kaldır
    printf("Enter author: ");
    fgets(newBook.author, AUTHOR_LEN, stdin);
    newBook.author[strcspn(newBook.author, "\n")] = '\0'; // newline kaldır
    newBook.is_checked_out = false;

    *catalog = realloc(*catalog, (*count + 1) * sizeof(Book));
    (*catalog)[*count] = newBook;
    (*count)++;
    printf("Book added successfully.\n");
}

int findBookIndex(Book *catalog, int count, int id) {
    for (int i = 0; i < count; i++) {
        if (catalog[i].book_id == id) {
            return i;
        }
    }
    return -1;
}

void viewBook(Book *catalog, int count) {
    int id;
    printf("Enter book ID to view: ");
    scanf("%d", &id);
    int index = findBookIndex(catalog, count, id);
    if (index != -1) {
        printf("Book ID: %d\nTitle: %s\nAuthor: %s\nStatus: %s\n",
               catalog[index].book_id,
               catalog[index].title,
               catalog[index].author,
               catalog[index].is_checked_out ? "Checked Out" : "Available");
    } else {
        printf("Book not found.\n");
    }
}

void checkoutBook(Book *catalog, int count) {
    int id;
    printf("Enter book ID to check out: ");
    scanf("%d", &id);
    int index = findBookIndex(catalog, count, id);
    if (index != -1) {
        if (!catalog[index].is_checked_out) {
            catalog[index].is_checked_out = true;
            printf("Book checked out.\n");
        } else {
            printf("Book is already checked out.\n");
        }
    } else {
        printf("Book not found.\n");
    }
}

void returnBook(Book *catalog, int count) {
    int id;
    printf("Enter book ID to return: ");
    scanf("%d", &id);
    int index = findBookIndex(catalog, count, id);
    if (index != -1) {
        if (catalog[index].is_checked_out) {
            catalog[index].is_checked_out = false;
            printf("Book returned.\n");
        } else {
            printf("Book was not checked out.\n");
        }
    } else {
        printf("Book not found.\n");
    }
}

void saveToFile(Book *catalog, int count, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Unable to open file for writing");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d|%s|%s|%d\n",
                catalog[i].book_id,
                catalog[i].title,
                catalog[i].author,
                catalog[i].is_checked_out);
    }

    fclose(file);
    printf("Catalog saved to file.\n");
}

void loadFromFile(Book **catalog, int *count, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open file for reading");
        return;
    }

    free(*catalog);
    *catalog = NULL;
    *count = 0;

    Book temp;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d|%99[^|]|%99[^|]|%d\n",
                   &temp.book_id, temp.title, temp.author, (int *)&temp.is_checked_out) == 4) {
            *catalog = realloc(*catalog, (*count + 1) * sizeof(Book));
            (*catalog)[*count] = temp;
            (*count)++;
        }
    }

    fclose(file);
    printf("Catalog loaded from file.\n");
}