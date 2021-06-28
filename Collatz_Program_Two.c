/************************************************************/
/*Author: Vijay Seshu R                                     */
/*Date: 25-05-2021                                          */
/*Version: 1.0                                              */
/*Change log:                                               */
/************************************************************/

/*************** Header files ****************************/
#include<stdio.h>
#include<time.h>
#include<stdlib.h>

/***************** Macros ****************************/
#define YES (1)
#define NO (0)
#define PRINT_EXE_TIME (1)
#define PRINT_CSEQ (0)

/*************** Structure definitions **********************/
//-Structure to store results in double linked list
typedef struct _DLL_a3ul
{
    struct _DLL_a3ul *Prev;
    unsigned long long Data[3];
    struct _DLL_a3ul *Next;
}DLL_A3UL;
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
    while (pow--)res = res * num;
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
        if(str[i-1] >= 48 && str[i-1] <=57)
            res += (str[i-- - 1] - 48) * PowerOf(10, j++);
        else i--;
    }
    return res;
}
/******************* AddNodeDesc ****************************/
/*Function: AddNodeDesc                                     */
/*Description: Creates and updates double linked list in    */
/*             descending order                             */
/*Input: FirstNode - pointer, node's Data                   */
/*Return type: Pointer to first node                        */
/************************************************************/
DLL_A3UL* AddNodeDesc(DLL_A3UL *FirstNode, unsigned long long Data[3])
{
    DLL_A3UL *Temp = NULL, *Temp1 = NULL;
    Temp = (DLL_A3UL*)malloc(sizeof(DLL_A3UL));
    Temp->Prev = Temp->Next = NULL;
    for(short i = 0; i < 3; i++)
    {
        Temp->Data[i] = Data[i];
    }
    //-First node created if list does not exists
    if(FirstNode == NULL)
    {
        FirstNode = Temp;
    }
    //-Check for the position, where the new data can be stored
    //-List is managed in descending order
    else if(FirstNode->Data[0] > Data[0])
    {
        Temp1 = FirstNode;
        //-Traverse through the list to the required position
        while(Temp1->Next != NULL)
        {
            if(Temp1->Data[0] > Data[0])
            {
                Temp1 = Temp1->Next; //-Sorting
            }
            else
            {
                break;
            }
        }
        //-Insert new data at an intermediate position in the list
        if(Temp1->Next != NULL)
        {
            Temp->Next = Temp1;
            Temp->Prev = Temp1->Prev;
            Temp1->Prev->Next = Temp;
            Temp1->Prev = Temp;
        }
        //-Insert new data at end of list
        else
        {
            Temp->Prev = Temp1;
            Temp1->Next = Temp;
        }
    }
    //-New data is greater than first node data
    //-Assign new node as first node
    else if(FirstNode->Data[0] < Data[0])
    {
        Temp1 = FirstNode;
        FirstNode = Temp;
        FirstNode->Next = Temp1;
        Temp1->Prev = FirstNode;
    }
    //-Returns the First node address
    return FirstNode;
}
/******************* GetDataFromNode *************************/
/*Function: GetDataFromNode                                  */
/*Description: retrieve data from specified node             */
/*Input: FirstNode pointer, Index - position of required node*/
/*       Data pointer in which results are updated           */
/*Return type: short - function result                       */
/*************************************************************/
short GetDataFromNode(DLL_A3UL *Nodee, unsigned long long index, unsigned long long *Data)
{
    DLL_A3UL *Node = Nodee;
    if(Node == NULL)return 1;
    //-Traverse to the node with index
    while(index && Node)
    {
        index--;
        Node = Node->Next;
    }
    if(Node)
    {
        for(short i = 0; i < 3; i++)
        {
            Data[i] = Node->Data[i]; //-Index's node data fetch
        }
    }
    return 0;
}
/******************* GetDLLLength ***************************/
/*Function: GetDLLLength                                    */
/*Description: count number of nodes in created list        */
/*Input: FirstNode pointer, pointer to update length        */
/*Return type: pointer to last node in the list             */
/************************************************************/
DLL_A3UL * GetDLLLength(DLL_A3UL *Nodee, unsigned long long *Length)
{
    DLL_A3UL *Node = Nodee;
    if(Node == NULL)return NULL;
    *Length = 1;
    //-Traverse through the list
    while(Node->Next)
    {
        *Length += 1;
        Node = Node->Next; //-Node contains last node address
    }
    //-Return address of last node
    return Node;
}
/******************* DeleteDLL ******************************/
/*Function: DeleteDLL                                       */
/*Description: delete nodes from created list               */
/*Input: FirstNode pointer                                  */
/*Return type: void                                         */
/************************************************************/
void DeleteDLL(DLL_A3UL *Nodee)
{
    DLL_A3UL *Node = Nodee, *Temp = NULL;
    while(Node)
    {
        Temp = Node->Next;
        free(Node); //-Created node freed
        Node = Temp;
    }
}
/*************** Collatz Main *******************************/
/*Function: main                                            */
/*Description: Main function to find the starting number    */
/*below a given limit that has the longest Collatz sequence.*/
/*Input: Upper-limit given in argv[1]                       */
/*Output: Number with longest collatz sequence              */
/*        Length of the sequence                            */
/*Return type: int                                          */
/************************************************************/
int main(int argc, char* argv[]) {
    //-Local variables
    unsigned long long input_num = 0, LongCSNum = 0, LongCSCount = 0, Upper_Limit = 0, count = 0;
    char ExitPath = NO; //-if ExitPath is enabled, no further functional execution will happen
    clock_t start, end;
    double seconds = 0;
    DLL_A3UL *FirstNode = NULL;
    unsigned long long Data[] = {0, 0, 0};

    //-arguments check
    if (argc == 1)
    {
        printf("\n\'Upper limit\' argument not provided.\n");
    }
    else if (argc == 2)
    {
        char* input_str = argv[1];
        int i = 0;
        unsigned long long ActUpLimit = 0, ActLowLimit = 0;
        unsigned long long CurrRange = 0, CurrNum = 0, CurrCount = 0;
		char RangeMatched = NO;
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
            FILE* CollatzDF = NULL;
            static char StrFrmFile[1000];
            unsigned long long RangeFromFile = 0;
            const char *FileName = "HeuristicCollatzData.txt"; //File in which ranges are stored

            //-Valid argument received
            start = clock();
            Upper_Limit = (unsigned long long) StrToi64(input_str); //-Convert string input to an integer
            printf("\nRunning Program Two (CPU time reduction) for upper limit: %llu", Upper_Limit);
            CollatzDF = fopen(FileName, "r");
            if (CollatzDF != NULL)
            {
                //-End of file check
                if (!feof(CollatzDF))
                {
                    //-Read string from file, maximum size is 999
                    if(fgets(StrFrmFile, 999, CollatzDF))
                    {
                        //-Detect the max range stored in file (ex: Range: 1000 for 1000 max range)
                        if(StrFrmFile[0] == 'R')
                        {
                            RangeFromFile = (unsigned long long)StrToi64(&StrFrmFile[7]);
                            printf("\nLearnt range: %llu", RangeFromFile);
                        }
                    }
                }//-End: if (!feof(CollatzDF))
                //-Calculate upper and lower limits based on range learnt from file
                if(RangeFromFile > Upper_Limit)
                {
                    ActUpLimit = Upper_Limit;
                    ActLowLimit = Upper_Limit - Upper_Limit % 100 + 1;
                }
                else if(RangeFromFile < Upper_Limit)
                {
                    ActUpLimit = Upper_Limit;
                    ActLowLimit = RangeFromFile + 1;
                }
                else
                {
                    ActUpLimit = Upper_Limit;
                    ActLowLimit = RangeFromFile - 1;
                }
                //Extract the Number & count for a given range from file
                while(fscanf(CollatzDF,"%llu%llu%llu", &CurrRange, &CurrNum, &CurrCount) != EOF)
                {
                    if(CurrRange == ActLowLimit - 1)
                    {
                        LongCSNum = CurrNum;
                        LongCSCount = CurrCount;
                        RangeMatched = YES;
                        break;
                    }
					if(CurrRange > Upper_Limit)break;
                }
                //-Use default values if Range is not matched
                if(!RangeMatched)
                {
                    ActLowLimit = 2;
                    LongCSCount = 0;
                    LongCSNum = 0;
                }
                fclose(CollatzDF);
            }//-End: if (CollatzDF != NULL)
            else
            {
                //-calculation if no file found
                ActUpLimit = Upper_Limit;
                ActLowLimit = 2;
            }
            //- Loop that finds the starting number below a given limit that has the longest Collatz sequence
            for (unsigned long long i = ActLowLimit; i <= ActUpLimit - 1; i++)
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
                //-multiples of 100 related data stored in list, these are the ranges stored into file
                if(i % 100 == 0)
                {
                    Data[0] = i;
                    Data[1] = LongCSNum;
                    Data[2] = LongCSCount;
                    //-Maintain the range data in list
                    FirstNode = AddNodeDesc(FirstNode, Data);
                }
            }//-End: for (unsigned long i = Upper_Limit; i >= 1; i--)
            //-Output number with longest chain
            if (!ExitPath)
            {
                unsigned long long TempData[] = {0, 0, 0};
                CollatzDF = fopen(FileName, "r+");
                //-Update the file if new highest Range is available
                if(!GetDataFromNode(FirstNode, 0, TempData) && !fseek(CollatzDF,0,SEEK_SET))
                {
                    fprintf(CollatzDF,"Range: %010llu", TempData[0]);
                }
                //-Update newly learnt values into the file
                if(!fseek(CollatzDF,0,SEEK_END))
                {
                    DLL_A3UL *LastNode = NULL, *Tempr = NULL;
                    unsigned long long DLLLength = 0;
                    LastNode = GetDLLLength(FirstNode, &DLLLength);
                    //-Fetch data from list and write to file
                    while(LastNode)
                    {
                        fprintf(CollatzDF, "\n%llu %llu %llu", LastNode->Data[0], LastNode->Data[1], LastNode->Data[2]);
                        LastNode = LastNode->Prev;
                    }
                }
                fclose(CollatzDF);
                //-Calculated values compared to values from file
                if(CurrCount > LongCSCount && RangeMatched)
                {
                    LongCSNum = CurrNum;
                    LongCSCount = CurrCount;
                }
                //-Output number with longest chain
                printf("\nNumber with the longest chain below the upper limit (%llu) is : %llu ", Upper_Limit, LongCSNum);
                printf("\nLength of the Collatz sequence : %llu", LongCSCount);
                end = clock();
                seconds = (double)(end - start) / CLOCKS_PER_SEC;
#if PRINT_EXE_TIME
                printf("\nProcessing time : %f s", seconds);//-execution time check
#endif
            }
            else
            {
                // no action
            }
        }//-End: if (!ExitPath)
        else
        {
            printf("\nInvalid \'upper limit\' provided.\n");
        }
        DeleteDLL(FirstNode);
    }
    else
    {
        printf("\nToo many arguments.\n");
    }
    //-Exit path
    return 0;
}
/************************ End of file **********************************/
