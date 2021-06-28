/************************************************************/
/*Author: Vijay Seshu R                                     */
/*Date: 25-05-2021                                          */
/*Version: 1.0                                              */
/*Change log:                                               */
/************************************************************/

/************ Header files ****************************/
#include<stdio.h>
#include<time.h>
#include<stdlib.h>

/***************** Macros ****************************/
#define YES (1)
#define NO (0)
#define PRINT_EXE_TIME (1)
#define PRINT_CSEQ (0)

/*************** StringLength *******************************/
/*Function: StringLength                                    */
/*Description: calculates string length                     */
/*Input: string pointer                                     */
/*Return type: unsigned long long                           */
/************************************************************/
unsigned long long StringLength(char* str)
{
    unsigned long long count = 0;
    if (str != NULL) while (str[count])count++;
    return count;
}
/******************** PowerOf *******************************/
/*Function: PowerOf                                         */
/*Description: calculates power of given base               */
/*Input: num for base, pow for power index                  */
/*Return type: unsigned long long                           */
/************************************************************/
unsigned long long PowerOf(unsigned long long num, unsigned long long pow)
{
    unsigned long long res = 1;
    while (pow--)res *= num;
    return res;
}
/******************* StrToi64 *******************************/
/*Function: StrToi64                                        */
/*Description: Converts string to 64bit integer             */
/*Input: string pointer                                     */
/*Return type: unsigned long long                           */
/************************************************************/
unsigned long long StrToi64(char* str)
{
    unsigned long long i = StringLength(str), j = 0;
    unsigned long long res = 0;
    if(str != NULL) while (i)
    {
        res += (str[i-- - 1] - 48) * PowerOf(10, j++);
    }
    return res;
}
/*************** Collatz Main *******************************/
/*Function: main                                            */
/*Description: Main function to find the starting number    */
/*below a given limit that has the longest Collatz sequence.*/
/*Input: Upper-limit given in argv[1]                       */
/*Output: Number with longest collatz sequence              */
/*        Length of the sequence                            */
/*        Program statistics                                */
/*Return type: int                                          */
/************************************************************/
int main(int argc, char* argv[]) {
    //-Local variables
    unsigned long long input_num = 0, LongCSNum = 0, LongCSCount = 0, Upper_Limit = 0, count = 0;
    char ExitPath = NO; //-if ExitPath is enabled, no further functional execution will happen
    clock_t start, end;
    double seconds = 0;

    //-arguments check
    if (argc == 1)
    {
        printf("\n\'Upper limit\' argument not provided.\n");
    }
    else if (argc == 2)
    {

        char* input_str = argv[1];
        char i = 0;
        //-validate input
        while (input_str[i] != NULL)
        {
            //-ASCII check for input provided
            if (input_str[i] < 48 /* 0 */ || input_str[i] > 57 /* 9 */)
            {
                //-Enable exit: other than 0-9 detected in input
                ExitPath = YES;
                break;
            }
            i++;
        }//-end: while (input_str[i] != NULL)
        if (!ExitPath)
        {
            //-Valid argument received
            start = clock();
            Upper_Limit = StrToi64(input_str);
            printf("\nRunning Program One (code simplicity and low memory usage) for upper limit: %llu", Upper_Limit);
            LongCSCount = 0;
            LongCSNum = 0;
            //- Loop that finds the starting number below a given limit that has the longest Collatz sequence
            for (unsigned long long i = Upper_Limit-1; i > 1; i--)
            {
                const unsigned long long max_valueof_i = 6148914691236517204/*0x5555555555555554*/; //- calculated as (sizeof(long long) - 1) / 3
                input_num = i;
                count = 1;
#if PRINT_CSEQ
                printf("\n%ld ", input_num);
#endif
                //-Loop to determine the length of Collatz sequence for a given number
                while (input_num > 1)
                {
                    count++;
                    //-Enable Exit if next step in sequence is out of boundary of (unsigned long long) datatype
                    if (input_num > max_valueof_i && input_num & 1)
                    {
                        printf("\n\nStep in Collatz sequence of (%llu) is not supported. Exceeds 64bit width.\nExiting.\n", i);
                        ExitPath = YES;
                        break;
                    }
                    else
                    {
                        //-calculate next number in Collatz sequence
                        input_num = ((input_num & 1) == 0) ? input_num / 2 : input_num * 3 + 1;
#if PRINT_CSEQ
                        printf("%ld ", input_num);
#endif
                    }
                }//-End: while (input_num > 1)
                if (ExitPath)break; //-break loop if exit is enabled
                //-Preserve number and count for current number's sequence if its count is greater than existing value
                if (LongCSCount < count)
                {
                    LongCSCount = count;
                    LongCSNum = i;
                }
            }//-End: for (unsigned long long i = Upper_Limit; i >= 1; i--)
            if (!ExitPath)
            {
                //-Output number with longest chain
                printf("\nNumber with the longest chain below the upper limit (%llu) : %llu ", Upper_Limit, LongCSNum);
                printf("\nLength of the Collatz sequence : %llu", LongCSCount);
                end = clock();
                seconds = (double)(end - start) / CLOCKS_PER_SEC;
#if PRINT_EXE_TIME
                printf("\nProcessing time : %f s", seconds);//-Program execution time
#endif
            }
            else
            {
                // no action
            }
        }
        else
        {
            printf("\nInvalid \'upper limit\' provided.\n");
        }
    }
    else {
        printf("\nToo many arguments.\n");
    }
    //-Exit path
    return 0;
}
/************************ End of file **********************************/
