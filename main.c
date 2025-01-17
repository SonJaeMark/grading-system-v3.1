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
        while(!user.student->id && !user.teacher->id)
        {
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
                    return 0;
                default:
                    printf("\n\n");
                    printf("input 1-7\n");
                break;
            }
        }
    }
    return 0;
}