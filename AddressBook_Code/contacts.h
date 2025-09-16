#ifndef CONTACTS_H
#define CONTACTS_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_CONTACTS 100

typedef struct                      // structure design
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
void saveContacts(contact contacts[], int count);
void loadContacts(contact contacts[], int *count);

#endif 