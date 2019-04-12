#include "onegin.h"
//----------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------TESTING-------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief function is cheking file fin
 * @version 2.0
 * @param fin

 * This function cheking if file was not opened
 */
int File_OK(FILE* fin)
{
    if (fin == NULL)
    {
        printf("File was not opened! fin == NULL \n");
        return FIN_ERR;
    }
    return OK;
}

//----------------------------------------------------------------------------------------------------
//----------------------------------------------TEST--------------------------------------------------
//----------------------------------------------------------------------------------------------------

/**
 * @brief function is cheking codes of errors
 * @version 2.0
 * @param int err
 * @return void
 *
 *  @code
    int err = Unit_test();
    TestOK(err);
 *  @endcode

 * This function is cheking codes of rules for printing results
 */

int Test_OK(int err)
{
    switch(err)
    {

        case FOUT_ERR  :
            printf("\tFile was not opened\n\n");
            break;
        case FIN_ERR  :
            printf("\tFile was not opened\n\n");
            break;
        case FILE_SIZE :
            printf("Root_num is not equal\n\n");
            break;
        case PTR_BAD  :
            printf("Single Root1 is not equal to unit_root1\n\n");
            break;
        case COUNT_LINE  :
            printf("Root2 is not equal to unit_root2\n\n");
            break;

        default :
            break;
    }
    return err;
}

//----------------------------------------------------------------------------------------------------------------------
//------------------------------------------------SIZEOF_FILE-----------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------



/**
 * @brief function is cheking size
 * @version 2.0
 * @param fin

 * This function cheking size of INPUT.txt file
 */

long Sizeof_file(FILE *fin)
{
    if(!fin)
    {
        return -1;
    }
    assert(fin);

    long current = ftell(fin);
    fseek(fin, 0, SEEK_END);
    long size = ftell(fin);
    fseek(fin, 0, (int) current);

    return size;
}


/*long Sizeof_file2(FILE *fin)
{
    assert(fin);

    struct stat buff;
    stat("test", &buff);

    return buff.st_size;
}*/

//----------------------------------------------------------------------------------------------------------------------
//------------------------------------------------COUNT_LINE------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------


/**
 * @brief function is cheking lines
 * @version 2.0
 * @param char* buff
 * @param long file_size
 * @return int count_line
 *
 *  @code
    int count_line = Count_line(buff, file_size);
    if(count_line <= 0)
    {
        exit(5);
    }
 *  @endcode

 * This function is cheking amount of lines  in INPUT.txt file
 */


int Count_line(char *buff, long file_size)
{
    if(!buff)
    {
        return -1;
    }
    assert(buff);

    int count_line = 0;

    for (int i = 0; i < file_size; i++)
    {
        if (buff[i] == '\n')
        {
            buff[i] = '\0';
            count_line++;
        }
    }

    //for(char* s = strchr(buff, '\n'); s; s = strchr(s + 1, '\n'))
    //{
    //    text[++i] = s + 1;
    //}

    buff[file_size] = '\0'; // last line without '\n'! After last line add one more '\0'
    if(file_size != 0)
    {
        count_line++;      // last line without '\n'
    }

    return count_line;
}

//----------------------------------------------------------------------------------------------------------------------
//------------------------------------------------MAKE_BUFFSTR----------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief function is making buffer of strings
 * @version 2.0
 * @param char* buff
 * @param long file_size
 * @paramint count_line
 * @param int* count_empty
 * @return Strings* strings
 * @code
        int count_empty = 0;
        Strings* strings = Make_buffstr(buff, count_line, file_size, &count_empty);
        assert(strings);
 * @endcode

 * This function is making an array of structures Strings from char* buff
 */


String_view* Make_buffstr(char* buff, int count_line, long file_size, int* count_empty)
{
    if(!count_empty)
    {
        return (String_view*) POISON_PTR;
    }
    assert(count_empty);
    if(!buff)
    {
        return (String_view*) POISON_PTR;
    }
    assert(buff);

    String_view* strings = (String_view*) calloc((size_t) count_line, sizeof(* strings));
    if(!strings)
    {
        return (String_view*) POISON_PTR;
    }
    assert(strings);

    char* ptrString = buff;                      // pointer that runs around the buff
    int i = 0;
    int cur_position = 0;

    for(int j = 0; j < file_size + 1; j++)           // +1 because the last one is an additional '\0'
    {
        if(buff[j] == '\0')
        {
            strings[i].length = j - cur_position;// count the length of the lines
            if(i == 0)
            {
                strings[i].length++;             // For the first iteration, when calculating a row, we increase the length
            }
            strings[i].string = ptrString;       // We throw a pointer to a line in the current location of the carriage on the buffer
            ptrString = &(buff[j]) + 1;          // move the carriage
            cur_position = j;
            if(strings[i].length == 1)
            {
                (*count_empty)++;                // if the line was empty (only '\0') DO NOT increase the row counter
            }
            else
            {
                i++;                             // increase i to go to the new element of the array of structures
            }
        }
    }
    return strings;
}

//----------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------PRINT_TEXT-----------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief Printing the array of structurs
 * @version 2.0
 * @param FILE* file
 * @param Strings* strings
 * @param int count_line
 * @return void
 *
 * This function is printing the array of stucturs Strings
 */
void Print_text(FILE* file, String_view* strings, int count_line)
{
    assert(count_line);
    assert(file);
    assert(strings);

    int i = 0;
    for(i = 0; i < count_line; i++)
    {
        fprintf(file, "%s\n", strings[i].string);
    }
}

//----------------------------------------------------------------------------------------------------------------------
//---------------------------------------------COMPARE_FUNC_FROM_BEGIN--------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/**
 * @brief Comparating elements
 * @version 2.0
 * @param const void* const_str1
 * @param const void* const_str1
 * @return strcmp(str1.string, str2.string);
 *
 * @code
        qsort(strings, (size_t) count_real_lines, sizeof(*strings), Comparator);
   @endcode
 *
 * This function is compatating elements of the array of stucturs Strings str.string
 */

int Comparator(const void* const_str1, const void* const_str2)
{
    if(!const_str1)
    {
        return POISON;
    }
    if(!const_str2)
    {
        return POISON;
    }
    assert(const_str1);
    assert(const_str2);
    int i = 0;
    int j = 0;
    String_view str1 = *(String_view *) const_str1;
    String_view str2 = *(String_view *) const_str2;

    while (isdigit(*(str1.string)) || isspace(*(str1.string))
           || ispunct(*(str1.string)))
    {
        i++;
    }
    while (isdigit(*(str2.string)) || isspace(*(str2.string))
           || ispunct(*(str2.string)))
    {
        j++;
    }
    while (str1.string[i] - str2.string[j] == 0)
    {
        i++;
        j++;
    }
    return strcmp(str1.string, str2.string);
}

//----------------------------------------------------------------------------------------------------------------------
//---------------------------------------------ONEGIN-----------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief Example of Onegin
 * @version 2.0
 * @param int sort_kind
 * @param FILE* fout
 * @param FILE* fin
 * @return void
 *
 *  @code
 *  FILE* fin = fopen("INPUT.txt", "r");
    FILE* fout1 = fopen("OUTPUT1", "w");
    File_OK(fin);

    Onegin(STRAIGHT, fout1, fin);

    @endcode
 *
 * This function can read file and then sorting them in the way user want: STRAIGHT, VICEVERSA, NONE
 **/

int Onegin(int sort_kind, FILE* fout, FILE* fin)
{
    if(fout == NULL)
    {
        return FOUT_ERR;
    }
    if(fin == NULL)
    {
        return FIN_ERR;
    }


    assert(fout);
    assert(fin);

    long file_size = Sizeof_file(fin);
    if(file_size == -1)
    {
        return FILE_SIZE ;
    }

    char* buff = (char*) calloc ((size_t)file_size + 1, sizeof(* buff));   // +1 for last '\0'
    if(buff == NULL)
    {
        return PTR_BAD ;
    }
    assert(buff);

    size_t result = fread(buff, sizeof(char), (size_t) file_size, fin);
    fseek(fin, 0, SEEK_SET);
    printf("result111 =%zu\n", result);
    if (result != file_size)
    {
        printf("result = %zu, file_size = %zu\n", result, file_size);
        return FREAD_ERR;
    }
    int count_line = Count_line(buff, file_size);
    if(count_line == -1)
    {
        return COUNT_LINE ;
    }

    int count_empty = 0;
    String_view* strings = Make_buffstr(buff, count_line, file_size, &count_empty);
    if(!strings)
    {
        return POISON_PTR;
    }
    assert(strings);
    if(strings == NULL)
    {
        return PTR_BAD;
    }

    int real_count_line = count_line - count_empty;


    char* buff_copy = (char*) calloc ((size_t)file_size + 1, sizeof(* buff_copy));
    if(!buff_copy)
    {
        return PTR_BAD;
    }
    assert(buff_copy);
    memcpy(buff_copy, (const char*) buff, ((size_t)file_size + 1) *  sizeof(* buff));
    String_view* strings_copy = Make_buffstr(buff_copy, count_line, file_size, &count_empty);
    if(!strings)
    {
        return POISON_PTR;
    }
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
    Sort_str(sort_kind, strings_copy, real_count_line);
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

    Print_text(fout, strings_copy, real_count_line);


    Free_mem(buff, buff_copy, strings_copy, strings);

    return OK;
}

void Free_mem(char* buff, char* buff_copy, String_view* strings_copy, String_view* strings)
{
    free(buff);
    buff = NULL;
    free(buff_copy);
    buff_copy = NULL;
    free(strings_copy);
    strings_copy = NULL;
    free(strings);
    strings = NULL;
}


//----------------------------------------------------------------------------------------------------------------------
//------------------------------------------------SORT_STR--------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief Sorting in different ways
 * @version 2.0
 * @param   int sort_kind
 * @param   Strings* strings
 * @param   int count_real_lines
 * @return  Strings* strings
 * @code
 *  Sort_str(sort_kind, strings_copy, real_count_line);
 * @endcode
 *
 * This function can sort struct Strings in the way user want: STRAIGHT, VICEVERSA, NONE
 **/

String_view*  Sort_str(int sort_kind, String_view* strings, int count_real_lines)
{
    assert(strings);

    switch(sort_kind)
    {
        case STRAIGHT :
        {
            qsort(strings, (size_t) count_real_lines, sizeof(*strings), Comparator);
            break;
        }
        case VICEVERSA :
        {
            qsort(strings, (size_t) count_real_lines, sizeof(*strings), Comparator);
            break;
        }
        case NONE :
        {
            break;
        }
        default:
            break;
    }
    return strings;
}

//----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------VISE_VERSA_STR---------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief Making strings.string vice_versa
 * @version 2.0
 * @param   Strings* strings
 * @param   int count_real_lines
 * @return  Strings* strings
 * @code
        strings = Vice_versa_str(strings, count_real_lines);
   @endcode
 *
 * This function can remake struct Strings in the other way (from end)
 **/

/*String_view* Vice_versa_str(String_view* strings, int count_real_lines)
{
    assert(strings);

    int j = 0;
    for(j = 0; j < count_real_lines; j++)
    {
        int i = 0;
        for(i = 0; i < (strings[j].length - 1)/2; i++)
        {
            char c = strings[j].string[i];
            strings[j].string[i] = strings[j].string[strings[j].length - 2 - i];
            strings[j].string[strings[j].length - 2 - i] = c;
        }

    }

    return strings;
}*/

//----------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------MAIN_FUNC-----------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief main function
 * @version 3.0
 *
 *
 *  Main function of our program: User is able to put a text in the file INPUT.txt, then call the
 *  function Onegin, after which he or she will have text, sorted in the following way: STRAIGHT,
 *  VICEVERSA, NONE.
 */


/*int main()
{
    printf("\t\tThe function \"Sort_str\" can sort strings.\n"
           "\tPlease put the text into the file \"INPUT.txt\".\n"
           "\tCheck the result in the file \"OUTPUT.txt\".\n"
           "\tPlease, enter any symbol to continue\".\n");
    //getchar();
    FILE* fin = fopen("INPUT.txt", "r");
    FILE* fout1 = fopen("OUTPUT1", "w");
    FILE* fout2 = fopen("OUTPUT2", "w");
    FILE* fout3 = fopen("OUTPUT3", "w");
    Test_OK(File_OK(fin));
    Test_OK(File_OK(fout1));
    Test_OK(File_OK(fout2));
    Test_OK(File_OK(fout3));


    if(Test_OK(Onegin(STRAIGHT, fout1, fin)) != OK)
        exit(1);
    if(Test_OK(Onegin(VICEVERSA, fout2, fin)) != OK)
        exit(2);
    if(Test_OK(Onegin(NONE, fout3, fin)) != OK)
        exit(1);
    fclose(fin);
    fclose(fout1);
    fclose(fout2);
    fclose(fout3);

    return 0;
}*/
