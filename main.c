#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "stringlib.h"
#include "userfilelib.h"
#include "userlib.h"
#include "studentlib.h"
#include "teacherlib.h"


// disable all fgetsm in userfilelib 

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

int ask(char *q, char *ans1, char *ans0)
{
    char strBuffer[STR_CVS_LEN_IN];
    while (1)
    {
        printf("%s: ", q);
        fgetsm(strBuffer, STR_CVS_LEN_IN, stdin);

        if(strcmp(ans1, strBuffer) == 0)
        {
            return 1;
        }
        else if (strcmp(ans0, strBuffer) == 0)
        {
            return 0;
        }
        
    }
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
    char r[5] = "r";
    char l[5] = "l";
    int action = 0;

    readBanner();
    resetColor();

    while (1)
    {
        if(user.student->id == 0 && user.teacher->id == 0 && ask("[l]Login || [r]Register", l, r)) loginUser(&user);
        else if(user.student->id == 0 && user.teacher->id == 0) registerUser(&user);

        resetColor();
        printNewLine(1);
        printf("Actions: [1]Log out                         [2]View All My Students\n");
        printf("Actions: [3]Add Student To Class            [4]Remove Student To Class\n");
        printf("Actions: [5]View Grades Of Student By Id    [6]Give Grades\n"); 
        printf("Actions: [7]View My Grades                  [8]Exit\n");
        

        printf("Actions: ");
        fgetsm(strBuffer, STR_CVS_LEN_IN, stdin);
        sscanf(strBuffer, "%d", &action);

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
            return 0;
        default:
            printf("\n\n");
            printf("input 1-7\n");
            break;
        }
    }
    

    
    
    return 0;
}