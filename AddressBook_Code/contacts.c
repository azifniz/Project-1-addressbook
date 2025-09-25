#include "contacts.h"
#include "validation.h"

#include <stdio.h>
#include <string.h>


// ::::::::Function to create a new contact:::::::::
void createContact(contact contacts[],int *count)
{
    if (*count >= MAX_CONTACTS)                                            // check if address book is full
    {
        printf("\033[1;31m## Address book full!\033[0m\n");
        return ;                           
    }

    contact newContact ;                                                   // a variable named 'newContact' is created in contact(structure)
    do
    {
        printf("\n\033[1;36mEnter name : \033[0m");                        //getting name and validating it
        scanf("%[^\n]", newContact.name);
        while(getchar()!='\n');
    } while (!validateName(newContact.name));

    do 
    {
        printf("\n\033[1;36mEnter phone (10 digits): \033[0m");            //getting phone number and validating it
        scanf("%s", newContact.phone);  
        while(getchar()!='\n');           
    } while (!validatePhone(newContact.phone, contacts, *count));

    do 
    {
        printf("\n\033[1;36mEnter email: \033[0m");                        //getting email and validating it
        scanf(" %[^\n]", newContact.email);
        while(getchar()!='\n');
    } while (!validateEmail(newContact.email , contacts, *count));

    contacts[(*count)++] = newContact;                                     //copies the values stored in the structure variable 'newContact' to the structure array contacts 
    printf("\n\033[1;32m>> Contact added successfully!\033[0m\n");
}

// ::::::::::Function to search for a contact:::::::::
void searchContact(contact contacts[], int count) 
{
    if (count == 0)                                                       // check if there are any contacts
    {
        printf("\n\033[1;31m## No contacts available.\033[0m\n");
        return;
    }

    int choice , found = 0;
    while (1)
    {
        char query[50];
        printf("\033[1;97m");
        printf("\n╭────\033[0m \033[1;92mSearch Contact Menu\033[0m \033[1;97m────╮\n");
        printf("│                             │\n");
        printf("│  Search by:                 │\n");                     //menu for search options
        printf("│  [1] Name                   │\n");
        printf("│  [2] Phone                  │\n");
        printf("│  [3] Email                  │\n");
        printf("│  [4] Return to Main         │\n");
        printf("╰─────────────────────────────╯\n");
        printf("\nEnter your choice: \033[0m");
        scanf("%d", &choice);
        while(getchar()!='\n');

        if (choice == 1)                                                // Search by name
        {   
            printf("\n\033[1;36mEnter the Name : \033[0m");                       
            scanf(" %[^\n]", query);  
            while(getchar()!='\n');  

            for (int i = 0; i < count; i++)                             //loop to search the contact by name
            {
                if (strcasecmp(contacts[i].name, query) == 0 ) 
                {
                    printf("\n\033[1;32m>> Found:\033[0m \033[38;2;255;180;50m%s | %s | %s\033[0m\n",contacts[i].name, contacts[i].phone, contacts[i].email);
                    found = 1;
                }
            }
        }
        else if (choice == 2)                                           // Search by phone
        {    
            printf("\n\033[1;36mEnter the Phone number : \033[0m");                       
            scanf(" %[^\n]", query);
            while(getchar()!='\n');     

            for (int i = 0; i < count; i++)                             //loop to search the contact by phone
            {
                if (strcmp(contacts[i].phone, query) == 0) 
                {
                    printf("\n\033[1;32m>> Found:\033[0m \033[38;2;255;180;50m%s | %s | %s\033[0m\n",contacts[i].name, contacts[i].phone, contacts[i].email);
                    found = 1;
                }
            }
        }    
        else if (choice == 3)                                           // Search by email
        {     
            printf("\n\033[1;36mEnter the Email : \033[0m");                       
            scanf(" %[^\n]", query);
            while(getchar()!='\n');

            for (int i = 0; i < count; i++)                             //loop to search the contact by email
            {
                if (strcasecmp(contacts[i].email, query) == 0) 
                {
                    printf("\n\033[1;32m>> Found:\033[0m \033[38;2;255;180;50m%s | %s | %s\033[0m\n",contacts[i].name, contacts[i].phone, contacts[i].email);
                    found = 1;
                }
            }
        }
        else if (choice == 4)                                           // Return to Main
        {
            printf("\n>> Exiting search menu.\n");
            break;                                  
        }
        else 
        {
            printf("\n\033[1;31m## Invalid choice.\033[0m\n");
            choice = 0;
            continue;                                                   //continue again from the sub menu  (next iteration of while loop)
        }
    
        if (!found) 
            printf("\n\033[1;31m## No contact found.\033[0m\n");
        choice = 0;                                                     //resetting choice for next search
        found = 0;                                                      //resetting found for next search
    }
}

//::::::::::::::::Function to edit a contact::::::::
void editContact(contact contacts[], int count)
{
    if (count == 0)                                                     // check if there are any contacts
    {
        printf("\n\033[1;31m## No contacts available.\033[0m\n");
        return;
    }

    int choice;
    while (1)                                                           // infinite loop to allow multiple edits until user chooses to exit
    {
        printf("\033[1;97m");
        printf("\n\n╭─────\033[0m \033[1;92mEdit Contact Menu\033[0m \033[1;97m─────╮\n");
        printf("│                             │\n");
        printf("│  Edit Contact By:           │\n");
        printf("│  [1] Name                   │\n");
        printf("│  [2] Phone                  │\n");
        printf("│  [3] Email                  │\n");
        printf("│  [4] Return to Main         │\n");
        printf("╰─────────────────────────────╯\n");
        printf("\nEnter your choice: \033[0m");
        scanf("%d", &choice);
        while(getchar()!='\n');

        if (choice == 1)                                                // Edit by name
        {
            listContacts(contacts, count);                              // Display contacts with index numbers
            printf("\n\033[1;36mEnter the index number of the contact to edit name: \033[0m");
            int index;
            scanf("%d", &index);
            while(getchar()!='\n');

            if (index < 1 || index > count)                             // Validate index
            {
                printf("\n\033[1;31m## Invalid index.\033[0m\n");
                continue;
            }                                                           //converting index to 0 as array index starts from 0

            char newName[50];
            do 
            {
                printf("\n\033[1;36mEnter new name: \033[0m");
                scanf("%[^\n]", newName);
                while(getchar()!='\n');
            } while (!validateName(newName));
            strcpy(contacts[index].name, newName);                      //saving the new name
            printf("\n\033[1;32m>> Name updated successfully!\033[0m\n");
        } 
        else if (choice == 2)                                           // Edit by phone
        {
            char phone[11];  
            int index = -1   ;                                          // to store the index of the found contact
            printf("\n\033[1;36mEnter the phone number of the contact to edit: \033[0m");
            scanf("%10s", phone);
            while(getchar()!='\n');
            for (int i = 0; i < count; i++)                             // searching for the contact with the given phone number
            {
                if (strcmp(contacts[i].phone, phone) == 0)
                {
                    index = i;
                    break;
                }
            }
            if (index == -1)                            
            {
                printf("\n\033[1;31m## Contact not found.\033[0m\n");
                continue;                                               //continue again from the sub menu  (next iteration of while loop)
            }
            char newPhone[11];
            do 
            {
                printf("\n\033[1;36mEnter new phone number : \033[0m");
                scanf("%10s", newPhone);
                while(getchar()!='\n');
            } while (!validatePhone(newPhone, contacts, count));

            strcpy(contacts[index].phone, newPhone);                   //saving the new phone number
            printf("\n\033[1;32m>> Phone updated successfully!\033[0m\n");
        } 
        else if (choice == 3)                                          // Edit by email
        {
            char email[30];
            int index = -1;
            printf("\n\033[1;36mEnter the email of the contact to edit: \033[0m");
            scanf(" %[^\n]", email);
            while(getchar()!='\n');

            for (int i = 0; i < count; i++)                           // searching for the contact with the given email
            {
                if (strcasecmp(contacts[i].email, email) == 0)
                {
                    index = i;
                    break;
                }
            }
            if (index == -1) 
            {
                printf("\n\033[1;31m## Contact not found.\033[0m\n");
                continue;                                             //continue again from the sub menu  (next iteration of while loop)
            }
            char newEmail[30];
            do 
            {
                printf("\n\033[1;36mEnter new email: \033[0m");
                scanf(" %[^\n]", newEmail);
            } while (!validateEmail(newEmail, contacts, count));
            strcpy(contacts[index].email, newEmail);
            printf("\n\033[1;32m>> Email updated successfully!\033[0m\n");
        } 
        else if (choice == 4) 
        {
            printf("\n>> Exiting edit menu.\n");
            break;                                                    //exiting the infinite loop and returning to main menu
        } 
        else 
        {
            printf("\n\033[1;31m## Invalid choice.\033[0m\n");
        }
    }
}

//:::::::::::Function to delete a contact:::::::::::
void deleteContact(contact contacts[], int *count)
{
    if (*count == 0) 
    {
        printf("\n\033[1;31m## No contacts to delete.\033[0m\n");
        return;
    }
    int choice;
    while (1)                                                        // infinite loop to allow multiple deletions until user chooses to exit
    {
        printf("\n╭──── \033[0m\033[1;92mDelete Contact Menu \033[0m\033[1;97m────╮\n");
        printf("│                             │\n");
        printf("│  Delete Contact By:         │\n");
        printf("│  [1] Name                   │\n");
        printf("│  [2] Phone                  │\n");
        printf("│  [3] Email                  │\n");
        printf("│  [4] Return to Main         │\n");
        printf("╰─────────────────────────────╯\n");
        printf("\nEnter your choice: \033[0m");
        scanf("%d", &choice);
        while(getchar()!='\n');

    if (choice < 1 || choice > 4)                                    // Validate choice
    {
        printf("\n\033[1;31m## Invalid choice.\033[0m\n");
        return;
    }

    if (choice == 1)                                                 // Delete by name
    {
            listContacts(contacts, *count);                          // Display contacts with index numbers
            printf("\n\033[1;36mEnter the index number of the contact to delete: \033[0m");
            int index;
            scanf("%d", &index);
            while(getchar()!='\n');

            if (index < 1 || index > *count)                         // Validate index
            {
                printf("\n\033[1;31m## Invalid index.\033[0m\n");
                continue;
            }
            index--;                                                 //converting index to 0 as array index starts from 0
            
            for (int j = index; j < *count - 1; j++)                 // loop for shifting contacts
            {
                contacts[j] = contacts[j + 1];                       //shifting all contacts after the deleted one to the left
            }
            (*count)--;
            printf("\n\033[1;32m>> Contact deleted successfully!\033[0m\n");           
    }
    else if (choice == 2)                                            // Delete by phone
    {
        char phone[11];
        printf("\n\033[1;36mEnter the phone number of the contact to delete: \033[0m");
        scanf("%10s", phone);
        while(getchar()!='\n');

        for (int i = 0; i < *count; i++)                             // loop to search the contact by phone
        {
            if (strcmp(contacts[i].phone, phone) == 0) 
            {
                for (int j = i; j < *count - 1; j++)                 //loop for shifting contacts
                {
                    contacts[j] = contacts[j + 1];                   //shifting all contacts after the deleted one to the left
                }
                (*count)--;                                          //decreasing the count of contacts
                printf("\n\033[1;32m>> Contact deleted successfully!\033[0m\n");
                return;
            }
        }
        printf("\n\033[1;31m## Contact not found.\033[0m\n");
    }
    else if (choice == 3)                    // Delete by email
    {
        char email[30];
        printf("\n\033[1;36mEnter the email of the contact to delete: \033[0m");
        scanf(" %[^\n]", email);
        while(getchar()!='\n');

        for (int i = 0; i < *count; i++)                            // loop to search the contact by email
        {
            if (strcasecmp(contacts[i].email, email) == 0) 
            {
                for (int j = i; j < *count - 1; j++)                //loop for shifting contacts
                {
                    contacts[j] = contacts[j + 1];                  //shifting all contacts after the deleted one to the left
                }
                (*count)--;                                         //decreasing the count of contacts
                printf("\n\033[1;32m>> Contact deleted successfully!\033[0m\n");
                return;
            }
        }
        printf("\n\033[1;31m## Contact not found.\033[0m\n");
    }
    else if (choice == 4)
    {
        printf("\n>> Exiting delete menu.\n");
        break;                                                     //exiting the infinite loop and returning to main menu
    }
    }
}

//:::::::::::Function to list all contacts:::::::::::  
void listContacts(contact contacts[], int count)        
{
    if (count == 0)                                               // check if there are any contacts
    {
        printf("\n\033[1;31m## No contacts available.\033[0m\n");
        return;
    }

    printf("\n\033[1;37m═══════════════════════════\033[0m \033[1;92mCONTACT LIST \033[0m\033[1;37m═══════════════════════════\033[0m\n");
    for (int i = 0; i < count; i++)                               // loop to print all contacts
    {
        printf("\n\033[38;2;255;180;50m%3d. %-20s | %-3s | %s\033[0m\n", i + 1, contacts[i].name, contacts[i].phone, contacts[i].email);
    }
    printf("\n\033[1;37m════════════════════════════════════════════════════════════════════\033[0m\n");
}

//:::::::::::Function to save contacts to a file:::::::::::
void saveContacts(contact contacts[], int count) 
{
    FILE *fp = fopen("Addressbookcontacts.csv", "w");              // write mode
    if (fp == NULL) 
    {
        printf("\n\033[1;31m## Error opening file for writing!\033[0m\n");
        return;
    }

    for (int i = 0; i < count; i++) 
    {
        fprintf(fp, "%s,%s,%s\n", contacts[i].name, contacts[i].phone, contacts[i].email);   // write each contact to the file
    }

    fclose(fp);
    printf("\n\033[1;32m>> Contacts saved successfully\033[0m\n");
}

//:::::::::::Function to load contacts from a file:::::::::::
void loadContacts(contact contacts[], int *count) 
{
    FILE *fp = fopen("Addressbookcontacts.csv", "r");              // read mode
    if (fp == NULL) 
        return;   
    

    int read;                                                     // to store the return value of fscanf
    while (1) 
    {
        read = fscanf(fp, "%49[^,],%10[^,],%29[^\n]\n",contacts[*count].name,contacts[*count].phone, contacts[*count].email);   // read a line from the file

        if (read != 3)                                            //if fscanf return EOF or doesn't read exactly 3 items
            break;

        (*count)++;                                               // increment count for each successfully read contact 

        if (*count >= MAX_CONTACTS)
            break;
    }

    fclose(fp);
}