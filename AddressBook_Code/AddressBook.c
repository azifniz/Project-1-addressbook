#include<stdio.h>
#include<string.h>   //for string functions
#include<ctype.h>   //for isalpha() and isdigit() functions   

#define MAX_CONTACTS 100 

typedef struct                       // structure design
{
    char name[50];
    char phone[11];
    char email[30];
}contact;                           // structure named contact

//------------------->FEATURE FUNCTION DECLARATIONS<------------------------------------
void createContact(contact contacts[], int *count);
void listContacts(contact contacts[], int count);
void searchContact(contact contacts[], int count);
void editContact(contact contacts[], int count);
void deleteContact(contact contacts[], int *count);


//------------------->VALIDATION FUNCTION DECLARATIONS<---------------------------------
int validateName(char name[]);
int validatePhone(char phone[], contact contacts[], int count);
int validateEmail(char email[], contact contacts[], int count);

//----------------------   -->>MAIN FUNCTION<<------------------------------------------
int main()
{
    contact contacts[MAX_CONTACTS];   //array named contacts
    int count = 0 ;                  // to count the number of contacts
    int choice ;

    while(1)                         // infinite loop to keep the program running until user chooses to exit
    {
        printf("\n::::::::: ADDRESS BOOK :::::::::\n\n");
        printf("1. Add contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. list contacts\n");
        printf("6. Exit \n");
        printf("................................\n");
        printf("Enter your choice : ");
        scanf("%d",&choice);
        while(getchar()!='\n');        // to clear the leftover line in buffer

        switch (choice)
        {
        case 1:
            createContact(contacts, &count);    // function call
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
            printf("\n>>Exiting...\n");
            return 0;
        
        default:
            printf("\n#Invalid choice : Try again.\n");
        }
    }
}

//------------------------------------------------>>FEATURES<<----------------------------------------------------------------

// ::::::::Function to create a new contact:::::::::
void createContact(contact contacts[],int *count)
{
    if (*count >= MAX_CONTACTS)             // check if address book is full
    {
        printf("Address book full!\n");
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
        scanf("%10s", newContact.phone);  // limit input to 10 characters
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
        printf("\n#No contacts available.\n");
        return;
    }

    int choice , found = 0;
    char query[50];
    printf("\nSearch by: \n");                          //menu for search options
    printf("1.Name  \n");
    printf("2.Phone  \n");
    printf("3.Email  \n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    getchar();

    if (choice < 1 || choice > 3)                    // Validate choice
    {
        printf("\n#Invalid choice.\n");
        return;
    }

    if (choice == 1) 
    {   
        printf("Enter the Name : ");                       
        scanf(" %[^\n]", query);  
        while(getchar()!='\n');                                               
        for (int i = 0; i < count; i++) 
        {
            if (strcasecmp(contacts[i].name, query) == 0 ) 
            {
                printf("\n>>Found: %s | %s | %s\n",contacts[i].name, contacts[i].phone, contacts[i].email);
                found = 1;
            }
        }
    } 
    else if (choice == 2) 
    {    
        printf("Enter the Phone number : ");                       
        scanf(" %[^\n]", query);
        while(getchar()!='\n');                                                     
        for (int i = 0; i < count; i++) 
        {
            if (strcmp(contacts[i].phone, query) == 0) 
            {
                printf("\n>>Found: %s | %s | %s\n",contacts[i].name, contacts[i].phone, contacts[i].email);
                found = 1;
            }
        }
    } 
    else if (choice == 3) 
    {     
        printf("Enter the Email : ");                       
        scanf(" %[^\n]", query);
        while(getchar()!='\n');
        for (int i = 0; i < count; i++) 
        {
            if (strcasecmp(contacts[i].email, query) == 0) 
            {
                printf("\n>>Found: %s | %s | %s\n",contacts[i].name, contacts[i].phone, contacts[i].email);
                found = 1;
            }
        }
    } 
    
    if (!found) 
        printf("\n#No contact found.\n");
}

//::::::::::::::::Function to edit a contact::::::::
void editContact(contact contacts[], int count)
{
    if (count == 0)                                    // check if there are any contacts
    {
        printf("\n#No contacts available.\n");
        return;
    }

    int choice;
    while (1)                                   // infinite loop to allow multiple edits until user chooses to exit
    {
        printf("\n---------- Edit Contact Menu ----------\n");
        printf("Edit Contact By:\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
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
                printf("\n#Invalid index.\n");
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
            printf("\n>>Name updated successfully!\n");
        } 
        else if (choice == 2)                                  // Edit by phone
        {
            char phone[11]; 
            int index = -1   ;                             // to store the index of the found contact
            printf("Enter the phone number of the contact to edit: ");
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
                printf("\n#Contact not found.\n");
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
            printf("\n>>Phone updated successfully!\n");
        } 
        else if (choice == 3)                                  // Edit by email
        {
            char email[30];
            int index = -1;
            printf("Enter the email of the contact to edit: ");
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
                printf("\n#Contact not found.\n");
                continue;                                       //continue again from the sub menu  (next iteration of while loop)
            }
            char newEmail[30];
            do 
            {
                printf("Enter new email: ");
                scanf(" %[^\n]", newEmail);
            } while (!validateEmail(newEmail, contacts, count));
            strcpy(contacts[index].email, newEmail);
            printf("\n>>Email updated successfully!\n");
        } 
        else if (choice == 4) 
        {
            printf("Exiting edit menu.\n");
            break;                                   //exiting the infinite loop and returning to main menu
        } 
        else 
        {
            printf("\n#Invalid choice.\n");
        }
    }
}

//:::::::::::Function to delete a contact:::::::::::
void deleteContact(contact contacts[], int *count)
{
    if (*count == 0) 
    {
        printf("\n#No contacts to delete.\n");
        return;
    }
    int choice;
    while (1)                                   // infinite loop to allow multiple deletions until user chooses to exit
    {
    printf("\n---------- Delete Contact Menu ----------\n");
        printf("Delete Contact By:\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while(getchar()!='\n');

    if (choice < 1 || choice > 4)      // Validate choice
    {
        printf("\n#Invalid choice.\n");
        return;
    }

    if (choice == 1)
    {
        char name[50];
        printf("Enter the name of the contact to delete: ");
        scanf(" %[^\n]", name);
        while(getchar()!='\n');
        for (int i = 0; i < *count; i++)                 
        {
            if (strcasecmp(contacts[i].name, name) == 0) 
            {
                for (int j = i; j < *count - 1; j++)              // finding the contact to be deleted
                {
                    contacts[j] = contacts[j + 1];                  //shifting all contacts after the deleted one to the left
                }
                (*count)--;                                        //decreasing the count of contacts
                printf("\n>>Contact deleted successfully!\n");
                return;
            }
        }
        printf("\n#Contact not found.\n");
    }
    else if (choice == 2)
    {
        char phone[11];
        printf("Enter the phone number of the contact to delete: ");
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
                printf("\n>>Contact deleted successfully!\n");
                return;
            }
        }
        printf("\n#Contact not found.\n");
    }
    else if (choice == 3)
    {
        char email[30];
        printf("Enter the email of the contact to delete: ");
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
                printf("\n>>Contact deleted successfully!\n");
                return;
            }
        }
        printf("\n#Contact not found.\n");
    }
    else if (choice == 4)
    {
        printf("Exiting delete menu.\n");
        break;                                   //exiting the infinite loop and returning to main menu 
    }
    }
}

//:::::::::::Function to list all contacts:::::::::::  
void listContacts(contact contacts[], int count)        
{
    if (count == 0) 
    {
        printf("\n#No contacts available.\n");
        return;
    }

    printf("\n::::::::::::::::>> CONTACT LIST <<::::::::::::::::\n");
    for (int i = 0; i < count; i++) 
    {
        printf("\n%d. %s | %s | %s\n", i + 1, contacts[i].name, contacts[i].phone, contacts[i].email);
    }
    printf("\n---------------------------------------------------\n");
}

//---------------------------------------------->>VALIDATION<<-----------------------------------------------------------------
// Name validation function
int validateName(char name[]) 
{
    for (int i = 0; name[i] != '\0'; i++)                         // to check if all characters are alphabets or space
    {
        if (!isalpha(name[i]) && name[i] != ' ') 
        {
            printf("\n# Invalid! : Use alphabets and spaces only.\n");
            return 0;
        }
    }
    return 1;
}

// Phone validation function
int validatePhone(char phone[], contact contacts[], int count)        
{
    if (strlen(phone) != 10)                                      // to check the length of phone number
    {
        printf("\n# Invalid! The phone number Must be 10 digits.\n\n");
        return 0;
    }

    for (int i = 0; phone[i] != '\0'; i++)                        // to check if all characters are digits
    {
        if (!isdigit(phone[i])) 
        {
            printf("\n# Invalid! The phone number must contain only digits.\n\n");
            return 0;
        }
    }

    for (int i = 0; i < count; i++)                              // to check for duplicate phone numbers
    {
        if (strcmp(contacts[i].phone, phone) == 0) 
        {
            printf("\n# Error! This phone number already exists.\n\n");
            return 0;
        }
    }

    return 1;
}

// Email validation function
int validateEmail(char email[], contact contacts[], int count)  
{
    const char *end = "@gmail.com";
    size_t emailLen = strlen(email);
    size_t endLen = strlen(end);

    if (emailLen <= endLen)                        // basic length check
    {
        printf("\n# Invalid! email too short.\n\n");
        return 0;
    }

    const char *ending = email + (emailLen - endLen);     // points to the end part of the email
    if (strcmp(ending, end) != 0) 
    {
        printf("\n# Invalid! email must end with @gmail.com\n\n");
        return 0;
    }

    for (size_t i = 0; i < emailLen - endLen; i++)          // check the local part of the email
    {
        char c = email[i];
        if (!(isalnum(c) || c == '_' || c == '.')) 
        {
            printf("\n# Invalid! character '%c'\n\n", c);
            return 0;
        }
    }

    for (int i = 0; i < count; i++)                      // check for duplicate emails
    {
        if (strcasecmp(contacts[i].email, email) == 0) 
        {
            printf("\n# Error! This email already exists.\n\n");
            return 0;
        }
    }
    return 1; 
}



