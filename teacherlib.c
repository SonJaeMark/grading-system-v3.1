#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "stringlib.h"
#include "userfilelib.h"
#include "userlib.h"
#include "studentlib.h" 


#define NUM_GRADES 6  // Define yung number ng subjects

/**
 * @brief Calculates the average grade of a student.
 *
 * This function retrieves individual subject grades from the Student structure, calculates the total,
 * and then computes the average by dividing the total grades by the number of subjects.
 *
 * @param student The Student object containing the grades to calculate the average.
 * @return float The calculated average grade.
 */
float getAve(Student student) {
    float gradesArray[NUM_GRADES]; // Array to hold individual grades
    float totalGrades = 0.0;      // Variable to store the total of all grades

    // Store individual grades in an array
    gradesArray[0] = student.grades.MATH;
    gradesArray[1] = student.grades.SCI;
    gradesArray[2] = student.grades.ENG;
    gradesArray[3] = student.grades.FIL;
    gradesArray[4] = student.grades.HIS;
    gradesArray[5] = student.grades.PE;

    // Calculate total grades
    for (int i = 0; i < NUM_GRADES; i++) {
        totalGrades += gradesArray[i];
    }

    // Calculate and return the average
    return totalGrades / NUM_GRADES;
}


/**
 * @brief Removes duplicate integers from an array and updates its size.
 *
 * This function sorts the array in ascending order, removes any duplicate values, 
 * and updates the size of the array to reflect the new unique values.
 *
 * @param data The array of integers to process.
 * @param size A pointer to the size of the array, which is updated to the new size.
 */
void removeDuplicate(int data[], int *size) {
    int indicator = 1;   // Flag to control the sorting loop
    int newSize = 0;     // New size of the array after duplicates are removed
    int tempOut[*size];  // Temporary array to store unique values
    int temp = 0;        // Variable for tracking the last unique number

    // Sort the array in ascending order
    while (indicator) {
        indicator = 0;
        for (int i = 0; i < *size - 1; i++) {
            if (data[i] > data[i + 1]) {
                // Swap elements if out of order
                int temp = data[i];
                data[i] = data[i + 1];
                data[i + 1] = temp;
                indicator = 1;
            }
        }
    }

    // Remove duplicates
    for (int i = 0; i < *size; i++) {
        if (temp != data[i]) {
            temp = data[i];
            tempOut[newSize] = data[i];
            newSize++;
        }
    }

    // Copy unique values back to the original array
    for (int i = 0; i < newSize; i++) {
        data[i] = tempOut[i];
    }

    // Update the size
    *size = newSize;
}

/**
 * @brief Finds unique elements in the compare array not present in the base array.
 *
 * This function identifies and retains only the unique elements in the compare array that do not exist in the base array.
 *
 * @param base The base array to compare against.
 * @param baseSize The size of the base array.
 * @param compare The array to filter for unique values.
 * @param compareSize A pointer to the size of the compare array, which is updated to the new size.
 */
void getUnique(int base[], int baseSize, int compare[], int *compareSize) {
    int newSize = 0;          // New size for the compare array after filtering
    int temp[*compareSize];   // Temporary array to store elements of the compare array

    // Copy elements of the compare array to a temporary array
    for (int i = 0; i < *compareSize; i++) {
        temp[i] = compare[i];
    }

    // Remove elements from temp that exist in the base array
    for (int i = 0; i < *compareSize; i++) {
        for (int j = 0; j < baseSize; j++) {
            if (temp[i] == base[j]) {
                temp[i] = 0; // Mark as duplicate
                break;
            }
        }
    }

    // Retain only the unique elements
    for (int i = 0; i < *compareSize; i++) {
        if (temp[i] != 0) {
            compare[newSize] = temp[i];
            newSize++;
        }
    }

    // Update the size of the compare array
    *compareSize = newSize;
}

/**
 * @brief Filters elements in the compare array that match elements in the base array.
 *
 * This function identifies elements in the compare array that are also present in the base array
 * and modifies the compare array to contain only the matching elements. The size of the compare 
 * array is updated accordingly.
 *
 * @param base The base array containing reference values.
 * @param baseSize The size of the base array.
 * @param compare The array to filter for matching values.
 * @param compareSize A pointer to the size of the compare array, which is updated to the new size.
 */
void getMatch(int base[], int baseSize, int compare[], int *compareSize) {
    int newSize = 0;         // Tracks the new size of the compare array after filtering
    int temp[*compareSize];  // Temporary array to store initial elements of the compare array

    // Copy elements of the compare array to a temporary array
    for (int i = 0; i < *compareSize; i++) {
        temp[i] = compare[i];
    }

    // Check for matching elements and store them in the compare array
    for (int i = 0; i < *compareSize; i++) {
        for (int j = 0; j < baseSize; j++) {
            if (temp[i] == base[j]) { // If a match is found
                compare[newSize] = temp[i];
                newSize++;
            }
        }
    }

    // Update the size of the compare array
    *compareSize = newSize;
}







/**
 * @brief Displays all students associated with the logged-in teacher.
 *
 * This function retrieves and displays all students linked to the teacher's ID. 
 * If a student is logged in, access to this function is denied.
 *
 * @param user A pointer to the User object containing teacher and student details.
 * @return int The number of students retrieved. Returns 0 if access is denied.
 */
int viewAllMyStudents(User *user) {
    int numOfStud = 0; // Number of students retrieved

    // Check if the logged-in user is a student
    if (user->student->id != 0) {
        printfWARNNING("You are not allowed to access this!");
        return 0;
    }

    // Retrieve all students linked to the teacher's ID
    numOfStud = getAllStudentByTeacherId(user->teacher->id, user->student);

    setColor(GREEN_TEXT);
    // Display the list of students
    for (int i = 0; i < numOfStud; i++) {
        printf("[%d] %d %s %s\n", i + 1, user->student[i].id, user->student[i].fname, user->student[i].lname);
    }

    // Reinitialize the student array to prevent residual data
    initStudent(user->student);

    return numOfStud;
}


/**
 * @brief Adds one or more students to a teacher's class.
 *
 * This function allows a teacher to add students to their class by inputting student IDs. 
 * It ensures that duplicate IDs are removed, the maximum allowable number of students (10) is not exceeded, 
 * and all updates to the teacher and student information are saved.
 *
 * @param user A pointer to a User object. The User object must represent a teacher or an administrator.
 *             - If the user is a student, the function will abort with a warning.
 * @return The number of students successfully added to the class.
 */
int addStudentToClass(User *user)
{
    int succeedCount = 0;          // Count of successfully added students
    int currentStudCount = 0;      // Number of current students in the class
    int inputIdsHolderCount = MAX_STUDENT_COUNT; 
    int studRetrievedCount = MAX_STUDENT_COUNT;
    int inputIdsSize = MAX_STUDENT_COUNT;
    char strBuffer[STR_CVS_LEN_OUT];
    int studRetrieved[studRetrievedCount];
    int inputIds[inputIdsSize];
    int inputIdsHolder[inputIdsHolderCount];
    int inputIdCount = 0;
    char buffer[STR_CVS_LEN_OUT];

    // Check if the user is a student
    if (user->student->id != 0)
    {
        printfWARNNING("!!You are not allowed to access this!");
        return 0;
    }

    // Retrieve current students in the teacher's class
    for (int i = 0; i < MAX_STUDENT_COUNT; i++)
    {
        if (user->teacher->studentsList.studentId[i] != 0)
        {
            studRetrieved[i] = user->teacher->studentsList.studentId[i];
            currentStudCount++;
        }
    }
    studRetrievedCount = currentStudCount;

    // Check if the class is already at maximum capacity
    if (currentStudCount == 10)
    {
        printfWARNNING("Not able to add more students, you've reached the maximum student count allowable!");
        return 0;
    }

    // Initialize input IDs to zero
    for (int i = 0; i < MAX_STUDENT_COUNT; i++)
    {
        inputIds[i] = 0;
    }

    // Loop to get valid student IDs from the user
    while (1)
    {
        resetColor();
        printf("Enter the ID of the student(s) you want to add to your class (separate with space if more than 1): ");
        fgetsm(strBuffer, STR_CVS_LEN_OUT, stdin);

        // Parse student IDs from input
        inputIdCount = sscanf(
            strBuffer, "%d %d %d %d %d %d %d %d %d %d",
            &inputIds[0], &inputIds[1], &inputIds[2], &inputIds[3], &inputIds[4],
            &inputIds[5], &inputIds[6], &inputIds[7], &inputIds[8], &inputIds[9]
        );

        // Remove duplicate IDs
        removeDuplicate(inputIds, &inputIdsSize);

        // Store input IDs in the holder array
        for (int i = 0; i < inputIdsSize; i++)
        {
            inputIdsHolder[i] = inputIds[i];
        }
        inputIdsHolderCount = inputIdsSize;

        // Ensure the total count doesn't exceed the maximum allowed
        getUnique(studRetrieved, studRetrievedCount, inputIds, &inputIdsSize);
        if (inputIdsSize + currentStudCount <= 10) break;

        printfWARNNING("Input ID/s exceed the maximum allowable student count.");
    }

    // Add students to the class
    for (int i = 0; i < inputIdsSize; i++)
    {
        if (getStudentById(inputIds[i], user->student) &&
            strcpy(user->student->section, user->teacher->section) != NULL &&
            editStudent(user->student->id, user->student))
        {
            snprintf(buffer, sizeof(buffer) - 1, "Student %d successfully added to your class!", inputIds[i]);
            printfSUCCESS(buffer);
            for (int j = 0; j < MAX_STUDENT_COUNT; j++)
            {
                if (user->teacher->studentsList.studentId[j] == 0)
                {
                    user->teacher->studentsList.studentId[j] = inputIds[i];
                    j = MAX_STUDENT_COUNT;
                }
            }
            succeedCount++;
        }
        else
        {
            snprintf(buffer, sizeof(buffer) - 1, "Student %d failed to add to your class!", inputIds[i]);
            printfERROR(buffer);
        }
    }

    // Warn about duplicate IDs already in the class
    getMatch(studRetrieved, studRetrievedCount, inputIdsHolder, &inputIdsHolderCount);
    for (int i = 0; i < inputIdsHolderCount; i++)
    {
        snprintf(buffer, sizeof(buffer) - 1, "Student ID no.%d is already in your class.", inputIdsHolder[i]);
        printfWARNNING(buffer);
    }

    // Save changes to the teacher's information
    if (editTeacher(user->teacher->id, user->teacher))
    {
        snprintf(buffer, sizeof(buffer) - 1, "Added %d students to your class.", succeedCount);
        printfSUCCESS(buffer);
        snprintf(buffer, sizeof(buffer) - 1, "You now have %d students in total in your class.", succeedCount + currentStudCount);
        printfSUCCESS(buffer);
    }
    else
    {
        printfERROR("Failed to edit teacher info, please contact the admin!");
        return 0;
    }

    // Reinitialize the student object and return the count of successfully added students
    initStudent(user->student);
    return succeedCount;
}


/**
 * @brief Removes one or more students from a teacher's class.
 *
 * This function allows a teacher to remove students from their class by inputting student IDs.
 * It ensures that valid student IDs are processed, prevents removal of students not currently in the class,
 * and updates both the teacher and student information.
 *
 * @param user A pointer to a User object. The User object must represent a teacher or an administrator.
 *             - If the user is a student, the function will abort with a warning.
 * @return The number of students successfully removed from the class.
 */
int removeStudentToClass(User *user)
{
    int succeedCount = 0;          // Count of successfully removed students
    int currentStudCount = 0;      // Number of current students in the class
    int inputIdsHolderCount = MAX_STUDENT_COUNT;
    int studRetrievedCount = MAX_STUDENT_COUNT;
    int inputIdsSize = MAX_STUDENT_COUNT;
    char strBuffer[STR_CVS_LEN_OUT];
    int studRetrieved[studRetrievedCount];
    int inputIds[inputIdsSize];
    int inputIdsHolder[inputIdsHolderCount];
    int inputIdCount = 0;
    char buffer[STR_CVS_LEN_OUT];

    // Check if the user is a student
    if (user->student->id != 0)
    {
        printfWARNNING("You are not allowed to access this!");
        return 0;
    }

    // Retrieve the current list of students in the teacher's class
    for (int i = 0; i < MAX_STUDENT_COUNT; i++)
    {
        if (user->teacher->studentsList.studentId[i] != 0)
        {
            studRetrieved[i] = user->teacher->studentsList.studentId[i];
            currentStudCount++;
        }
    }
    studRetrievedCount = currentStudCount;

    // Initialize the input IDs array to zero
    for (int i = 0; i < MAX_STUDENT_COUNT; i++)
    {
        inputIds[i] = 0;
    }

    // Loop to get valid student IDs from the user
    while (1)
    {
        resetColor();
        printf("Enter the ID of the student(s) you want to remove from your class (separate with space if more than 1): ");
        fgetsm(strBuffer, STR_CVS_LEN_OUT, stdin);

        // Parse student IDs from input
        inputIdCount = sscanf(
            strBuffer, "%d %d %d %d %d %d %d %d %d %d",
            &inputIds[0], &inputIds[1], &inputIds[2], &inputIds[3], &inputIds[4],
            &inputIds[5], &inputIds[6], &inputIds[7], &inputIds[8], &inputIds[9]
        );

        // Remove duplicate IDs from the input
        removeDuplicate(inputIds, &inputIdsSize);

        // Store input IDs in the holder array
        for (int i = 0; i < inputIdsSize; i++)
        {
            inputIdsHolder[i] = inputIds[i];
        }
        inputIdsHolderCount = inputIdsSize;

        // Ensure that the removal will not result in a negative student count
        getMatch(studRetrieved, studRetrievedCount, inputIds, &inputIdsSize);
        if (currentStudCount - inputIdsSize >= 0) break;

        printfWARNNING("Input ID/s exceed the total student count.");
    }

    // Remove the students from the class
    for (int i = 0; i < inputIdsSize; i++)
    {
        if (getStudentById(inputIds[i], user->student) &&
            strcpy(user->student->section, "A0") != NULL &&
            editStudent(user->student->id, user->student))
        {
            snprintf(buffer, sizeof(buffer) - 1, "Student %d successfully removed from your class!", inputIds[i]);
            printfSUCCESS(buffer);

            // Remove the student ID from the teacher's list
            for (int j = 0; j < MAX_STUDENT_COUNT; j++)
            {
                if (user->teacher->studentsList.studentId[j] == inputIds[i])
                {
                    user->teacher->studentsList.studentId[j] = 0;
                    break;
                }
            }
            succeedCount++;
        }
        else
        {
            snprintf(buffer, sizeof(buffer) - 1, "Student %d failed to be removed from your class!", inputIds[i]);
            printfERROR(buffer);
        }
    }

    // Warn about IDs not found in the class
    getUnique(studRetrieved, studRetrievedCount, inputIdsHolder, &inputIdsHolderCount);
    for (int i = 0; i < inputIdsHolderCount; i++)
    {
        snprintf(buffer, sizeof(buffer) - 1, "Student ID no.%d is not in your class.", inputIdsHolder[i]);
        printfWARNNING(buffer);
    }

    // Save changes to the teacher's information
    if (editTeacher(user->teacher->id, user->teacher))
    {
        snprintf(buffer, sizeof(buffer) - 1, "Removed %d students from your class.", succeedCount);
        printfSUCCESS(buffer);
        snprintf(buffer, sizeof(buffer) - 1, "You now have %d students in total in your class.", currentStudCount - succeedCount);
        printfSUCCESS(buffer);
    }
    else
    {
        printfERROR("Failed to edit teacher info, please contact the admin!");
        return 0;
    }

    // Reinitialize the student object and return the count of successfully removed students
    initStudent(user->student);
    return succeedCount;
}



/**
 * @brief View the grades of a specific student by their ID.
 *
 * This function allows a teacher to view the grades of a student
 * if the student is part of their class. The function validates
 * the student ID and retrieves the grades for display.
 *
 * @param user A pointer to a User object. Must represent a teacher.
 */
void viewGradesOfStudentById(User *user)
{
    int isExit = 0;                // Flag to check if student ID is valid
    int inputIdsSize = MAX_STUDENT_COUNT;
    char strBuffer[STR_CVS_LEN_OUT];
    int inputIds[inputIdsSize];
    int inputIdCount = 0;
    char buffer[STR_CVS_LEN_OUT];

    // Check if the user is a student
    if (user->student->id != 0)
    {
        printfWARNNING("You are not allowed to access this!");
        return;
    }

    // Loop until a valid student ID is entered
    while (1)
    {
        resetColor();
        printf("Enter the ID of the student you want to see grades: ");
        fgetsm(strBuffer, STR_CVS_LEN_OUT, stdin);

        // Parse the input ID
        inputIdCount = sscanf(strBuffer, "%d", &inputIds[0]);

        // Validate if the student ID is part of the teacher's class
        for (int i = 0; i < MAX_STUDENT_COUNT; i++)
        {
            if (inputIds[0] == user->teacher->studentsList.studentId[i])
            {
                isExit = 1;
            }
        }
        if (isExit) break;

        snprintf(buffer, sizeof(buffer) - 1, "ID no.%d is not in your class.", inputIds[0]);
        printfWARNNING(buffer);
    }

    // Retrieve and display the student's grades
    setColor(GREEN_TEXT);
    getStudentById(inputIds[0], user->student);
    viewMyGrades(user);
    initStudent(user->student);
}

/**
 * @brief Assign grades to a student in the teacher's class.
 *
 * This function allows a teacher to give grades to a specific student
 * in their class. Grades are assigned for predefined subjects and 
 * saved only upon confirmation.
 *
 * @param user A pointer to a User object. Must represent a teacher.
 */
void giveGrades(User *user)
{
    int isExit = 0;                // Flag to check if student ID is valid
    int inputIdsSize = MAX_STUDENT_COUNT;
    char strBuffer[STR_CVS_LEN_OUT];
    int inputIds[inputIdsSize];
    int inputIdCount = 0;
    float grades[7];
    char buffer[STR_CVS_LEN_OUT];

    char subjects[6][4] = {
        "MAT", "SCI", "ENG", "FIL", "HIS", "PE"
    };

    // Check if the user is a student
    if (user->student->id != 0)
    {
        printfWARNNING("You are not allowed to access this!\n");
        return;
    }

    // Loop until a valid student ID is entered
    while (1)
    {
        resetColor();
        printf("Enter the ID of the student you want to assign grades to: ");
        fgetsm(strBuffer, STR_CVS_LEN_OUT, stdin);

        // Parse the input ID
        inputIdCount = sscanf(strBuffer, "%d", &inputIds[0]);

        // Validate if the student ID is part of the teacher's class
        for (int i = 0; i < MAX_STUDENT_COUNT; i++)
        {
            if (inputIds[0] == user->teacher->studentsList.studentId[i])
            {
                isExit = 1;
            }
        }
        if (isExit) break;

        snprintf(buffer, sizeof(buffer) - 1, "ID no.%d is not in your class.", inputIds[0]);
        printfWARNNING(buffer);
    }

    // Retrieve the student object for grade assignment
    getStudentById(inputIds[0], user->student);

    // Prompt the teacher to enter grades for each subject
    printf("Enter grades for each subject:\n");
    for (int i = 0; i < 6; i++)
    {
        printf("Enter grade for %s: ", subjects[i]);
        fgetsm(strBuffer, STR_CVS_LEN_OUT, stdin);
        sscanf(strBuffer, "%f", &grades[i]);
    }

    // Confirmation before saving grades
    while (1)
    {
        resetColor();
        printf("Save changes? \n[y] Yes || [n] No: ");
        fgetsm(strBuffer, sizeof(strBuffer), stdin);

        if (strcmp("y", strBuffer) == 0) break;
        else if (strcmp("n", strBuffer) == 0)
        {
            printfSUCCESS("Grades not saved");
            return;
        }
        else printfWARNNING("Enter [y] for yes and [n] for no");
    }

    // Assign grades to the student object
    user->student->grades.MATH = grades[0];
    user->student->grades.SCI = grades[1];
    user->student->grades.ENG = grades[2];
    user->student->grades.FIL = grades[3];
    user->student->grades.HIS = grades[4];
    user->student->grades.PE = grades[5];

    user->student->grades.AVE = getAve(user->student[0]);

    // Save the student's grades and provide feedback
    if (editStudent(inputIds[0], user->student))
    {
        printfSUCCESS("Grades successfully saved!");
        printf("Do you want to view the grades? [y] Yes || [n] No: ");
        fgetsm(strBuffer, STR_CVS_LEN_OUT, stdin);

        if (strcmp(strBuffer, "y") == 0)
        {
            viewMyGrades(user);
        }
        else if (strcmp("n", strBuffer) == 0)
        {
            initStudent(user->student);
            return;
        }
        else printfWARNNING("Enter [y] for yes and [n] for no");
    }
    else
    {
        printfERROR("Error in saving grades!");
    }

    // Reinitialize the student object
    initStudent(user->student);
}




