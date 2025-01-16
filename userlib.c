#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "userfilelib.h"
#include "userlib.h"
#include "stringlib.h"
#include "validationlib.h"

/**
 * @brief Registers a new user (Teacher or Student).
 *
 * Prompts the user to input personal details such as name, username, section, date of birth, and password.
 * Saves the user information to the appropriate data store based on their role.
 *
 * @param user A pointer to the User object to store the registration details.
 * @return int Returns 1 for successful registration, 0 otherwise.
 */
int registerUser(User *user)
{
    char strBuffer[STR_CVS_LEN_IN];
    char passwordHolder[STR_CVS_LEN_IN];
    char userToCsv[STR_CVS_LEN_OUT];
    int isTeacher = -1;
    int MM;
    int DD;
    int YYYY;
    int id = 0;

    resetColor();
    printf("Registration:\n");
    
    while (1)
    {
        
        printf("Register as [t]Teacher || [s]Student: ");
        fgetsm(strBuffer, sizeof(strBuffer), stdin);
        if (strcmp(strBuffer, "t") == 0)
        {
            printfSUCCESS("Registering as Teacher...");
            initTeacher(user->teacher);
            initStudent(user->student);
            isTeacher = 1;
            break;
        }
        else if (strcmp(strBuffer, "s") == 0)
        {
            printfSUCCESS("Registering as Student...");
            initStudent(user->student);
            initTeacher(user->teacher);
            isTeacher = 0;
            break;
        }
        else
        {
            printfWARNNING("Please input correct response... ");
        }       
    }
    strcpy(strBuffer, "\0");

    printf("Please enter necessary details.\n");

    printf("Enter firstname: ");
    fgetsm(strBuffer, sizeof(strBuffer), stdin);
    isTeacher == 1 ? strcpy(user->teacher->fname, strBuffer) : strcpy(user->student->fname, strBuffer);
    strcpy(strBuffer, "\0");
    

    printf("Enter lastname: ");
    fgetsm(strBuffer, sizeof(strBuffer), stdin);
    isTeacher == 1 ? strcpy(user->teacher->lname, strBuffer) : strcpy(user->student->lname, strBuffer);
    strcpy(strBuffer, "\0");
    

    printf("Enter username: ");
    fgetsm(strBuffer, sizeof(strBuffer), stdin);
    isTeacher == 1 ? strcpy(user->teacher->userName, strBuffer) : strcpy(user->student->userName, strBuffer);
    strcpy(strBuffer, "\0");

    while (1)
    {
        if(!isTeacher) break;

        printf("Sections: A1, A2, A3, A4, A5, A6, A7, A8, A9, A10\n");
        printf("Enter section: ");
        fgetsm(strBuffer, sizeof(strBuffer), stdin);
        
        if(strcmp(strBuffer, "A1") == 0) break;
        if(strcmp(strBuffer, "A2") == 0) break;
        if(strcmp(strBuffer, "A3") == 0) break;
        if(strcmp(strBuffer, "A4") == 0) break;
        if(strcmp(strBuffer, "A5") == 0) break;
        if(strcmp(strBuffer, "A6") == 0) break;
        if(strcmp(strBuffer, "A7") == 0) break;
        if(strcmp(strBuffer, "A8") == 0) break;
        if(strcmp(strBuffer, "A9") == 0) break;
        if(strcmp(strBuffer, "A10") == 0) break;
        

    } 
    isTeacher == 1 ? strcpy(user->teacher->section, strBuffer) : strcpy(user->student->section, "A0");
    strcpy(strBuffer, "\0");

    while (1)
    {
        resetColor();
        printf("Enter date of birth 'MM DD YYYY' format: ");
        fgetsmINPUT();
        scanf("%d %d %d", &MM, &DD, &YYYY);
        resetColor();

        sscanf(strBuffer, "%d %d %d", &MM, &DD, &YYYY);
        if(dateOfBirthValidation(MM, DD, YYYY) == 1) break;
        
        printfWARNNING("Birthday format invalid");
    }


    while (1)
    {
        resetColor();
        printf("Enter password: ");
        fgetsm(strBuffer, sizeof(strBuffer), stdin);

        strcpy(passwordHolder, strBuffer);

        printf("Re-enter password: ");
        fgetsm(strBuffer, sizeof(strBuffer), stdin);

        if (strcmp(passwordHolder, strBuffer) == 0) break;        
        printfERROR("Password not match.");
    }
    
    while (1)
    {
        printf("Save info?\n");
        printf("[y]Yes || [n]No: ");
        fgetsm(strBuffer, sizeof(strBuffer), stdin);

        if(strcmp("y", strBuffer) == 0) break;
        else if(strcmp("y", strBuffer) == 0)
        {
            return 0;
        }

    }
    

    id = generateId();

    if (isTeacher)
    {
        user->teacher->id = id;
        user->teacher->dateOfBirth.MM = MM;
        user->teacher->dateOfBirth.DD = DD;
        user->teacher->dateOfBirth.YYYY = YYYY;
    }
    else
    {
        user->student->id = id;
        user->student->dateOfBirth.MM = MM;
        user->student->dateOfBirth.DD = DD;
        user->student->dateOfBirth.YYYY = YYYY;
    }
    getchar();
    
    if (isTeacher)
    {
        strcpy(user->teacher->password, strBuffer);
        teacherToCsv(user->teacher, userToCsv);
        saveTeacher(userToCsv);
        savePassword(user->teacher->id, user->teacher->password);
        
    }
    else
    {
        strcpy(user->student->password, strBuffer);
        studentToCsv(user->student, userToCsv);
        saveStudent(userToCsv);
        savePassword(user->student->id, user->student->password);
    }

    printfSUCCESS("Registration Complete!!!");
    snprintf(strBuffer, sizeof(strBuffer) -1, "Your ID is %d", id);
    printfSUCCESS(strBuffer);
}


/**
 * @brief Logs out the currently logged-in user.
 *
 * Asks for confirmation before logging the user out and reinitializes their data structures.
 *
 * @param user A pointer to the User object to clear the login details.
 * @return int Returns 1 if the user logs out successfully, 0 if they cancel the logout.
 */
int logoutUser(User *user)
{
    char strBuffer[STR_CVS_LEN_IN];
    while (1)
    {
        resetColor();
        printf("You sure you want to log out?\n");
        printf("[y]Yes || [n]No: ");
        fgetsm(strBuffer, sizeof(strBuffer), stdin);

        if(strcmp("n", strBuffer) == 0) break;
        else if(strcmp("y", strBuffer) == 0)
        {
            initTeacher(user->teacher);
            initStudent(user->student);
            break;
        }
        else printfWARNNING("Enter [y] for yes and [n] for no");
    }
    
}

/**
 * @brief Logs a user into the system.
 *
 * Prompts the user to select their role (Teacher or Student), input their ID and password, 
 * and validates the credentials before logging them in.
 *
 * @param user A pointer to the User object to store the login details.
 * @return int Returns 1 for successful login, 0 otherwise.
 */
int loginUser(User *user)
{
    char strBuffer[STR_CVS_LEN_IN];
    char passwordHolder[STR_CVS_LEN_IN];
    int id;
    int isTeacher = -1;
    char buffer[STR_CVS_LEN_OUT];

    resetColor();
    if(user->teacher->id != 0)
    {
        snprintf(buffer, sizeof(buffer) - 1, "Cannot log in, User %d-%s is currently logged in.\n", user->teacher->id, user->teacher->userName);
        printfWARNNING(buffer);
        return 0;
    }
    else if(user->student->id != 0)
    {
        snprintf(buffer, sizeof(buffer) - 1, "Cannot log in, User %d-%s is currently logged in.\n", user->student->id, user->student->userName);
        printfWARNNING(buffer);
        return 0;
    }
    
    
    while (1)
    {
        resetColor();
        printf("Enter ID: ");
        fgetsm(strBuffer, sizeof(strBuffer), stdin);

        /*
        *   implement login by username
        *
        */
        
        sscanf(strBuffer, "%d", &id);
        getPasswordById(id, passwordHolder);

        printf("Enter password: ");
        fgetsm(strBuffer, sizeof(strBuffer), stdin);

        sscanf(strBuffer, "%d", &id);
        getPasswordById(id, passwordHolder);

        if (strcmp(passwordHolder, strBuffer) == 0) break;        
        printfWARNNING("Incorrect password or id.");
    }


    suppressErrMes(1);

    if(getTeacherById(id, user->teacher))
    {
        initStudent(user->student);
        snprintf(buffer, sizeof(buffer) - 1, "Welcome %s %s!", user->teacher->fname, user->teacher->lname);
        printfSUCCESS(buffer);
    }
    else if (getStudentById(id, user->student))
    {
        initTeacher(user->teacher);
        snprintf(buffer, sizeof(buffer) - 1, "Welcome %s %s!", user->student->fname, user->student->lname);
        printfSUCCESS(buffer);
    }
    else
    {
        printfERROR("User data lost");
        printfERROR("Please contact admin");
    }
    
    
    return 1;
}