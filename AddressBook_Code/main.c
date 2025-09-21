#include<stdio.h>
#include "contacts.h"
#include "validation.h"
 

int main()
{
    contact contacts[MAX_CONTACTS];                              //array named contacts
    int count = 0 ;                                              // to count the number of contacts
    int choice ;
    loadContacts(contacts, &count);                              // load existing contacts from file

    while(1)                                                     // infinite loop to keep the program running until user chooses to exit
    {
        printf("\n\033[1;97m");
        printf("╭─────────────────────────────╮\n");
        printf("│       \033[0m \033[1;92mADDRESS BOOK\033[0m \033[1;97m        │\n");
        printf("╞═════════════════════════════╡\n");
        printf("│                             │\n");
        printf("│  [1] Add contact            │\n");
        printf("│  [2] Search contact         │\n");
        printf("│  [3] Edit contact           │\n");
        printf("│  [4] Delete contact         │\n");
        printf("│  [5] List contacts          │\n");
        printf("│  [6] Save contacts          │\n");
        printf("│  [7] Exit                   │\n");
        printf("╰─────────────────────────────╯\n");
        printf("\nEnter your choice : \033[0m");
        scanf("%d",&choice);
        while(getchar()!='\n');                                  // to clear the leftover line in buffer

        switch (choice)
        {
        case 1:
            createContact(contacts, &count);                     // function calls
            break;
        case 2:
            searchContact(contacts, count);   
            break;
        case 3:
            editContact(contacts, count);
            break;
        case 4:
            deleteContact(contacts, &count);
            break;
        case 5:
            listContacts(contacts, count);
            break;
        case 6:
            saveContacts(contacts, count);
            break;
        case 7:
            return 0;                                           // exit the program
            break;
        default:
            printf("\n\033[1;31m## Invalid choice : Try again.\n\033[0m");
        }
    }
}