
int dateOfBirthValidation(int MM, int DD, int YYYY)
{
    int notLeapYear = YYYY % 4;
    int maxDates[13] = {0, 31, notLeapYear ? 28 : 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if( MM > 12 || MM < 1 || DD < 1 || YYYY > 2013 || YYYY < 1965) return 0;
    if(DD > maxDates[MM]) return 0;
    
    return 1;
}