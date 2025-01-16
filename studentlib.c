#include <stdlib.h>
#include <stdio.h>

#include "stringlib.h"
#include "userfilelib.h"
#include "userlib.h"


/**
 * @brief Displays the grades of the currently logged-in student.
 *
 * This function checks if the user is logged in as a student. If so, it prints the student's section, 
 * name, and grades. If the user is not logged in as a student, it displays a warning message and denies access.
 *
 * @param user A pointer to the User object containing the student's information.
 * @return int Returns 1 if the grades are successfully displayed, 0 if the user is not allowed to access this feature.
 */
int viewMyGrades(User *user)
{
    setColor(GREEN_TEXT);
    // Check if the user is logged in as a student
    if (user->student->id == 0)
    {
        printfWARNNING("You are not allowed to access this!"); // Display warning
        return 0; // Deny access
    }

    // Display the student's section
    printf("Section: %s\n", user->student->section);

    // Display the student's name and grades
    printf("%s %s grades:\n", user->student->fname, user->student->lname);
    printStudent(user->student, 1); // Print the student's grades 

    resetColor();

    return 1; // Successfully displayed grades
}