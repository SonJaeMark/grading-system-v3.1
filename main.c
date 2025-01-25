#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "stringlib.h"
#include "userfilelib.h"
#include "userlib.h"
#include "studentlib.h"
#include "teacherlib.h"


// disable all fgetsm in userfilelib 


int rememberMe(User *user)
{
    char strBuff[STR_CVS_LEN_OUT];
    int isTeacher = 0;
    int returnFlag = 0;

    if(user->teacher->id)
    {
        isTeacher = 1;
    }
    else if(user->student->id)
    {
        isTeacher = 0;
    }

    FILE *fptr = fopen(LOG_FILE, "w");
    while (1)
    {
        printf("Remember me? [y]Yes || [n]No: ");
        fgetsm(strBuff, sizeof(strBuff), stdin);

        if(isTeacher && strcmp("y", strBuff) == 0)
        {
            fprintf(fptr, "%d,%d", isTeacher, user->teacher->id);
            returnFlag = 1;
            break;
        }
        else if(!isTeacher && strcmp("y", strBuff) == 0)
        {
            fprintf(fptr, "%d,%d", isTeacher, user->student->id);
            returnFlag = 1;
            break;
        }
        else if(strcmp("n", strBuff) == 0)
        {
            returnFlag = 1;
            break;
        }
        else if (strcmp("b", strBuff) == 0)
        {
            returnFlag = 0;
            break;
        }
        else
        {
            printfWARNNING("[n] for NO, [y] for YES and [b] for back");
        }
        
    }
    
    fclose(fptr);
    return returnFlag;
}

int getLoggedUser(User *user)
{
    FILE *fptr = fopen(LOG_FILE, "r");
    char strBuff[STR_CVS_LEN_OUT];
    char strBuffOut[MAX_FILE_LINE][STR_CVS_LEN_IN];
    char *delim = ",";
    int id = 0;
    int isTeacher = -1;
    int returnFlag = 0;
    char fname[STR_CVS_LEN_IN];
    char lname[STR_CVS_LEN_IN];

    if(user->student->id != 0 || user->teacher->id != 0)
    {
        return 1;
    }
    if(fptr == NULL)
    {
        printfWARNNING("NO user yet");
        return 0;
    }
    else if (fptr)
    {
        fgetsm(strBuff, sizeof(strBuff), fptr);
    }

    strSplit(strBuff, strBuffOut, delim);

    sscanf(strBuffOut[0], "%d", &isTeacher);
    sscanf(strBuffOut[1], "%d", &id);

    suppressErrMes(0);

    if(isTeacher  == 1 && getTeacherById(id, user->teacher))
    {
        strcpy(fname, user->teacher->fname);
        strcpy(lname, user->teacher->lname);
        returnFlag = 1;
    }
    else if (isTeacher == 0 && getStudentById(id, user->student))
    {   
        strcpy(fname, user->student->fname);
        strcpy(lname, user->student->lname);
        returnFlag = 1;
    }
    
    snprintf(strBuff, sizeof(strBuff) - 1, "Welcome %s %s!", fname, lname);
    if(returnFlag) printfSUCCESS(strBuff);
    return returnFlag;
}


void readBanner()
{
    FILE *fptr;
    char strBuff[STR_CVS_LEN_OUT];

    fptr = fopen("banner.txt", "r");

    if(fptr == NULL)
    {
        return;
    }
    setColor(GREEN_TEXT);

    do
    {
        fgets(strBuff, sizeof(strBuff) -1, fptr);
        strBuff[strcspn(strBuff,"\n")] = '\0';
        printf("%s\n", strBuff);

    } while (!feof(fptr));
    printNewLine(2);
    fclose(fptr);

}

int main()
{
    User user;
    Teacher teachers[10];
    Student students[10];

    user.teacher = teachers;
    user.student = students;

    initStudent(user.student);
    initTeacher(user.teacher);
    
    char strBuffer[STR_CVS_LEN_IN];
    int action = 0;

    

    readBanner();
    resetColor();

    while (1)
    {
        while(!getLoggedUser(&user) && !user.student->id && !user.teacher->id)
        {
            printNewLine(1);
            
            resetColor();

            printf("[l]Login || [r]Register: ");
            fgetsm(strBuffer, sizeof(strBuffer), stdin);

            printNewLine(1);
            if(strcmp("l", strBuffer) == 0 && loginUser(&user))
            {
                break;   
            }
            else if (strcmp("r", strBuffer) == 0 && registerUser(&user))
            {
                break;   
            }
            else if (strcmp("e", strBuffer) == 0)
            {
                return 0;
            }
            
        }
        
        if (user.student->id || user.teacher->id)
        {
            if(!user.teacher) initStudent(user.student);
            printActionMenu();
            fgetsm(strBuffer, STR_CVS_LEN_IN, stdin);
            sscanf(strBuffer, "%d", &action);
            

            printNewLine(2);
            switch (action)
            {
                case 1:
                    printNewLine(1);
                    logoutUser(&user);

                    break;
                case 2:
                    printNewLine(1);
                    viewAllMyStudents(&user);
                    break;
                case 3:
                    printNewLine(1);
                    addStudentToClass(&user);
                    break;
                case 4:
                    printNewLine(1);
                    removeStudentToClass(&user);
                    break;
                case 5:
                    printNewLine(1);
                    viewGradesOfStudentById(&user);
                    break;
                case 6:
                    printNewLine(1);
                    giveGrades(&user);
                    break;
                case 7:
                    printNewLine(1);
                    viewMyGrades(&user);
                    break;
                case 8:
                    if(rememberMe(&user)) return 0;
                default:
                    printf("\n\n");
                    printf("input 1-7\n");
                break;
            }
        }
    }
    return 0;
}