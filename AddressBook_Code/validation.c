#include "validation.h"

// Name validation function
int validateName(char name[]) 
{
    if (name[0] == ' ')
    {
        printf("\n\033[1;31m## Invalid! Name cannot start with a space.\033[0m\n");
        return 0;
    }
    if (strlen(name) == 0)                                         // to check if name is empty
    {
        printf("\n\033[1;31m## Invalid! Name cannot be empty.\033[0m\n");
        return 0;
    }
    for (int i = 0; name[i] != '\0'; i++)                          // to check if all characters are alphabets or space
    {
        if (!isalpha(name[i]) && name[i] != ' ') 
        {
            printf("\n\033[1;31m## Invalid! : Use alphabets and spaces only.\033[0m\n");
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
        printf("\n\033[1;31m## Invalid! The phone number Must be 10 digits.\033[0m\n");
        return 0;
    }

    for (int i = 0; phone[i] != '\0'; i++)                        // to check if all characters are digits
    {
        if (!isdigit(phone[i])) 
        {
            printf("\n\033[1;31m## Invalid! The phone number must contain only digits.\033[0m\n");
            return 0;
        }
    }

    for (int i = 0; i < count; i++)                               // to check for duplicate phone numbers
    {
        if (strcmp(contacts[i].phone, phone) == 0) 
        {
            printf("\n\033[1;31m## Error! This phone number already exists.\033[0m\n");
            return 0;
        }
    }

    return 1;
}

// Email validation function
int validateEmail(char email[], contact contacts[], int count)  
{
    const char *end = "@gmail.com";                               // required ending for the email
    size_t emailLen = strlen(email);                   
    size_t endLen = strlen(end);

    if (emailLen <= endLen)                                       // basic length check
    {
        printf("\n\033[1;31m## Invalid! email too short.\033[0m\n");
        return 0;
    }

    const char *ending = email + (emailLen - endLen);             // points to the end part of the email
    if (strcmp(ending, end) != 0) 
    {
        printf("\n\033[1;31m## Invalid! email must end with @gmail.com\033[0m\n");
        return 0;
    }

    for (size_t i = 0; i < emailLen - endLen; i++)                // check the local part of the email
    {
        char c = email[i];
        if (!(isalnum(c) || c == '_' || c == '.')) 
        {
            printf("\n\033[1;31m## Invalid! character '%c'\033[0m\n\n", c);
            return 0;
        }
    }

    for (int i = 0; i < count; i++)                              // check for duplicate emails
    {
        if (strcasecmp(contacts[i].email, email) == 0) 
        {
            printf("\n\033[1;31m## Error! This email already exists.\033[0m\n\n");
            return 0;
        }
    }
    return 1; 
}

