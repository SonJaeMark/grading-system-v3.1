#pragma once

#include "userlib.h"

float getAve(Student student);
void removeDuplicate(int idArr[], int *size);
void getUnique(int base[], int baseSize, int compare[], int *compareSize);
void getMatch(int base[], int baseSize, int compare[], int *compareSize);

int viewAllMyStudents(User *user);
int addStudentToClass(User *user);
int removeStudentToClass(User *user);
void viewGradesOfStudentById(User *user);
void giveGrades(User *user);