#include "contacts.h"
#include "validation.h"

#include <stdio.h>
#include <string.h>

 

// ::::::::Function to create a new contact:::::::::
void createContact(contact contacts[],int *count)
{
    if (*count >= MAX_CONTACTS)             // check if address book is full
    {
        printf("## Address book full!\n");
        return ;                           // simple return used to exit the function. usually used in void functions
    }

    contact newContact ;                  // a variable named 'newContact' is created in contact(structure)
    do
    {
        printf("\nEnter name : ");
        scanf("%[^\n]", newContact.name);
        while(getchar()!='\n');
    } while (!validateName(newContact.name));

    do 
    {
        printf("Enter phone (10 digits): ");
        scanf("%s", newContact.phone);  // limit input to 10 characters
        while(getchar()!='\n');           // to clear the leftover line in buffer
    } while (!validatePhone(newContact.phone, contacts, *count));

    do 
    {
        printf("Enter email: ");
        scanf(" %[^\n]", newContact.email);
        while(getchar()!='\n');
    } while (!validateEmail(newContact.email , contacts, *count));

    contacts[(*count)++] = newContact;           //copies the values stored in the structure variable 'newContact' to the structure array contacts 
    printf("\n>> Contact added successfully!\n");
}

// ::::::::::Function to search for a contact:::::::::
void searchContact(contact contacts[], int count) 
{
    if (count == 0)                                 // check if there are any contacts
    {
        printf("\n## No contacts available.\n");
        return;
    }

    int choice , found = 0;
    char query[50];
    printf("\n----- Search Contact Menu -----\n");
    printf(".                             .\n");
    printf(".  Search by:                 .\n");                          //menu for search options
    printf(".  [1] Name                   .\n");
    printf(".  [2] Phone                  .\n");
    printf(".  [3] Email                  .\n");
    printf("...............................\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    getchar();

    if (choice < 1 || choice > 3)                    // Validate choice
    {
        printf("\n## Invalid choice.\n");
        return;
    }

    if (choice == 1) 
    {   
        printf("\nEnter the Name : ");                       
        scanf(" %[^\n]", query);  
        while(getchar()!='\n');                                               
        for (int i = 0; i < count; i++) 
        {
            if (strcasecmp(contacts[i].name, query) == 0 ) 
            {
                printf("\n>> Found: %s | %s | %s\n",contacts[i].name, contacts[i].phone, contacts[i].email);
                found = 1;
            }
        }
    } 
    else if (choice == 2) 
    {    
        printf("\nEnter the Phone number : ");                       
        scanf(" %[^\n]", query);
        while(getchar()!='\n');                                                     
        for (int i = 0; i < count; i++) 
        {
            if (strcmp(contacts[i].phone, query) == 0) 
            {
                printf("\n>> Found: %s | %s | %s\n",contacts[i].name, contacts[i].phone, contacts[i].email);
                found = 1;
            }
        }
    } 
    else if (choice == 3) 
    {     
        printf("\nEnter the Email : ");                       
        scanf(" %[^\n]", query);
        while(getchar()!='\n');
        for (int i = 0; i < count; i++) 
        {
            if (strcasecmp(contacts[i].email, query) == 0) 
            {
                printf("\n>> Found: %s | %s | %s\n",contacts[i].name, contacts[i].phone, contacts[i].email);
                found = 1;
            }
        }
    } 
    
    if (!found) 
        printf("\n## No contact found.\n");
}

//::::::::::::::::Function to edit a contact::::::::
void editContact(contact contacts[], int count)
{
    if (count == 0)                                    // check if there are any contacts
    {
        printf("\n## No contacts available.\n");
        return;
    }

    int choice;
    while (1)                                   // infinite loop to allow multiple edits until user chooses to exit
    {
        printf("\n\n------ Edit Contact Menu ------\n");
        printf(".                             .\n");
        printf(".  Edit Contact By:           .\n");
        printf(".  [1] Name                   .\n");
        printf(".  [2] Phone                  .\n");
        printf(".  [3] Email                  .\n");
        printf(".  [4] Return to Main         .\n");
        printf("...............................\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        while(getchar()!='\n');

        if (choice == 1)                           // Edit by name
        {
            listContacts(contacts, count);                                    // Display contacts with index numbers
            printf("\nEnter the index number of the contact to edit name: ");
            int index;
            scanf("%d", &index);
            while(getchar()!='\n');
            if (index < 1 || index > count)            // Validate index
            {
                printf("\n## Invalid index.\n");
                continue;
            }
            index--;                        //converting index to 0 as array index starts from 0
            char newName[50];
            do 
            {
                printf("Enter new name: ");
                scanf("%[^\n]", newName);
                while(getchar()!='\n');
            } while (!validateName(newName));
            strcpy(contacts[index].name, newName);                 //saving the new name
            printf("\n>> Name updated successfully!\n");
        } 
        else if (choice == 2)                                  // Edit by phone
        {
            char phone[11]; 
            int index = -1   ;                             // to store the index of the found contact
            printf("\nEnter the phone number of the contact to edit: ");
            scanf("%10s", phone);
            while(getchar()!='\n');
            for (int i = 0; i < count; i++)                   // searching for the contact with the given phone number
            {
                if (strcmp(contacts[i].phone, phone) == 0)
                {
                    index = i;
                    break;
                }
            }
            if (index == -1)                            
            {
                printf("\n## Contact not found.\n");
                continue;                                    //continue again from the sub menu  (next iteration of while loop)
            }
            char newPhone[11];
            do 
            {
                printf("Enter new phone number : ");
                scanf("%10s", newPhone);
                while(getchar()!='\n');
            } while (!validatePhone(newPhone, contacts, count));

            strcpy(contacts[index].phone, newPhone);                   //saving the new phone number
            printf("\n>> Phone updated successfully!\n");
        } 
        else if (choice == 3)                                  // Edit by email
        {
            char email[30];
            int index = -1;
            printf("\nEnter the email of the contact to edit: ");
            scanf(" %[^\n]", email);
            while(getchar()!='\n');
            for (int i = 0; i < count; i++) 
            {
                if (strcasecmp(contacts[i].email, email) == 0)
                {
                    index = i;
                    break;
                }
            }
            if (index == -1) 
            {
                printf("\n## Contact not found.\n");
                continue;                                       //continue again from the sub menu  (next iteration of while loop)
            }
            char newEmail[30];
            do 
            {
                printf("Enter new email: ");
                scanf(" %[^\n]", newEmail);
            } while (!validateEmail(newEmail, contacts, count));
            strcpy(contacts[index].email, newEmail);
            printf("\n>> Email updated successfully!\n");
        } 
        else if (choice == 4) 
        {
            printf("\n>> Exiting edit menu.\n");
            break;                                   //exiting the infinite loop and returning to main menu
        } 
        else 
        {
            printf("\n## Invalid choice.\n");
        }
    }
}

//:::::::::::Function to delete a contact:::::::::::
void deleteContact(contact contacts[], int *count)
{
    if (*count == 0) 
    {
        printf("\n## No contacts to delete.\n");
        return;
    }
    int choice;
    while (1)                                   // infinite loop to allow multiple deletions until user chooses to exit
    {
        printf("\n----- Delete Contact Menu -----\n");
        printf(".                             .\n");
        printf(".  Delete Contact By:         .\n");
        printf(".  [1] Name                   .\n");
        printf(".  [2] Phone                  .\n");
        printf(".  [3] Email                  .\n");
        printf(".  [4] Return to Main         .\n");
        printf("...............................\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        while(getchar()!='\n');

    if (choice < 1 || choice > 4)      // Validate choice
    {
        printf("\n## Invalid choice.\n");
        return;
    }

    if (choice == 1)                           // Delete by name
    {
            listContacts(contacts, *count);                                    // Display contacts with index numbers
            printf("\nEnter the index number of the contact to delete: ");
            int index;
            scanf("%d", &index);
            while(getchar()!='\n');

            if (index < 1 || index > *count)            // Validate index
            {
                printf("\n## Invalid index.\n");
                continue;
            }
            index--;                              //converting index to 0 as array index starts from 0
            
            for (int j = index; j < *count - 1; j++)              // loop for shifting contacts
            {
                contacts[j] = contacts[j + 1];                  //shifting all contacts after the deleted one to the left
            }
            (*count)--;
            printf("\n>> Contact deleted successfully!\n");           
    }
    else if (choice == 2)
    {
        char phone[11];
        printf("\nEnter the phone number of the contact to delete: ");
        scanf("%10s", phone);
        while(getchar()!='\n');
        for (int i = 0; i < *count; i++)                 
        {
            if (strcmp(contacts[i].phone, phone) == 0) 
            {
                for (int j = i; j < *count - 1; j++)              // finding the contact to be deleted
                {
                    contacts[j] = contacts[j + 1];                  //shifting all contacts after the deleted one to the left
                }
                (*count)--;                                        //decreasing the count of contacts
                printf("\n>> Contact deleted successfully!\n");
                return;
            }
        }
        printf("\n## Contact not found.\n");
    }
    else if (choice == 3)
    {
        char email[30];
        printf("\nEnter the email of the contact to delete: ");
        scanf(" %[^\n]", email);
        while(getchar()!='\n');
        for (int i = 0; i < *count; i++)                 
        {
            if (strcasecmp(contacts[i].email, email) == 0) 
            {
                for (int j = i; j < *count - 1; j++)              // finding the contact to be deleted
                {
                    contacts[j] = contacts[j + 1];                  //shifting all contacts after the deleted one to the left
                }
                (*count)--;                                        //decreasing the count of contacts
                printf("\n>> Contact deleted successfully!\n");
                return;
            }
        }
        printf("\n## Contact not found.\n");
    }
    else if (choice == 4)
    {
        printf("\n>> Exiting delete menu.\n");
        break;                                   //exiting the infinite loop and returning to main menu
    }
    }
}

//:::::::::::Function to list all contacts:::::::::::  
void listContacts(contact contacts[], int count)        
{
    if (count == 0) 
    {
        printf("\n## No contacts available.\n");
        return;
    }

    printf("\n::::::::::::::::::::::::>> CONTACT LIST <<::::::::::::::::::::::::\n");
    for (int i = 0; i < count; i++) 
    {
        printf("\n%d. %s | %s | %s\n", i + 1, contacts[i].name, contacts[i].phone, contacts[i].email);
    }
    printf("\n------------------------------------------------------------------\n");
}

//:::::::::::Function to save contacts to a file:::::::::::
void saveContacts(contact contacts[], int count) 
{
    FILE *fp = fopen("Addressbookcontacts.csv", "w");  // write mode
    if (fp == NULL) 
    {
        printf("\n## Error opening file for writing!\n");
        return;
    }

    for (int i = 0; i < count; i++) 
    {
        fprintf(fp, "%s,%s,%s\n", contacts[i].name, contacts[i].phone, contacts[i].email);
    }

    fclose(fp);
    printf("\n>> Contacts saved successfully \n");
}

//:::::::::::Function to load contacts from a file:::::::::::
void loadContacts(contact contacts[], int *count) 
{
    FILE *fp = fopen("Addressbookcontacts.csv", "r");
    if (fp == NULL) 
        return;   
    

    int read;       // to store the return value of fscanf
    while (1) 
    {
        read = fscanf(fp, "%49[^,],%10[^,],%29[^\n]\n",contacts[*count].name,contacts[*count].phone, contacts[*count].email);

        if (read != 3)    //if fscanf return EOF or doesn't read exactly 3 items
            break;

        (*count)++;         // increment count for each successfully read contact 

        if (*count >= MAX_CONTACTS)
            break;
    }

    fclose(fp);
}