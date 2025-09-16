#ifndef VALIDATION_H
#define VALIDATION_H

#include "contacts.h"

//------------------->VALIDATION FUNCTION DECLARATIONS<---------------------------------
int validateName(char name[]);
int validatePhone(char phone[], contact contacts[], int count);
int validateEmail(char email[], contact contacts[], int count);

#endif 