#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "userfilelib.h"
#include "stringlib.h"

/**
 * @brief Suppresses or enables error messages based on the input parameter.
 *
 * This function is designed to determine whether error messages should be suppressed.
 * A non-zero value for the input parameter indicates suppression is enabled,
 * while a zero value indicates suppression is disabled.
 *
 * @param isSuppress An integer flag:
 *                   - Non-zero: Suppress error messages.
 *                   - Zero: Do not suppress error messages.
 * @return The value of the `isSuppress` parameter, indicating the suppression state.
 */
int suppressErrMes(int isSuppress)
{
    // Return the suppression state (non-zero means suppress, zero means do not suppress)
    return isSuppress;
}

/**
 * @brief Generates a unique ID by reading and updating a stored value.
 *
 * This function reads a stored ID value from a file, increments it, and writes the updated value back to the file.
 * If the file does not exist, it will create the file and initialize the ID to a default value (240000).
 *
 * @return int The generated unique ID.
 */
int generateId()
{
    FILE *fptr;
    int currIdVal;           /**< Current ID value read from the file */
    char buff[STR_CVS_LEN_IN];   /**< Buffer to store the read ID as a string */

    // Open the file for reading
    fptr = fopen(ID_VAL_FILE, "r");

    // If the file doesn't exist, create it and initialize the ID value
    if (fptr == NULL)
    {
        fptr = fopen(ID_VAL_FILE, "w");
        if (fptr == NULL) 
        {
            // If unable to create or open the file, print an error and return -1
            printfERROR("Error creating ID file.");
            return -1;
        }

        /**< Initial ID value if the file does not exist */
        fprintf(fptr, "%d", ID_INIT_VAL);  // Write the initial ID value to the file
        currIdVal = ID_INIT_VAL;            // Set the current ID value to the initial value
    }
    else
    {
        // If the file exists, read the current ID value and increment it
        fgets(buff, STR_CVS_LEN_IN, fptr);
        currIdVal = atoi(buff) + 1;  // Increment the read ID value

        // Reopen the file for writing and update the ID value
        fptr = fopen(ID_VAL_FILE, "w");
        if (fptr == NULL) 
        {
            // If unable to open the file for writing, print an error and return -1
            printfERROR("Error opening ID file for writing.");
            return -1;
        }

        fprintf(fptr, "%d", currIdVal);  // Write the updated ID value back to the file
    }

    fclose(fptr);  // Close the file

    return currIdVal;  // Return the generated ID value
}


/**
 * @brief Saves student information in CSV format to the student file.
 * 
 * This function saves the given student information string into a CSV file.
 * If the file does not exist, it creates a new file and writes a header line.
 * If the file exists, it appends the student information to the file.
 * 
 * @param studentInfoCsv Pointer to the string containing student information in CSV format.
 * @return int Returns 1 if the operation is successful, otherwise returns 0.
 */
int saveStudent(char *studentInfoCsv)
{
    FILE *fptr;

    // check if the studentInfoCsv is empty or NULL    
    if(studentInfoCsv == NULL || strcmp("", studentInfoCsv) == 0)
    {
        printfERROR("Student info is empty");
        return 0;
    }

    fptr = fopen(STUDENT_FILE, "r");

    // check file if NULL
    if(fptr == NULL)
    {
        fptr = fopen(STUDENT_FILE, "w");
        if (fptr == NULL)
        {
            printfERROR("Error opening student file for writing");
            return 0;
        }
        // add header if file not exist yet
        fprintf(fptr, "id,first_name,last_name,date_of_birth,username,section,grades(MATH,SCI,ENG,FIL,HISTORY,PE,AVE)\n");
    }
    else
    {
        fptr = fopen(STUDENT_FILE, "a");
        if (fptr == NULL)
        {
            printfERROR("Error opening student file for appending");
            return 0;
        }
    }

    // print the studentInfoCsv into file
    fprintf(fptr, "%s\n", studentInfoCsv); 
    fclose(fptr);

    return 1;
}

/**
 * @brief Saves teacher information in CSV format to the teacher file.
 * 
 * This function saves the given teacher information string into a CSV file.
 * If the file does not exist, it creates a new file and writes a header line.
 * If the file exists, it appends the teacher information to the file.
 * 
 * @param teacherInfoCsv Pointer to the string containing teacher information in CSV format.
 * @return int Returns 1 if the operation is successful, otherwise returns 0.
 */
int saveTeacher(char *teacherInfoCsv)
{
    FILE *fptr;

    // check if the teacherInfoCsv is empty or NULL
    if(strcmp("", teacherInfoCsv) == 0 || teacherInfoCsv == NULL)
    {
        printfERROR("Teacher info is empty");
        return 0;
    }

    fptr = fopen(TEACHER_FILE, "r");

    // check file if NULL
    if(fptr == NULL)
    {
        fptr = fopen(TEACHER_FILE, "w");
        if (fptr == NULL)
        {
            printfERROR("Error opening student file for writing");
            return 0;
        }
        // add header if file not exist yet
        fprintf(fptr, "id,first_name,last_name,date_of_birth,username,section,{student_list}");
        
    }
    else
    {
        fptr = fopen(TEACHER_FILE, "a");
        if (fptr == NULL)
        {
            printfERROR("Error opening student file for appending");
            return 0;
        }
    }

    // print the teacherInfoCsv into file
    fprintf(fptr, "%s\n", teacherInfoCsv); 
    fclose(fptr);
    return 1;
}


/**
 * @brief Retrieves a student's information from a file by their ID.
 *
 * This function searches for a student in the file specified by `STUDENT_FILE`
 * using the provided student ID. If a match is found, the student's information
 * is stored in the provided `Student` structure.
 *
 * @param id The ID of the student to search for. Must be greater than or equal to `ID_INIT_VAL`.
 * @param student Pointer to a `Student` structure where the retrieved student data will be stored.
 * 
 * @return int Returns 1 if the student is found and successfully retrieved, otherwise returns 0.
 * 
 * The function performs the following:
 * - Validates the provided ID and `Student` pointer.
 * - Opens the file `STUDENT_FILE` for reading.
 * - Iterates through the file line by line, parsing each line into a `Student` structure.
 * - Compares the parsed student's ID with the provided ID.
 * - If a match is found, the corresponding `Student` structure is populated and the search terminates.
 * 
 * @note
 * - The file is expected to have a CSV format with a header row.
 * - The `csvToStudent` function is used to parse each line into a `Student` structure.
 * - If the file cannot be opened or the student is not found, an appropriate error message is displayed.
 * 
 * Example:
 * ```c
 * Student student;
 * int result = getStudentById(1001, &student);
 * if (result) {
 *     printf("Student Name: %s %s\n", student.fname, student.lname);
 * } else {
 *     printf("Student not found.\n");
 * }
 * ```
 */
int getStudentById(int id, Student *student)
{
    FILE *fptr;
    Student studentBuffer;
    char studBuff[STR_CVS_LEN_OUT];
    char buffer[STR_CVS_LEN_IN];
    int isFound = 0;
    int numOfReadVal = 0;
    

    if(student == NULL || id < ID_INIT_VAL)
    {
        snprintf(buffer, sizeof(buffer) - 1, "ID %d is invalid or student didn't initialized", id);
        printfERROR(buffer);
        return 0;
    }

    fptr = fopen(STUDENT_FILE, "r");

    if(fptr == NULL)
    {
        printfERROR("File not found");
        return 0;
    }
    
    fgets(studBuff, STR_CVS_LEN_OUT - 1, fptr); // reads header
    while (fgets(studBuff, STR_CVS_LEN_OUT - 1, fptr) != NULL)
    {
        csvToStudent(studBuff, &studentBuffer);
        if(id == studentBuffer.id)
        {
            csvToStudent(studBuff, student);
            isFound = 1;
            break;
        }
    }

    if(!isFound  && !suppressErrMes)
    {
        snprintf(buffer, sizeof(buffer) - 1, "Student with ID %d not found", id);
        printfERROR(buffer);
    } 
    fclose(fptr);
    return isFound;
}


/**
 * @brief Retrieves a teacher's information from a file by their ID.
 *
 * This function searches for a teacher in the file specified by `TEACHER_FILE`
 * using the provided teacher ID. If a match is found, the teacher's information
 * is stored in the provided `Teacher` structure.
 *
 * @param id The ID of the teacher to search for. Must be greater than or equal to `ID_INIT_VAL`.
 * @param teacher Pointer to a `Teacher` structure where the retrieved teacher data will be stored.
 * 
 * @return int Returns 1 if the teacher is found and successfully retrieved, otherwise returns 0.
 * 
 * The function performs the following:
 * - Validates the provided ID and `Teacher` pointer.
 * - Opens the file `TEACHER_FILE` for reading.
 * - Iterates through the file line by line, parsing each line into a `Teacher` structure.
 * - Compares the parsed teacher's ID with the provided ID.
 * - If a match is found, the corresponding `Teacher` structure is populated and the search terminates.
 * 
 * @note
 * - The file is expected to have a CSV format with a header row.
 * - The `csvToTeacher` function is used to parse each line into a `Teacher` structure.
 * - If the file cannot be opened or the teacher is not found, an appropriate error message is displayed.
 * 
 * Example:
 * ```c
 * Teacher teacher;
 * int result = getTeacherById(101, &teacher);
 * if (result) {
 *     printf("Teacher Name: %s %s\n", teacher.fname, teacher.lname);
 * } else {
 *     printf("Teacher not found.\n");
 * }
 * ```
 */
int getTeacherById(int id, Teacher *teacher)
{
    FILE *fptr;
    Teacher teacherBuffer;
    char teachBuff[STR_CVS_LEN_OUT];
    char buffer[STR_CVS_LEN_IN];
    int isFound = 0;
    int numOfReadVal = 0;

    if(teacher == NULL || id < ID_INIT_VAL)
    {
        snprintf(buffer, sizeof(buffer) - 1, "ID %d is invalid or teacher didn't initialized", id);
        printfERROR(buffer);
        return 0;
    }

    fptr = fopen(TEACHER_FILE, "r");

    if(fptr == NULL)
    {
        printfERROR("File not found");
        return 0;
    }
    
    fgets(teachBuff, STR_CVS_LEN_OUT - 1, fptr); // reads header
    while (fgets(teachBuff, STR_CVS_LEN_OUT - 1, fptr) != NULL)
    {
        csvToTeacher(teachBuff, &teacherBuffer);
        if(id == teacherBuffer.id)
        {
            csvToTeacher(teachBuff, teacher);
            isFound = 1;
            break;
        }
    }

    if(!isFound  && !suppressErrMes)
    {
        snprintf(buffer, sizeof(buffer) - 1, "Teacher with ID %d not found", id);
        printfERROR(buffer);
    }

    fclose(fptr);
    return isFound;
}

/**
 * @brief Retrieves all students assigned to a teacher by the teacher's ID.
 *
 * This function retrieves a teacher's information using their ID and uses the
 * teacher's list of assigned student IDs to retrieve the corresponding students'
 * information. The retrieved students are stored in the provided `studentList` array.
 *
 * @param id The ID of the teacher whose assigned students are to be retrieved.
 * @param studentList Pointer to an array of `Student` structures to store the retrieved students.
 * 
 * @return int Returns the total number of students successfully retrieved.
 * 
 * The function performs the following:
 * - Retrieves the teacher's information using `getTeacherById`.
 * - Iterates through the teacher's list of student IDs.
 * - Calls `getStudentById` for each student ID and stores the results in the `studentList` array.
 * 
 * @note
 * - The `MAX_STUDENT_COUNT` constant is used to limit the number of students.
 * - Ensure that the `studentList` array is properly allocated before calling this function.
 * 
 * Example:
 * ```c
 * Student students[MAX_STUDENT_COUNT];
 * int numStudents = getAllStudentByTeacherId(101, students);
 * printf("Number of students retrieved: %d\n", numStudents);
 * for (int i = 0; i < numStudents; i++) {
 *     printf("Student ID: %d, Name: %s %s\n", students[i].id, students[i].fname, students[i].lname);
 * }
 * ```
 */
int getAllStudentByTeacherId(int id, Student *studentList)
{
    Teacher teacher;
    char teacherInCsv[STR_CVS_LEN_OUT];
    int result = 0;

    getTeacherById(id, &teacher);

    for (int i = 0; i < MAX_STUDENT_COUNT; i++)
    {
        if(teacher.studentsList.studentId[i] != 0) 
        {
            getStudentById(teacher.studentsList.studentId[i], &studentList[result]);
            result++;
        }
    }
    return result;
}

/**
 * @brief Updates the information of a student in the student file.
 *
 * This function modifies the information of a student identified by the given ID
 * in the file specified by `STUDENT_FILE`. The updated information is provided
 * via the `Student` structure passed as an argument.
 * 
 * @param id The ID of the student to be updated.
 * @param student Pointer to a `Student` structure containing the updated information.
 * 
 * @return int Returns 1 if the update is successful, otherwise returns 0.
 *
 * This function performs the following:
 * - Opens the `STUDENT_FILE` for reading.
 * - Creates a temporary file (`TEMP_FILE`) to store the updated data.
 * - Reads each line of the original file, and checks if the student ID matches the provided ID.
 * - If the ID matches, the updated student information is written to the temporary file.
 * - If the ID does not match, the original line is written to the temporary file.
 * - Once all lines are processed, the contents of the temporary file are copied back to the original file.
 * 
 * @note
 * - The file is expected to have a CSV format with a header row.
 * - The `initStudent`, `studentToCsv`, `csvToStudent`, and `copyFile` functions are assumed to be defined elsewhere.
 * - Ensure proper initialization of the `Student` structure and validation of inputs before calling this function.
 * 
 * @warning
 * - If the file cannot be opened or the temporary file cannot be created, the function returns 0.
 * - If no student with the specified ID is found, the function leaves the file unchanged and returns 0.
 * 
 * Example:
 * ```c
 * Student student;
 * student.id = 101;
 * strcpy(student.fname, "John");
 * strcpy(student.lname, "Doe");
 * // Set other fields...
 *
 * int result = editStudent(101, &student);
 * if (result) {
 *     printf("Student information updated successfully.\n");
 * } else {
 *     printf("Failed to update student information.\n");
 * }
 * ```
 */
int editStudent(int id, Student *student)
{
    FILE *fptr;           // Pointer for the original student file
    FILE *fptrtemp;       // Pointer for the temporary file
    Student studentBuffer; // Buffer to hold student data while reading
    char studentInCsv[STR_CVS_LEN_OUT];       // Holds the edited student data in CSV format
    char studentInCsvBuff[STR_CVS_LEN_OUT];   // Buffer to hold each line read from the file
    char editedStudentInCsv[STR_CVS_LEN_OUT]; // Placeholder for edited CSV data (currently unused)

    // Initialize the student buffer and convert the edited student object to CSV format
    initStudent(&studentBuffer);
    studentToCsv(student, studentInCsv);

    // Open the original file for reading
    fptr = fopen(STUDENT_FILE, "r");
    if (fptr == NULL)
    {
        printfERROR("Error in opening file for editing student info");
        return 0;
    }

    // Open a temporary file for writing
    fptrtemp = fopen(TEMP_FILE, "w");
    if (fptrtemp == NULL)
    {
        printfERROR("Error in opening file for editing student info");
        fclose(fptr); // Ensure the original file is closed
        return 0;
    }

    // Write the header row to the temporary file
    fprintf(fptrtemp, "id,first_name,last_name,date_of_birth,username,section,grades(MATH,SCI,ENG,FIL,HISTORY,PE,AVE)\n");

    // Skip the header row of the original file
    fgetsm(studentInCsvBuff, STR_CVS_LEN_OUT, fptr);
    
    // Process each row in the original file
    do
    {
        // Read the next line
        fgetsm(studentInCsvBuff, STR_CVS_LEN_OUT, fptr);

        // If the line is empty or invalid, stop processing
        if (strcmp(studentInCsvBuff, "") == 0 || studentInCsvBuff[0] == '\0') break;

        // Convert the CSV data to a `Student` structure
        csvToStudent(studentInCsvBuff, &studentBuffer);

        // If the ID matches, write the updated student data to the temporary file
        if (id == studentBuffer.id)
        {
            fprintf(fptrtemp, "%s\n", studentInCsv);
        }
        else // Otherwise, write the original data
        {
            fprintf(fptrtemp, "%s\n", studentInCsvBuff);
        }

    } while (!feof(fptr)); // Continue until the end of the file

    fclose(fptrtemp); // Close the temporary file
    fclose(fptr);     // Close the original file

    // Reopen the temporary file for reading and overwrite the original file
    fptrtemp = fopen(TEMP_FILE, "r");
    fptr = fopen(STUDENT_FILE, "w");

    // Copy the contents of the temporary file to the original file
    return copyFile(fptr, fptrtemp);
}


/**
 * @brief Updates the information of a teacher in the teacher file.
 *
 * This function modifies the information of a teacher identified by the given ID
 * in the file specified by `TEACHER_FILE`. The updated information is provided
 * via the `Teacher` structure passed as an argument.
 * 
 * @param id The ID of the teacher to be updated.
 * @param teacher Pointer to a `Teacher` structure containing the updated information.
 * 
 * @return int Returns 1 if the update is successful, otherwise returns 0.
 *
 * This function performs the following:
 * - Opens the `TEACHER_FILE` for reading.
 * - Creates a temporary file (`TEMP_FILE`) to store the updated data.
 * - Reads each line of the original file, and checks if the teacher ID matches the provided ID.
 * - If the ID matches, the updated teacher information is written to the temporary file.
 * - If the ID does not match, the original line is written to the temporary file.
 * - Once all lines are processed, the contents of the temporary file are copied back to the original file.
 * 
 * @note
 * - The file is expected to have a CSV format with a header row.
 * - The `initTeacher`, `teacherToCsv`, `csvToTeacher`, and `copyFile` functions are assumed to be defined elsewhere.
 * - Ensure proper initialization of the `Teacher` structure and validation of inputs before calling this function.
 * 
 * @warning
 * - If the file cannot be opened or the temporary file cannot be created, the function returns 0.
 * - If no teacher with the specified ID is found, the function leaves the file unchanged and returns 0.
 * 
 * Example:
 * ```c
 * Teacher teacher;
 * teacher.id = 201;
 * strcpy(teacher.fname, "Alice");
 * strcpy(teacher.lname, "Smith");
 * // Set other fields...
 *
 * int result = editTeacher(201, &teacher);
 * if (result) {
 *     printf("Teacher information updated successfully.\n");
 * } else {
 *     printf("Failed to update teacher information.\n");
 * }
 * ```
 */
int editTeacher(int id, Teacher *teacher)
{
    FILE *fptr;            // Pointer to the original teacher file
    FILE *fptrtemp;        // Pointer to the temporary file
    Teacher teacherBuffer; // Buffer to store teacher data while reading
    char teacherInCsv[STR_CVS_LEN_OUT];        // CSV-formatted string for the edited teacher
    char teacherInCsvBuff[STR_CVS_LEN_OUT];    // Buffer to hold each line read from the file
    char editedTeacherInCsv[STR_CVS_LEN_OUT];  // Placeholder for edited CSV data (currently unused)

    // Initialize the teacher buffer and convert the edited teacher object to CSV format
    initTeacher(&teacherBuffer);
    teacherToCsv(teacher, teacherInCsv);

    // Open the original file for reading
    fptr = fopen(TEACHER_FILE, "r");
    if (fptr == NULL)
    {
        printfERROR("Error in opening file for editing teacher info");
        return 0;
    }

    // Open a temporary file for writing
    fptrtemp = fopen(TEMP_FILE, "w");
    if (fptrtemp == NULL)
    {
        printfERROR("Error in opening file for editing teacher info");
        fclose(fptr); // Ensure the original file is closed
        return 0;
    }

    // Write the header row to the temporary file
    fprintf(fptrtemp, "id,first_name,last_name,date_of_birth,username,section,{student_list}\n");

    // Skip the header row of the original file
    fgetsm(teacherInCsvBuff, STR_CVS_LEN_OUT, fptr);

    // Process each row in the original file
    do
    {
        // Read the next line
        fgetsm(teacherInCsvBuff, STR_CVS_LEN_OUT, fptr);

        // If the line is empty or invalid, stop processing
        if (strcmp(teacherInCsvBuff, "") == 0 || teacherInCsvBuff[0] == '\0') break;

        // Convert the CSV data to a `Teacher` structure
        csvToTeacher(teacherInCsvBuff, &teacherBuffer);

        // If the ID matches, write the updated teacher data to the temporary file
        if (id == teacherBuffer.id)
        {
            fprintf(fptrtemp, "%s\n", teacherInCsv);
        }
        else // Otherwise, write the original data
        {
            fprintf(fptrtemp, "%s\n", teacherInCsvBuff);
        }

    } while (!feof(fptr)); // Continue until the end of the file

    fclose(fptrtemp); // Close the temporary file
    fclose(fptr);     // Close the original file

    // Reopen the temporary file for reading and overwrite the original file
    fptrtemp = fopen(TEMP_FILE, "r");
    fptr = fopen(TEACHER_FILE, "w");

    // Copy the contents of the temporary file to the original file
    return copyFile(fptr, fptrtemp);
}


/**
 * @brief Copies the contents of one file to another.
 *
 * This function reads the content from a source file (`fptrFrom`) and writes it to a destination file (`fptrTo`).
 * 
 * @param fptrTo Pointer to the destination file, opened in write mode.
 * @param fptrFrom Pointer to the source file, opened in read mode.
 * 
 * @return int Returns 1 if the copy operation is successful, otherwise returns 0.
 *
 * The function performs the following:
 * - Checks if either file pointer is `NULL`. If so, it outputs an error message and returns 0.
 * - Reads the content of the source file character by character using `fgetc`.
 * - Writes each character to the destination file using `fputc`.
 * - Closes both files after the operation is complete.
 * 
 * @note
 * - The file pointers must be properly initialized and opened in the correct modes before calling this function.
 * - Ensure the source file exists and the destination file is writable.
 * 
 * @warning
 * - If either file pointer is `NULL`, the function will return 0 without copying any content.
 * - The caller is responsible for ensuring the files are not overwritten unintentionally.
 * 
 * Example:
 * ```c
 * FILE *source = fopen("source.txt", "r");
 * FILE *destination = fopen("destination.txt", "w");
 * 
 * if (copyFile(destination, source)) {
 *     printf("File copied successfully.\n");
 * } else {
 *     printf("Failed to copy the file.\n");
 * }
 * ```
 */
int copyFile(FILE *fptrTo, FILE *fptrFrom)
{
    char c; // Variable to store characters being copied

    // Check if the file pointers are valid
    if (fptrTo == NULL || fptrFrom == NULL)
    {
        printfERROR("Copying file failed, file not found");
        return 0; // Return 0 on failure
    }

    // Read and copy the file content character by character
    while ((c = fgetc(fptrFrom)) != EOF)
    {
        fputc(c, fptrTo); // Write each character to the destination file
    }

    // Close the source and destination files
    fclose(fptrFrom);
    fclose(fptrTo);

    return 1; // Return 1 on success
}


/**
 * @brief Saves a user's password to a file associated with their ID.
 *
 * This function attempts to save a user's password in a file specified by the 
 * macro PASSWORD_FILE. It stores the user's ID and password in the format 
 * "id,password" in the file. If the file does not already exist, it will be 
 * created, and a header ("id,password") will be written. The password entry 
 * is appended to the file each time this function is called.
 *
 * @param id The user's ID (integer).
 * @param password The user's password (string).
 *
 * @return Returns 1 if the password was successfully saved, otherwise 0 in case of failure.
 */
int savePassword(int id, char *password)
{
    FILE *fptr; /**< File pointer for opening the password file */
    char idstr[10]; /**< Temporary string to hold the user ID as a string */
    char passwordFormat[STR_CVS_LEN_IN]; /**< String to hold the formatted "id,password" entry */

    fptr = fopen(PASSWORD_FILE, "r"); /**< Try opening the file in read mode */

    sprintf(idstr, "%d", id); /**< Convert the integer ID to string */
    strcpy(passwordFormat, idstr); /**< Copy the ID string to passwordFormat */
    strcat(passwordFormat, ","); /**< Append a comma between the ID and password */
    strcat(passwordFormat, password); /**< Append the password to complete the entry */

    if (fptr == NULL) /**< Check if the file does not exist */
    {
        fptr = fopen(PASSWORD_FILE, "w"); /**< Open the file in write mode */
        fprintf(fptr, "id,password\n"); /**< Write header to the file */
        fprintf(fptr, "%s\n", passwordFormat); /**< Write the user password entry */
    }
    
    fptr = fopen(PASSWORD_FILE, "a"); /**< Open the file in append mode */
    fprintf(fptr, "%s\n", passwordFormat); /**< Append the user password entry */
    fclose(fptr); /**< Close the file */
    
    return 1; /**< Return 1 on success */
}


/**
 * @brief Retrieves a user's password by their ID from the password file.
 *
 * This function searches for a user's password in a file specified by the 
 * macro PASSWORD_FILE. The file is expected to contain user data in the 
 * format "id,password", where the ID is an integer, and the password is a string.
 * If the file cannot be opened or if the user is not found, the function 
 * returns 0 and sets a default message in the password string. If the password 
 * is successfully retrieved, it is copied to the provided password string, 
 * and the function returns 1.
 *
 * @param id The user's ID (integer).
 * @param password A pointer to a string where the password will be copied.
 *
 * @return Returns 1 if the password is found and copied, otherwise returns 0 if the password was not found.
 */
int getPasswordById(int id, char *password)
{
    disable(1);
    FILE *fptr; /**< File pointer for opening the password file */
    char idstr[10]; /**< Temporary string to hold the user ID as a string */
    char *delim = ","; /**< Delimiter used to separate ID and password in the file */
    char passwordFileContent[STR_CVS_LEN_OUT]; /**< Buffer to hold each line from the password file */
    char passwordBuffer[MAX_FILE_LINE][STR_CVS_LEN_IN]; /**< Buffer to store split user data (ID, password) */
    
    fptr = fopen(PASSWORD_FILE, "r"); /**< Try opening the password file in read mode */

    if(fptr == NULL) /**< Check if the file does not exist */
    {
        printfERROR("Password file not found");
        strcpy(password, "AYAWW KO NAAAAAAAAAAAAAA!!!"); /**< Default message if file not found */
        return 0; /**< Return 0 if the file could not be opened */
    }

    strcpy(password, "SUKO NAAAAAAAAAAAAAA!!!"); /**< Default password message in case user not found */
    sprintf(idstr, "%d", id); /**< Convert the integer ID to a string */

    fgetsm(passwordFileContent, sizeof(passwordFileContent), fptr); /**< Read the first line (header) from the file */
    do
    {
        fgetsm(passwordFileContent, sizeof(passwordFileContent), fptr); /**< Read the next line from the file */
        if(strcmp(passwordFileContent, "") == 0 || passwordFileContent[0] == '\0') break; /**< Check for end of file */
        
        strSplit(passwordFileContent, passwordBuffer, delim); /**< Split the line into ID and password */
        
        if(strcmp(idstr, passwordBuffer[0]) == 0) /**< Check if the ID matches */
        {
            strcpy(password, passwordBuffer[1]); /**< Copy the password if ID matches */
            fclose(fptr); /**< Close the file */
            return 1; /**< Return 1 if password is found */
        }
    } while (!feof(fptr)); /**< Continue until end of file is reached */
    

    disable(0);
    fclose(fptr); /**< Close the file if ID not found */
    return 0; /**< Return 0 if the ID was not found in the file */
}

