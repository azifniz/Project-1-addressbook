#include "validation.h"

// Name validation function
int validateName(char name[]) 
{
    if (name[0] == ' ')
    {
        printf("\n## Invalid! Name cannot start with a space.\n");
        return 0;
    }
    if (strlen(name) == 0)                                       // to check if name is empty
    {
        printf("\n## Invalid! Name cannot be empty.\n");
        return 0;
    }
    for (int i = 0; name[i] != '\0'; i++)                         // to check if all characters are alphabets or space
    {
        if (!isalpha(name[i]) && name[i] != ' ') 
        {
            printf("\n## Invalid! : Use alphabets and spaces only.\n");
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
        printf("\n## Invalid! The phone number Must be 10 digits.\n\n");
        return 0;
    }

    for (int i = 0; phone[i] != '\0'; i++)                        // to check if all characters are digits
    {
        if (!isdigit(phone[i])) 
        {
            printf("\n## Invalid! The phone number must contain only digits.\n\n");
            return 0;
        }
    }

    for (int i = 0; i < count; i++)                              // to check for duplicate phone numbers
    {
        if (strcmp(contacts[i].phone, phone) == 0) 
        {
            printf("\n## Error! This phone number already exists.\n\n");
            return 0;
        }
    }

    return 1;
}

// Email validation function
int validateEmail(char email[], contact contacts[], int count)  
{
    const char *end = "@gmail.com";                // required ending for the email
    size_t emailLen = strlen(email);                   
    size_t endLen = strlen(end);

    if (emailLen <= endLen)                        // basic length check
    {
        printf("\n## Invalid! email too short.\n\n");
        return 0;
    }

    const char *ending = email + (emailLen - endLen);     // points to the end part of the email
    if (strcmp(ending, end) != 0) 
    {
        printf("\n## Invalid! email must end with @gmail.com\n\n");
        return 0;
    }

    for (size_t i = 0; i < emailLen - endLen; i++)          // check the local part of the email
    {
        char c = email[i];
        if (!(isalnum(c) || c == '_' || c == '.')) 
        {
            printf("\n## Invalid! character '%c'\n\n", c);
            return 0;
        }
    }

    for (int i = 0; i < count; i++)                      // check for duplicate emails
    {
        if (strcasecmp(contacts[i].email, email) == 0) 
        {
            printf("\n## Error! This email already exists.\n\n");
            return 0;
        }
    }
    return 1; 
}

