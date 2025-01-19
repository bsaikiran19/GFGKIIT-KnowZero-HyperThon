#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100

struct Book
{
    int id;
    char title[50];
    char author[50];
    char category[20]; // Category of the book
    int isIssued;      // 0 = Available, 1 = Issued
};

struct Book books[MAX_BOOKS];
int bookCount = 0;

void addBook()
{
    struct Book newBook;
    printf("Enter Book ID: ");
    scanf("%d", &newBook.id);
    printf("Enter Book Title: ");
    getchar(); // Consume leftover newline
    fgets(newBook.title, 50, stdin);
    newBook.title[strcspn(newBook.title, "\n")] = '\0'; // Remove newline
    printf("Enter Author: ");
    fgets(newBook.author, 50, stdin);
    newBook.author[strcspn(newBook.author, "\n")] = '\0';

    // Choose category
    printf("Select Category:\n");
    printf("1. Fiction\n2. Non-Fiction\n3. Biopic\n4. Educational\n");
    printf("Enter your choice: ");
    int categoryChoice;
    scanf("%d", &categoryChoice);
    switch (categoryChoice)
    {
    case 1:
        strcpy(newBook.category, "Fiction");
        break;
    case 2:
        strcpy(newBook.category, "Non-Fiction");
        break;
    case 3:
        strcpy(newBook.category, "Biopic");
        break;
    case 4:
        strcpy(newBook.category, "Educational");
        break;
    default:
        strcpy(newBook.category, "Unknown");
        break;
    }

    newBook.isIssued = 0; // Initially, the book is available
    books[bookCount++] = newBook;
    printf("Book added successfully!\n");
}

void deleteBook()
{
    int id;
    printf("Enter Book ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++)
    {
        if (books[i].id == id)
        {
            for (int j = i; j < bookCount - 1; j++)
            {
                books[j] = books[j + 1]; // Shift remaining books
            }
            bookCount--;
            printf("Book deleted successfully!\n");
            return;
        }
    }
    printf("Book not found.\n");
}

void issueBook()
{
    int id;
    printf("Enter Book ID to issue: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++)
    {
        if (books[i].id == id)
        {
            if (books[i].isIssued)
            {
                printf("Book is already issued.\n");
                return;
            }
            else
            {
                books[i].isIssued = 1;
                printf("Book issued successfully!\n");
                return;
            }
        }
    }
    printf("Book not found.\n");
}

void depositBook()
{
    int id;
    printf("Enter Book ID to deposit: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++)
    {
        if (books[i].id == id)
        {
            if (!books[i].isIssued)
            {
                printf("Book was not issued.\n");
                return;
            }
            else
            {
                books[i].isIssued = 0;
                printf("Book deposited successfully!\n");
                return;
            }
        }
    }
    printf("Book not found.\n");
}

void viewBooks()
{
    printf("\n%-10s %-30s %-30s %-15s %-10s\n",
           "Book ID", "Title", "Author", "Category", "Status");

    for (int i = 0; i < bookCount; i++)
    {
        printf("%-10d %-30s %-30s %-15s %-10s\n",
               books[i].id,
               books[i].title,
               books[i].author,
               books[i].category,
               books[i].isIssued ? "Issued" : "Available");
    }
}

void saveBooksToFile()
{
    FILE *file = fopen("library.dat", "wb");
    if (file)
    {
        fwrite(&bookCount, sizeof(int), 1, file);
        fwrite(books, sizeof(struct Book), bookCount, file);
        fclose(file);
        printf("Data saved successfully!\n");
    }
    else
    {
        printf("Error saving data!\n");
    }
}

void loadBooksFromFile()
{
    FILE *file = fopen("library.dat", "rb");
    if (file)
    {
        fread(&bookCount, sizeof(int), 1, file);
        fread(books, sizeof(struct Book), bookCount, file);
        fclose(file);
    }
}

int main()
{
    int choice;
    loadBooksFromFile();

    do
    {
        printf("\n\t==========  KnowZero MANAGEMENT AREA  ==========\t\n");
        printf("\t\t  1. Add Book\n");
        printf("\t\t  2. Delete Book\n");
        printf("\t\t  3. Issue Book\n");
        printf("\t\t  4. Deposit Book\n");
        printf("\t\t  5. View Books\n");
        printf("\t\t  6. Save and Exit\n");
        printf("\t\t  Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addBook();
            break;
        case 2:
            deleteBook();
            break;
        case 3:
            issueBook();
            break;
        case 4:
            depositBook();
            break;
        case 5:
            viewBooks();
            break;
        case 6:
            saveBooksToFile();
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    } while (1);

    return 0;
}
