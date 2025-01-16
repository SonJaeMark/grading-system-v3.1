#pragma once 

#include "userfilelib.h"
typedef struct User
{
    Student *student;
    Teacher *teacher;
} User;

int registerUser(User *user);
int loginUser(User *user);
int logoutUser(User *user);

