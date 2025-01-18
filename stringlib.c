#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "stringlib.h"


int disable(int isDisabled)
{
    return isDisabled;
}

int exitFromCurrAction(char *action)
{
    if(strcmp("b", action) == 0)
    {
        return 1;
    }
    return 0;
}

void printActionMenu()
{
    resetColor();
    printNewLine(1);
    printf("        : [1]Log out                         [2]View All My Students\n");
    printf("        : [3]Add Student To Class            [4]Remove Student To Class\n");
    printf("        : [5]View Grades Of Student By Id    [6]Give Grades\n"); 
    printf("        : [7]View My Grades                  [8]Exit\n");
    printf("Actions: ");
}

/**
 * @brief Sets the terminal text color.
 * 
 * @param colorCode The color code from the TextColor enumeration.
 */
void setColor(TextColor colorCode) {
    printf("\033[1;%dm", colorCode); // Set the desired text color
}

/**
 * @brief Resets the terminal text color to the default.
 */
void resetColor() {
    printf("\033[0m"); // Reset to default
}

/**
 * @brief Prints a success message in green text.
 * 
 * @param message The success message to print.
 */
void printfSUCCESS(char *message) 
{
    printNewLine(1);
    setColor(GREEN_TEXT);
    printf("[%s]\n", message);
    resetColor();
    printNewLine(1);
}

/**
 * @brief Prints an error message in red text.
 * 
 * @param message The error message to print.
 */
void printfERROR(char *message) 
{
    printNewLine(1);
    setColor(RED_TEXT);
    printf("!!!%s!!!\n", message);
    resetColor();
    printNewLine(1);
}

/**
 * @brief Prints a warning message in yellow text.
 * 
 * @param message The warning message to print.
 */
void printfWARNNING(char *message) 
{
    printNewLine(1);
    setColor(YELLOW_TEXT);
    printf("!!%s!!\n", message);
    resetColor();
    printNewLine(1);
}

/**
 * @brief Sets the input prompt color to blue.
 */
void fgetsmINPUT() 
{
    setColor(BLUE_TEXT);
}

/**
 * @brief Prints a specified number of newline characters.
 * 
 * @param numOfNewLine The number of newlines to print.
 */
void printNewLine(int numOfNewLine) {
    for (int i = 0; i < numOfNewLine; i++) {
        printf("\n");
    }
}

/**
 * @brief Converts an array of strings into a single CSV-formatted string.
 *
 * This function concatenates elements from a 2D string array (`strArr`) into 
 * a single string (`strInCsvFormat`), using the specified delimiter. The 
 * function ensures no buffer overflow by checking the available size of 
 * `strInCsvFormat`.
 *
 * @param[in] strArr        A 2D array of strings to be concatenated.
 *                          Each row represents a string.
 * @param[in] delimiter     The delimiter used to separate strings in the output.
 *                          Can be a single character or multi-character string.
 * @param[out] strInCsvFormat
 *                          The resulting CSV-formatted string.
 *                          Must be pre-allocated with a size of `bufferSize`.
 * @param[in] bufferSize    The maximum size of the `strInCsvFormat` buffer.
 *
 * @note If the concatenated result exceeds `bufferSize`, the function stops 
 *       concatenation and returns an error message.
 *
 * @warning Ensure that the `strArr` contains valid strings and terminates 
 *          with an empty string (`""`) to avoid reading uninitialized memory.
 */
void strToCsvFormat(char strArr[MAX_FILE_LINE][STR_CVS_LEN_IN], char *delimiter, char *strInCsvFormat, int bufferSize) 
{
    // Initialize the output string
    strInCsvFormat[0] = '\0';

    // Iterate through the string array
    for (int i = 0; strcmp(strArr[i], "") != 0; i++) 
    {
        // Check if appending the next string and delimiter exceeds the buffer
        if (strlen(strInCsvFormat) + strlen(strArr[i]) + strlen(delimiter) >= bufferSize) 
        {
            printfERROR("Error: Buffer size exceeded while building CSV format.");
            return;
        }
        
        // Concatenate the current string
        strcat(strInCsvFormat, strArr[i]);
        
        // Add the delimiter if this is not the last element
        if (strcmp(strArr[i + 1], "") != 0) 
        {
            strcat(strInCsvFormat, delimiter);
        }
    }
}

/**
 * @brief Splits a string into tokens based on a given delimiter.
 *
 * This function splits the input string into substrings using the specified
 * delimiter and stores the resulting tokens in a 2D array. The original
 * input string remains unmodified.
 *
 * @param[in] input         The input string to be split. This string is
 *                          preserved during the operation.
 * @param[out] output       A 2D array to store the resulting tokens. Each token
 *                          is stored as a row in this array.
 *                          Ensure that `output` is pre-allocated with enough rows
 *                          and columns to accommodate the tokens.
 * @param[in] delimiter     The delimiter used to split the string. This can be
 *                          a single character or a string of characters.
 *
 * @return The number of tokens extracted from the input string.
 *
 * @note The function stops splitting if the number of tokens exceeds
 *       `STR_MID_LEN` or if the input string ends.
 *
 * @warning Ensure that the size of each row in the `output` array is at least
 *          `MAX_FILE_LINE` to avoid buffer overflows.
 * 
 * @example
 * Example usage:
 * @code
 *     char input[] = "John,Doe,2001,12A";
 *     char output[10][50];
 *     char delimiter[] = ",";
 *     int tokenCount = strSplit(input, output, delimiter);
 *     for (int i = 0; i < tokenCount; i++) {
 *         printf("Token %d: %s\n", i + 1, output[i]);
 *     }
 * @endcode
 */
int strSplit(char *input, char output[MAX_FILE_LINE][STR_CVS_LEN_IN], char *delimiter) 
{
    int i = 0;
    char tempInput[strlen(input) + 1];
    strcpy(tempInput, input); // Preserve original input
    
    char *str = strtok(tempInput, delimiter);
    while (str != NULL && i < STR_CVS_LEN_IN) 
    {
        strncpy(output[i], str, MAX_FILE_LINE - 1); // Prevent overflow
        output[i][MAX_FILE_LINE - 1] = '\0';       // Ensure null-termination
        str = strtok(NULL, delimiter);
        i++;
    }
    return i; // Return the number of tokens
}


/**
 * @brief Trims leading and trailing whitespace (spaces, tabs) from a string.
 *
 * This function modifies the input string by removing any leading and trailing
 * spaces and tabs. It also ensures that the string is properly null-terminated.
 *
 * @param in Pointer to the string to be trimmed.
 */
void strtrim(char *in) 
{
    if (in == NULL) {
        return;
    }

    char *start = in;
    char *end;

    // Remove leading whitespace
    while (*start && isspace(( char)*start)) 
    {
        start++;
    }

    // Move the trimmed string to the beginning
    if (start != in) {
        memmove(in, start, strlen(start) + 1);
    }

    // Remove trailing whitespace
    end = in + strlen(in) - 1;
    while (end >= in && isspace((unsigned char)*end)) {
        *end = '\0';
        end--;
    }
}


/**
 * @brief Reads a line of input from a file, trims leading and trailing whitespace, 
 *        and handles errors gracefully.
 *
 * This function reads a line of text from the specified file stream into the provided
 * buffer, trims any leading and trailing whitespace, and ensures the buffer contains
 * a valid empty string if the read operation fails. 
 *
 * @param[in, out] in   Pointer to a character array where the input line will be stored.
 *                      Must be large enough to hold at least `size` characters, including
 *                      the null terminator.
 * @param[in]      size The maximum number of characters to read, including the null terminator.
 * @param[in]      file The file stream to read from.
 *
 * @return A pointer to the input buffer `in` if successful, or `NULL` if an error occurs 
 *         or the end of the file is reached.
 *
 * @note This function uses `fgets` internally. The behavior is undefined if `in` is not
 *       properly allocated. The function assumes the presence of a helper function 
 *       `strtrim` to trim whitespace.
 *
 * @warning If `strtrim` is not defined, the program may fail to compile.
 */
char* fgetsm(char *in, int size, FILE *file)  
{
    fgetsmINPUT();
    // if(disable) printf(">> ");

    // Read a line of input from the file
    if (fgets(in, size, file) == NULL) 
    {
        in[0] = '\0'; // Ensure the string is empty if reading fails
        return in;
    }

    // Trim leading and trailing whitespace
    strtrim(in);
    resetColor();
    return in;
}

/**
 * @brief Initializes a Student structure with default values.
 *
 * This function sets all fields of the provided Student structure to default
 * values. Strings are set to "NULL", numeric values are set to 0, and grades
 * are initialized to 0.0. This ensures a clean state for the structure before
 * it is used.
 *
 * @param student Pointer to the Student structure to initialize.
 *                The pointer must not be NULL.
 */
void initStudent(Student *student)
{
    // Initialize id
    student->id = 0;

    // Initialize first name
    strncpy(student->fname, "NULL", STRUCT_MAX_CHAR - 1);
    student->fname[STRUCT_MAX_CHAR - 1] = '\0'; // Ensure null-termination

    // Initialize last name
    strncpy(student->lname, "NULL", STRUCT_MAX_CHAR - 1);
    student->lname[STRUCT_MAX_CHAR - 1] = '\0'; // Ensure null-termination

    // Initialize date of birth
    student->dateOfBirth.DD = 0;
    student->dateOfBirth.MM = 0;
    student->dateOfBirth.YYYY = 0;

    // Initialize username
    strncpy(student->userName, "NULL", STRUCT_MAX_CHAR - 1);
    student->userName[STRUCT_MAX_CHAR - 1] = '\0'; // Ensure null-termination

    // Initialize password
    strncpy(student->password, "NULL", STRUCT_MAX_CHAR - 1);
    student->password[STRUCT_MAX_CHAR - 1] = '\0'; // Ensure null-termination

    // Initialize section
    strncpy(student->section, "NULL", STRUCT_MAX_CHAR - 1);
    student->section[STRUCT_MAX_CHAR - 1] = '\0'; // Ensure null-termination

    // Initialize grades
    student->grades.MATH = 0.0;
    student->grades.SCI = 0.0;
    student->grades.ENG = 0.0;
    student->grades.FIL = 0.0;
    student->grades.HIS = 0.0;
    student->grades.PE = 0.0;
    student->grades.AVE = 0.0;
}


/**
 * @brief Initializes a StudentList structure with default values. 
 *
 * This function sets all elements in the studentId array of the StudentList
 * structure to 0, indicating uninitialized student IDs.
 *
 * @param studentList Pointer to the StudentList structure to initialize.
 *                    Must not be NULL.
 */
void initStudentList(StudentList *studentList) 
{
    for (int i = 0; i < MAX_STUDENT_COUNT; i++) {
        studentList->studentId[i] = 0; // Default value for uninitialized IDs
    }
}

/**
 * @brief Initializes a Teacher structure with default values.
 *
 * This function initializes all fields of the Teacher structure to their
 * default values. Strings are set to "NULL", numeric values are set to 0,
 * and the associated StudentList is initialized using initStudentList.
 *
 * @param teacher Pointer to the Teacher structure to initialize.
 *                Must not be NULL.
 */
void initTeacher(Teacher *teacher)
{
    // Initialize id 
    teacher->id = 0;

    // Initialize first name
    strncpy(teacher->fname, "NULL", STRUCT_MAX_CHAR - 1);
    teacher->fname[STRUCT_MAX_CHAR - 1] = '\0'; // Ensure null-termination

    // Initialize last name
    strncpy(teacher->lname, "NULL", STRUCT_MAX_CHAR - 1);
    teacher->lname[STRUCT_MAX_CHAR - 1] = '\0'; // Ensure null-termination

    // Initialize date of birth
    teacher->dateOfBirth.DD = 0;
    teacher->dateOfBirth.MM = 0;
    teacher->dateOfBirth.YYYY = 0;

    // Initialize username
    strncpy(teacher->userName, "NULL", STRUCT_MAX_CHAR - 1);
    teacher->userName[STRUCT_MAX_CHAR - 1] = '\0'; // Ensure null-termination

    // Initialize password
    strncpy(teacher->password, "NULL", STRUCT_MAX_CHAR - 1);
    teacher->password[STRUCT_MAX_CHAR - 1] = '\0'; // Ensure null-termination

    // Initialize section
    strncpy(teacher->section, "NULL", STRUCT_MAX_CHAR - 1);
    teacher->section[STRUCT_MAX_CHAR - 1] = '\0'; // Ensure null-termination

    // Initialize StudentList
    initStudentList(&teacher->studentsList);
}

/**
 * @brief Converts the information of a Student to CSV format.
 *
 * This function takes a pointer to a `Student` structure and converts its members
 * (id, first name, last name, date of birth, username, section, grades) into a CSV format string.
 * The result is stored in the provided `studentInCsv` array.
 *
 * @param student Pointer to the `Student` structure containing the student data.
 * @param studentInCsv Output array where the CSV string will be stored. It is assumed to be large enough.
 *                     The length is defined by `STR_CVS_LEN_OUT`.
 * 
 * @note The CSV output format is:
 *       - `id, first_name, last_name, date_of_birth, username, section, grades`
 *       - Grades are represented as a comma-separated list: `MATH,SCI,ENG,FIL,HIS,PE,AVE`
 */
void studentToCsv(Student *student, char studentInCsv[STR_CVS_LEN_OUT])
{
    char strArr[MAX_FILE_LINE][STR_CVS_LEN_IN];
    char *delim = ",";

    // Convert id to string
    snprintf(strArr[0], sizeof(strArr[0]), "%d", student->id);
    strArr[0][STR_CVS_LEN_IN - 1] = '\0'; // Ensure null-termination

    // first name
    strncpy(strArr[1], student->fname, STR_CVS_LEN_IN - 1);
    strArr[1][STR_CVS_LEN_IN - 1] = '\0'; // Ensure null-termination

    // last name
    strncpy(strArr[2], student->lname, STR_CVS_LEN_IN - 1);
    strArr[2][STR_CVS_LEN_IN - 1] = '\0'; // Ensure null-termination

    // Convert date of birth to string
    snprintf(strArr[3], sizeof(strArr[3]), "%d/%d/%d", student->dateOfBirth.MM, student->dateOfBirth.DD, student->dateOfBirth.YYYY);
    strArr[3][STR_CVS_LEN_IN - 1] = '\0'; // Ensure null-termination

    // username
    strncpy(strArr[4], student->userName, STR_CVS_LEN_IN - 1);
    strArr[4][STR_CVS_LEN_IN - 1] = '\0'; // Ensure null-termination

    // section
    strncpy(strArr[5], student->section, STR_CVS_LEN_IN - 1);
    strArr[5][STR_CVS_LEN_IN - 1] = '\0'; // Ensure null-termination

    // grades
    snprintf(strArr[6], sizeof(strArr[6]), "%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f", 
        student->grades.MATH, student->grades.SCI, student->grades.ENG,
        student->grades.FIL, student->grades.HIS, student->grades.PE,
        student->grades.AVE
    );
    strArr[6][STR_CVS_LEN_IN - 1] = '\0'; // Ensure null-termination

    strncpy(strArr[7], "\0", STR_CVS_LEN_IN - 1);
    strArr[7][STR_CVS_LEN_IN - 1] = '\0'; // Ensure null-termination

    strToCsvFormat(strArr, delim, studentInCsv, STR_CVS_LEN_OUT);
}


/**
 * @brief Converts the information of a Teacher to CSV format.
 *
 * This function takes a pointer to a `Teacher` structure and converts its members
 * (id, first name, last name, date of birth, username, section, student list) into a CSV format string.
 * The result is stored in the provided `teacherInCsv` array.
 *
 * @param teacher Pointer to the `Teacher` structure containing the teacher data.
 * @param teacherInCsv Output array where the CSV string will be stored. It is assumed to be large enough.
 *                     The length is defined by `STR_CVS_LEN_OUT`.
 * 
 * @note The CSV output format is:
 *       - `id, first_name, last_name, date_of_birth, username, section, student_ids`
 *       - Student IDs are represented as a comma-separated list.
 */
void teacherToCsv(Teacher *teacher, char teacherInCsv[STR_CVS_LEN_OUT])
{
    char strArr[MAX_FILE_LINE][STR_CVS_LEN_IN];
    char *delim = ",";
    int index = 0;

    // Convert id to string
    snprintf(strArr[0], sizeof(strArr[0]), "%d", teacher->id);
    strArr[0][STR_CVS_LEN_IN - 1] = '\0'; // Ensure null-termination

    // first name
    strncpy(strArr[1], teacher->fname, STR_CVS_LEN_IN - 1);
    strArr[1][STR_CVS_LEN_IN - 1] = '\0'; // Ensure null-termination

    // last name
    strncpy(strArr[2], teacher->lname, STR_CVS_LEN_IN - 1);
    strArr[2][STR_CVS_LEN_IN - 1] = '\0'; // Ensure null-termination

    // Convert date of birth to string
    snprintf(strArr[3], sizeof(strArr[3]), "%d/%d/%d", teacher->dateOfBirth.MM, teacher->dateOfBirth.DD, teacher->dateOfBirth.YYYY);
    strArr[3][STR_CVS_LEN_IN - 1] = '\0'; // Ensure null-termination

    // username
    strncpy(strArr[4], teacher->userName, STR_CVS_LEN_IN - 1);
    strArr[4][STR_CVS_LEN_IN - 1] = '\0'; // Ensure null-termination

    // section
    strncpy(strArr[5], teacher->section, STR_CVS_LEN_IN - 1);
    strArr[5][STR_CVS_LEN_IN - 1] = '\0'; // Ensure null-termination

    // student list
    for (int i = 6; i <= 16; i++)
    {
        snprintf(strArr[i], sizeof(strArr[i]), "%d", teacher->studentsList.studentId[index]);
        strArr[i][STR_CVS_LEN_IN - 1] = '\0'; // Ensure null-termination
        if(i == 16)
        {
           strncpy(strArr[i], "\0", STR_CVS_LEN_IN - 1);
           strArr[i][STR_CVS_LEN_IN - 1] = '\0'; // Ensure null-termination
        }
        index++;
    }

    strToCsvFormat(strArr, delim, teacherInCsv, STR_CVS_LEN_OUT);
}


/**
 * @brief Converts a CSV-formatted string to a Student structure.
 * 
 * This function parses a string in CSV format and populates the fields of a Student structure.
 * The expected format of the CSV string is:
 * id,first_name,last_name,MM,DD,YYYY,username,section,MATH,SCI,ENG,FIL,HIS,PE,AVE
 * where MM/DD/YYYY represents the date of birth, and the remaining fields are grades.
 * 
 * @param studentInCsv Pointer to the string containing student information in CSV format.
 * @param student Pointer to the Student structure to populate.
 * @return int Returns the number of substrings parsed if successful; otherwise, returns 0.
 */
int csvToStudent(char *studentInCsv, Student *student)
{
    char studentSubStr[256][64];
    char *delim = ",/";
    int subStrCount = 0;

    if(student == NULL || strcmp("", studentInCsv) == 0)
    {
        printfERROR("Student in csv format is empty or student didn't initialized.");
        return 0;
    }

    subStrCount = strSplit(studentInCsv, studentSubStr, delim);

    if(subStrCount != 15) 
    {
        printfERROR("Bad formatting of csv.");
        return 0;
    }

    sscanf(studentSubStr[0], "%d", &student->id); // str to int
    strcpy(student->fname, studentSubStr[1]); // first name
    strcpy(student->lname, studentSubStr[2]); // lastname name
    sscanf(studentSubStr[3], "%d", &student->dateOfBirth.MM); // date
    sscanf(studentSubStr[4], "%d", &student->dateOfBirth.DD); // of
    sscanf(studentSubStr[5], "%d", &student->dateOfBirth.YYYY); // birth
    strcpy(student->userName, studentSubStr[6]); // first name
    strcpy(student->section, studentSubStr[7]); // first name 
    sscanf(studentSubStr[8], "%f", &student->grades.MATH); // str to float grades
    sscanf(studentSubStr[9], "%f", &student->grades.SCI); // str to float grades
    sscanf(studentSubStr[10], "%f", &student->grades.ENG); // str to float grades
    sscanf(studentSubStr[11], "%f", &student->grades.FIL); // str to float grades
    sscanf(studentSubStr[12], "%f", &student->grades.HIS); // str to float grades
    sscanf(studentSubStr[13], "%f", &student->grades.PE); // str to float grades
    sscanf(studentSubStr[14], "%f", &student->grades.AVE); // str to float grades

    return subStrCount;
}

/**
 * @brief Converts a CSV-formatted string to a Teacher structure.
 * 
 * This function parses a string in CSV format and populates the fields of a Teacher structure.
 * The expected format of the CSV string is:
 * id,first_name,last_name,MM,DD,YYYY,username,section,studentId[0],studentId[1],...,studentId[9]
 * where MM/DD/YYYY represents the date of birth, and studentId fields contain IDs of students assigned to the teacher.
 * 
 * @param studentInCsv Pointer to the string containing teacher information in CSV format.
 * @param teacher Pointer to the Teacher structure to populate.
 * @return int Returns the number of substrings parsed if successful; otherwise, returns 0.
 */
int csvToTeacher(char *studentInCsv, Teacher *teacher)
{
    char studentSubStr[256][64];
    char *delim = ",/";
    int subStrCount = 0;

    if(teacher == NULL || strcmp("", studentInCsv) == 0)
    {
        printfERROR("Student in csv format is empty or student didn't initialized.");
        return 0;
    }

    subStrCount = strSplit(studentInCsv, studentSubStr, delim);
    
    if(subStrCount != 18) 
    {
        printfERROR("Bad formatting of csv");
        return 0;
    }

    sscanf(studentSubStr[0], "%d", &teacher->id); // str to int
    strcpy(teacher->fname, studentSubStr[1]); // first name
    strcpy(teacher->lname, studentSubStr[2]); // lastname name
    sscanf(studentSubStr[3], "%d", &teacher->dateOfBirth.MM); // date
    sscanf(studentSubStr[4], "%d", &teacher->dateOfBirth.DD); // of
    sscanf(studentSubStr[5], "%d", &teacher->dateOfBirth.YYYY); // birth
    strcpy(teacher->userName, studentSubStr[6]); // first name
    strcpy(teacher->section, studentSubStr[7]); // first name 
    sscanf(studentSubStr[8], "%d", &teacher->studentsList.studentId[0]); // str id to int id
    sscanf(studentSubStr[9], "%d", &teacher->studentsList.studentId[1]); // str id to int id
    sscanf(studentSubStr[10], "%d", &teacher->studentsList.studentId[2]); // str id to int id
    sscanf(studentSubStr[11], "%d", &teacher->studentsList.studentId[3]); // str id to int id
    sscanf(studentSubStr[12], "%d", &teacher->studentsList.studentId[4]); // str id to int id
    sscanf(studentSubStr[13], "%d", &teacher->studentsList.studentId[5]); // str id to int id
    sscanf(studentSubStr[14], "%d", &teacher->studentsList.studentId[6]); // str id to int id
    sscanf(studentSubStr[15], "%d", &teacher->studentsList.studentId[7]); // str id to int id
    sscanf(studentSubStr[16], "%d", &teacher->studentsList.studentId[8]); // str id to int id
    sscanf(studentSubStr[17], "%d", &teacher->studentsList.studentId[9]); // str id to int id

    return subStrCount;
}

/**
 * @brief Prints a formatted table displaying student information and grades.
 *
 * This function takes an array of `Student` structures and the number of students,
 * and prints a formatted table including their ID, full name, and grades for various subjects.
 *
 * @param student Pointer to an array of `Student` structures containing student data.
 * @param size The number of students in the array.
 *
 * The table includes the following columns:
 * - ID: Unique identifier for the student.
 * - Name: Full name (first name and last name combined).
 * - MATH: Grade for the Math subject.
 * - SCI: Grade for the Science subject.
 * - ENG: Grade for the English subject.
 * - FIL: Grade for the Filipino subject.
 * - HIS: Grade for the History subject.
 * - PE: Grade for the Physical Education subject.
 * - AVE: Average grade across all subjects.
 *
 * The table is displayed with proper alignment and spacing for readability. 
 */
void printStudent(Student *student, int size)
{
    int nameColLen = 30;
    int gradesColen = 10;
    char remarks[5];
    char fullname[STR_CVS_LEN_OUT];
    float gradeHolder;
    char lineSeparator[] = "+----------+------------------------------+----------+----------+----------+----------+----------+----------+----------+----------+";
    printf("%s\n",lineSeparator);
    printf("|  id      |  name                        |  MATH    |  SCI     |  ENG     |  FIL     |  HIS     |  PE      |  AVE     |  REMARKS |\n");
    printf("%s\n",lineSeparator);

    for (int i = 0; i < size; i++)
    {
        // id
        printf("|  %d  ", student[i].id);

        // name
        strcpy(fullname, student[i].fname);
        strcat(fullname, " ");
        strcat(fullname, student[i].lname);
        printf("|  %s",fullname);
        for (int i = 0; i < nameColLen - (strlen(fullname) + 2); i++)
        {
            printf(" ");
        }

        // math
        gradeHolder = student[i].grades.MATH;
        printf("|");
        gradeHolder < 10 ? printf("    ") : gradeHolder == 100 ? printf("  ") : printf("   ");
        printf("%.2f  ", gradeHolder);

        // sci
        gradeHolder = student[i].grades.SCI;
        printf("|");
        gradeHolder < 10 ? printf("    ") : gradeHolder == 100 ? printf("  ") : printf("   ");
        printf("%.2f  ", gradeHolder);

        // eng 
        gradeHolder = student[i].grades.ENG;
        printf("|");
        gradeHolder < 10 ? printf("    ") : gradeHolder == 100 ? printf("  ") : printf("   ");
        printf("%.2f  ", gradeHolder);
        
        // fil 
        gradeHolder = student[i].grades.FIL;
        printf("|");
        gradeHolder < 10 ? printf("    ") : gradeHolder == 100 ? printf("  ") : printf("   ");
        printf("%.2f  ", gradeHolder);
        
        // his 
        gradeHolder = student[i].grades.HIS;
        printf("|");
        gradeHolder < 10 ? printf("    ") : gradeHolder == 100 ? printf("  ") : printf("   ");
        printf("%.2f  ", gradeHolder);
        
        // pe 
        gradeHolder = student[i].grades.PE;
        printf("|");
        gradeHolder < 10 ? printf("    ") : gradeHolder == 100 ? printf("  ") : printf("   ");
        printf("%.2f  ", gradeHolder);
        
        // ave 
        gradeHolder = student[i].grades.AVE;
        printf("|");
        gradeHolder < 10 ? printf("    ") : gradeHolder == 100 ? printf("  ") : printf("   ");
        printf("%.2f  ", gradeHolder);

        // remarks
        printf("|");
        gradeRemarks(student, remarks);
        printf("  %s     ", remarks);

        printf("|\n");
    }
    printf("%s\n",lineSeparator);
    
}

/**
 * @brief Determines the grade remarks for a student based on their average grade.
 * 
 * This function calculates grade remarks based on the average grade (`AVE`) of a student.
 * Special remarks such as "INC" (Incomplete) or "NF" (Not Found) are assigned when specific 
 * conditions are met. Otherwise, letter grade remarks are assigned based on the rounded
 * average.
 * 
 * @param student A pointer to the Student structure containing grade details.
 * @param remarks A character array to store the remarks (e.g., "A", "B+", "INC").
 * 
 * @note If any of the individual subject grades (MATH, SCI, ENG, FIL, HIS, PE) is 0.0, 
 *       the remark will be "INC". If the average grade (`AVE`) is 0.0, the remark will be "NF".
 */
void gradeRemarks(Student *student, char *remarks)
{
    // Calculate the average grade and round it to the nearest integer
    float ave = student->grades.AVE;
    int grades = (int) round(ave);

    // Check if any subject grade is 0.0; if so, mark as "Incomplete"
    if (student->grades.MATH == 0.0 ||
        student->grades.SCI == 0.0 ||
        student->grades.ENG == 0.0 ||
        student->grades.FIL == 0.0 ||
        student->grades.HIS == 0.0 ||
        student->grades.PE == 0.0)
    {
        strcpy(remarks, "INC"); // Incomplete
        return;
    }

    // If the average grade is 0.0, mark as "Not Failed"
    if (ave == 0.0)
    {
        strcpy(remarks, "NF "); // Not Failed
        return;
    }

    // Assign grade remarks based on the rounded average
    switch (grades)
    {
        case 97 ... 100:
            strcpy(remarks, "A  "); // Excellent
            break;
        case 94 ... 96:
            strcpy(remarks, "A- "); // Very Good
            break;
        case 91 ... 93:
            strcpy(remarks, "B+ "); // Good
            break;
        case 88 ... 90:
            strcpy(remarks, "B  "); // Above Average
            break;
        case 85 ... 87:
            strcpy(remarks, "B- "); // Average
            break;
        case 80 ... 84:
            strcpy(remarks, "C+ "); // Satisfactory
            break;
        case 75 ... 79:
            strcpy(remarks, "C  "); // Passing
            break;
        case 0 ... 74:
            strcpy(remarks, "F  "); // Failing
            break;
        default:
            break; // No action for unexpected values
    }
}
