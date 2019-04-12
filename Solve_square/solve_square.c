#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <assert.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>

//----------------------------------------------------------------------------------------------------------------------
//------------------------------------------------DEFINES---------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

#define INFINIT -100
#define ifnull(what) fabs(what - 0) < DBL_EPSILON
#define ifnotnull(what) fabs(what - 0) > DBL_EPSILON


const int POISON        = NAN; //Nan

///Error codes
enum Errors {
    FILE_ERR        = -10,  /// if file was not opened
    ROOT_NUM        = -1,   /// if unit test shows that root_num is different
    ROOT_SINGLE     = -2,   /// if in the case of single root unit test shows error
    ROOT1           = -3,   /// if answer of root1 is not equal to unit answer
    ROOT2           = -4,   /// if answer of root1 is not equal to unit answer
    PTR_ROOT1       = -5,
    PTR_ROOT2       = -6,
    EQUAL_PTRS      = -7,
    A_INF           = -8,
    B_INF           = -9,
    C_INF           = -11

};

//----------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------FUNCTIONS-----------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------


int Unit_test       ();
int Solve_square(double a, double b, double c, double* root1, double* root2);
int Lineal_sol      (double b, double c, double* root1);
void Print_reply    (int root_num, double root1, double root2);

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

void TestOK(int err)
{
    switch(err)
    {
        case FILE_ERR :
            printf("\tFile was not opened\n\n");
            exit(1);//адекватно
            break;
        case ROOT_NUM :
            printf("Root_num is not equal\n\n");
            exit(2);//адекватно
            break;
        case ROOT_SINGLE :
            printf("Single Root1 is not equal to unit_root1\n\n");
            exit(3);//адекватно
            break;
        case ROOT1 :
            printf("Root1 is not equal to unit_root1\n\n");
            exit(4);//адекватно
            break;
        case ROOT2 :
            printf("Root2 is not equal to unit_root2\n\n");
            exit(5);//адекватно
            break;
        case PTR_ROOT1 :
            printf("Pointer on Root1 is NULL\n\n");
            exit(6);//адекватно
            break;
        case PTR_ROOT2 :
            printf("Pointer on Root2 is NULL\n\n");
            exit();//адекватно
            break;

        default :
            break;
    }

}

//----------------------------------------------------------------------------------------------------
//----------------------------------------------MAIN--------------------------------------------------
//----------------------------------------------------------------------------------------------------

/**
 * @brief main function
 * @version 2.0
 * @param no
 *
 * In the beginning of function user should call the function Unit_test(). If there's no mistakes, user should print
 * three coefficients for the quadratic equation (call function Quadr_equation and call Print_reply if user wants.
 */

int main(int argc, char** argv)
{
    if(strcmp(argv[1],"-u") == 0)
    {
        TestOK(Unit_test());
    }

    double a, b, c;
    a = b = c = POISON;
    double root1, root2;
    root1 = root2 = POISON;//Nan
    int root_num = 0;

    printf("\t\t\t\tHello!\n\t\t Please, print three coefficients for the quadratic equation :) ");

    while(scanf("%lg%lg%lg", &a, &b, &c) != 3)
    {
        while(getchar() != '\n');
        printf("\t\tTry again, print three coefficients for the quadratic equation :)");
    }


//----------------------------------------------------------------------------------------------------------------------
    root_num = Solve_square(a, b, c, &root1, &root2);
//----------------------------------------------------------------------------------------------------------------------

    TestOK(root_num);
    Print_reply(root_num, root1, root2);

    return 0;
}

//----------------------------------------------------------------------------------------------------------------------
//--------------------------------------------QUADRATIC_EAQUATION-------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

/**
    * @brief the function for solving quadratic equation
    * @version 2.0
    * @param double a
    * @param double bm
    * @param double c
    * @param double* root1
    * @param double* root2
    * @return int root_num
    * @code
    *   int root_num
        root_num = Quadr_equation(a, b, c, &root1, &root2);
    * @endcode

    * This function is cheking different kinds of quadratic equation
*/

int Solve_square(double a, double b, double c, double* root1, double* root2)
{
    if(root1 == NULL)
    {
        return PTR_ROOT1;
    }
    if(root2 == NULL)
    {
        return PTR_ROOT2;
    }
    if(root1 == root2)
    {
        return EQUAL_PTRS;
    }
    if(isinf(b) != 0)
    {
        return B_INF;
    }
    if(isinf(a) != 0)
    {
        return A_INF;
    }
    if(isinf(c) != 0)
    {
        return C_INF;
    }
    assert(root1);
    assert(root2);
    assert(root1 != root2);
    assert(!isinf(a));
    assert(!isinf(b));
    assert(!isinf(c));

    int root_num = -1; // poison
    if(ifnull(a))
    {
        if(ifnull(b) && ifnull(c))
        {
            root_num = INFINIT;
        }
        else if(ifnotnull(c) && ifnull(b))
        {
            root_num = 0;
        }
        else
        {
            root_num =  Lineal_sol(b, c, root1);
        }
    }
    else
    {
        double discr = b * b - 4 * a * c;
        double discr2 = sqrt(discr);

        if(ifnull(discr))
        {
            *root1 = -b / 2 / a;
            root_num = 1;
        }
        else if(discr < 0)
        {
                root_num = 0;
        }
        else
        {
                *root1 = (-b + discr2)/ 2 / a;
                *root2 = (-b - discr2)/ 2 / a;
                root_num = 2;
        }
    }
    return root_num;
}

//----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------LINEAL_SOL-------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

/**
    * @brief the function for solving leneal equation
    * @version 2.0
    * @param double b
    * @param double c
    * @param double* root1
    * @return number root_num
    *
    * @code
    *   int root_num
        root_num =  Lineal_sol(b, c, root1);
    * @endcode

    * This function is solving leneal equation and initialising root1 as the answer
*/

int Lineal_sol(double b, double c, double* root1)
{
    if(root1 == NULL)
    {
        return PTR_ROOT1;
    }
    if(isinf(b) != 0)
    {
        return B_INF;
    }
    if(isinf(c) != 0)
    {
        return C_INF;
    }
    assert(root1);
    assert(!isinf(b));
    assert(!isinf(c));
    *root1 = (-1) * c / b;
    return 1;
}



//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------PRINT_REPLY-------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

/**
  * @brief the function for printing answers
  * @version 2.0
  * @param double root1
  * @param double root2
  * @param int root_num
  * @return void
  * @code
       Print_reply(root_num, root1, root2);
  * @endcode


* This function is checking the root_num for switch and printing answers
*/

void Print_reply(int root_num, double root1, double root2)
{

    printf("\n\n\t\troot_num = %d\n", root_num);
    switch(root_num)
    {
        case 0 :
            printf("\tThere is no roots!\n");
            //printf("\t root1 = %lg\troot2 = %lg\n", root1, root2);
            printf("\n");
            break;
        case 1 :
            printf("\tOnly one root:\troot1 = %lg\n", root1);
            //printf("\t root1 = %lg\troot2 = %lg\n", root1, root2);
            printf("\n");
            break;
        case 2 :
            printf("\t root1 = %lg\troot2 = %lg\n", root1, root2);
            printf("\n");
            break;
        case INFINIT :
            printf("\tAll values are suitable!\n");
            //printf("\t root1 = %lg\troot2 = %lg\n", root1, root2);
            printf("\n");
            break;
        default :
            printf("\tDefault! Something is wrong!\n");
    }
}

//----------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------UNIT_TEST----------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

/**
  * @brief the function is checking the function of Quadr_equation
  * @version 2.0
  * @return int err

  * @code
        int err = Unit_test();
        TestOK(err);
  * @endcode

  * This function is checking the function of Quadr_equation in the following way: fscanf true unit_tests with true
  * answers, call Quadr_equation() and compare the results with the answers from FILE* fin. If something is wrong, it
  * returns the code of error.
*/

int Unit_test()
{
    int err = 1;
    FILE *fin = fopen("Unit_test.txt", "rb");
    if(fin == NULL)
    {
        printf("File was not open!\n");
        return FILE_ERR;
    }

    int num_sol = 0;
    int i = 0;
    int count = 6;
    fscanf(fin, "%i", &num_sol);
    double* buff = (double*) calloc((size_t)count * num_sol, sizeof(double));
    for(i = 0; i < count * num_sol; i++)
    {
        if(fscanf(fin, "%lg", &buff[i]) != 1)
        {
            printf("\tscanf shows: Something is wrong!\n");
        }
    }
    for(i = 0; i < count * num_sol; i++)
    {
        //printf("buff[%i] = %lg  ", i, buff[i]); //sscanf

    }

    double unit_a, unit_b, unit_c;

    double unit_root1, unit_root2;

    double  unit_root_num = 0;

    double root1, root2;
    root1 = root2 = POISON;
    int root_num = POISON;

    for(i = 0; i < num_sol; i++)
    {
        unit_a = buff[i * count];
        unit_b = buff[i* count + 1];
        unit_c = buff[i* count + 2];
        unit_root_num = buff[i* count + 3];
        unit_root1 = buff[i* count + 4];
        unit_root2 = buff[i* count + 5];

        root_num = Solve_square(unit_a, unit_b, unit_c, &root1, &root2);
        //Print_reply(root_num, root1, root2);


        if(root_num != unit_root_num)
        {
            err = ROOT_NUM;
        }

        switch(root_num)
        {
            case 0 :
                break;
            case 1 :
                if(root1 != unit_root1)
                {
                    err = ROOT_SINGLE;
                }
                break;
            case 2 :
                if(root1 != unit_root1)
                {
                    printf("root1 = %lg, unit_root1 = %lg, root1 is not equal to unit_root1\n\n", root1, unit_root1);
                    err = ROOT1;
                }
                if(root2 != unit_root2)
                {
                    printf("root2 = %lg, unit_root2 = %lg, root2 is not equal to unit_root2\n\n", root2, unit_root2);
                    err = ROOT2;
                }
                break;
            case INFINIT :
                break;
            default :
                printf("\tDefault! Something is wrong!\n");
        }
    }
    return err;

}