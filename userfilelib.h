#pragma once

#define STR_CVS_LEN_IN 64
#define STR_CVS_LEN_OUT 256
#define MAX_FILE_LINE 256
#define STRUCT_MAX_CHAR 32

#define STUDENT_FILE "ffile_student.txt"
#define TEACHER_FILE "ffile_teacher.txt"
#define ID_VAL_FILE "ffile_id_val.txt"
#define TEMP_FILE "ffile_temp.txt"
#define LOG_FILE "ffile_log.txt"
#define PASSWORD_FILE "ffile_password.txt"
#define ID_INIT_VAL 240000

#define MAX_STUDENT_COUNT 10

// Date and Grades Information
typedef struct Grades
{
    float MATH;
    float SCI;
    float ENG;
    float FIL;
    float HIS;
    float PE;
    float AVE;
} Grades;

typedef struct Date
{
    int MM;
    int DD;
    int YYYY;
} Date;

// Student Information
typedef struct Student
{
    int id;
    char fname[STRUCT_MAX_CHAR];
    char lname[STRUCT_MAX_CHAR];
    struct Date dateOfBirth;
    char userName[STRUCT_MAX_CHAR];
    char password[STRUCT_MAX_CHAR];
    char section[STRUCT_MAX_CHAR];
    struct Grades grades;
} Student;


// Teacher Information
typedef struct StudentList
{
    int studentId[MAX_STUDENT_COUNT];
} StudentList;

typedef struct Teacher
{
    int id;
    char fname[STRUCT_MAX_CHAR];
    char lname[STRUCT_MAX_CHAR];
    struct Date dateOfBirth;
    char userName[STRUCT_MAX_CHAR];
    char password[STRUCT_MAX_CHAR];
    char section[STRUCT_MAX_CHAR];
    struct StudentList studentsList;
} Teacher;

int suppressErrMes(int isSuppress);
int generateId();

int saveStudent(char *studentInfoCsv);
int saveTeacher(char *teacherInfoCsv);

int getStudentById(int id, Student *student);
int getTeacherById(int id, Teacher *teacher);

int getAllStudentByTeacherId(int id, Student *studentList);

int editStudent(int id, Student *student);
int editTeacher(int id, Teacher *teacher);

int copyFile(FILE *fptrTo, FILE *fptrFrom);

int savePassword(int id, char *password);
int getPasswordById(int id, char *password);
