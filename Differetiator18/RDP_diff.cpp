#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "RDP_diff.h"

Rdp::Rdp():
    position(0)
{
    formula_str = (char*)malloc(LENGTH_OF_FORMULA * sizeof(char));
    printf("Rdp() constructor!\n");
}

Rdp::~Rdp()
{
    delete formula_str;
    formula_str = nullptr;
    position = (int)POISON;
    printf("~Rdp() DEstructor!\n");
}

Tree* Rdp::GetTree(const char* string_)
{
    strcpy(formula_str, string_);
    position = 0;

    Tree* tree = new Tree();
    tree->root = GetE(tree);
    if(tree->root == nullptr)
    {
        printf("The func GetTree get a nullptr!\n");
        return nullptr;
    }

    if( formula_str[position] != '\0')
    {
        printf("Error in the func GetTree()\n");
        return nullptr;
    }
    position++;
    return tree;
}



Node* Rdp::GetE(Tree* tree)
{

    Node* val = GetT(tree);
    if(val == nullptr)
    {
        printf("The func GetE get a nullptr!\n");
        return nullptr;
    }

    while(formula_str[position] == '+' || formula_str[position] == '-')
    {
        int op = formula_str[position];
        position++;
        Node* val2 = GetT(tree);
        if(val2 == nullptr)
        {
            printf("The func GetE get a nullptr!\n");
            return nullptr;
        }
        if( op == '+')
        {
            Node* newtree = tree->Create_node(Func, Plus);
            newtree->left = val;
            val->parent = newtree;
            newtree->right = val2;
            val2->parent = newtree;

            val = newtree;
        }
        else if( op == '-')
        {
            Node* newtree = tree->Create_node(Func, Minus);
            newtree->left = val;
            val->parent = newtree;
            newtree->right = val2;
            val2->parent = newtree;

            val = newtree;
        }
    }
    return val;
}

Node* Rdp::GetT(Tree* tree)
{

    Node* val = GetP(tree);
    if(val == nullptr)
    {
        printf("The func GetT get a nullptr!\n");
        return nullptr;
    }

    while(formula_str[position] == '*' || formula_str[position] == '/')
    {
        int op = formula_str[position];
        position++;
        Node* val2 = GetP(tree);
        if(val2 == nullptr)
        {
            printf("The func GetT get a nullptr!\n");
            return nullptr;
        }
        if( op == '*')
        {
            Node* newtree = tree->Create_node(Func, Multy);
            newtree->left = val;
            val->parent = newtree;
            newtree->right = val2;
            val2->parent = newtree;

            val = newtree;
        }
        else if( op == '/')
        {
            Node* newtree = tree->Create_node(Func, Divide);
            newtree->left = val;
            val->parent = newtree;
            newtree->right = val2;
            val2->parent = newtree;

            val = newtree;
        }
    }
    return val;
}

Node* Rdp::GetP(Tree* tree)
{

    if(formula_str[position] == '(')
    {
        position++;
        Node* val = GetE(tree);
        if(val == nullptr)
        {
            printf("The func GetP get a nullptr!\n");
            return nullptr;
        }
        if( formula_str[position] != ')')
        {
             printf("Error in the func GetP()\n");
            return nullptr;
        }
        position++;
        return val;
    }
    else if(formula_str[position] == 's' && formula_str[position + 1] == 'i' )
    {
        if(formula_str[position + 2] == 'n')
        {
            position += 3;
            return Get_sin(tree);
        }
    }
    else if( formula_str[position] == 'c' && formula_str[position + 1] == 'o' )
    {
        if(formula_str[position + 2] == 's')
        {
            position += 3;
            return Get_cos(tree);
        }
    }
    else if( formula_str[position] == 't')
    {
        if(formula_str[position + 1] == 'g')
        {
            position += 2;
            return Get_tg(tree);
        }
    }
    else if( formula_str[position] == 'c' && formula_str[position + 1] == 't')
    {
        if(formula_str[position + 2] == 'g')
        {
            position += 3;
            return Get_ctg(tree);
        }
    }
    else if( formula_str[position] == 'x')
    {
        return Get_x(tree);
    }
    else if( formula_str[position] == 'y')
    {
        return Get_y(tree);
    }
    else if( formula_str[position] == 'l' && formula_str[position + 1] == 'n')
    {
        position +=2;
        return Get_ln(tree);
    }
    else if( formula_str[position] == 'e' && formula_str[position + 1] == 'x')
    {
        if(formula_str[position + 2] == 'p')
        {
            position += 3;
            return Get_exp(tree);
        }
    }
    else if( formula_str[position] == 's' && formula_str[position + 1] == 'q')
    {
        if(formula_str[position + 2] == 'r' && formula_str[position + 3] == 't')
        {
            position += 4;
            return Get_sqrt(tree);
        }
    }
    else if(formula_str[position] >= '0' && formula_str[position] <= '9')
    {
        return GetN(tree);
    }
    printf("Error in the func Get_P()\n");
    return nullptr;
}

Node* Rdp::GetN(Tree* tree)
{
    int val = 0;
    do
    {
        val = val * 10 + formula_str[position] - '0';
        position++;
    } while ( formula_str[position] >= '0' && formula_str[position] <= '9');

    Node* newtree = tree->Create_node(Const, val);
    return newtree;
}


Node* Rdp::Get_x(Tree* tree)
{
        position++;
        Node* val = tree->Create_node(Var, Var_x);
        return val;
}

Node* Rdp::Get_y(Tree* tree)
{
        position++;
        Node* val = tree->Create_node(Var, Var_y);
        return val;
}

Node* Rdp::Get_exp(Tree* tree)
{
    if( formula_str[position] == '(')
    {
        position++;
        Node* val = GetE(tree);
        if(val == nullptr)
        {
            printf("The func Get_exp get a nullptr!\n");
            return nullptr;
        }
        if( formula_str[position] != ')')
        {
            printf("Error in the func Get_exp()\n");
            return nullptr;
        }
        position++;
        Node* newtree = tree->Create_node(Func, Exp);
        newtree->right = val;
        val->parent = newtree;
        val = newtree;
        return val;
    }
    else
    {
        printf("Error in the function Get_exp!\n");
    }
    return nullptr;
}

Node* Rdp::Get_ln(Tree* tree)
{
    if( formula_str[position] == '(')
    {
        position++;
        Node* val = GetE(tree);
        if(val == nullptr)
        {
            printf("The func Get_ln get a nullptr!\n");
            return nullptr;
        }

        if( formula_str[position] != ')')
        {
             printf("Error in the func Get_ln()\n");
            return nullptr;
        }
        position++;
        Node* newtree = tree->Create_node(Func, Log);
        newtree->right = val;
        val->parent = newtree;
        val = newtree;
        return val;
    }
    else
    {
        printf("Error in the function Get_ln!\n");
    }
    return nullptr;
}

Node* Rdp::Get_sqrt(Tree* tree)
{
    if( formula_str[position] == '(')
    {
        position++;
        Node* val = GetE(tree);
        if(val == nullptr)
        {
            printf("The func Get_sqrt get a nullptr!\n");
            return nullptr;
        }
        if( formula_str[position] != ')')
        {
             printf("Error in the func Get_sqrt()\n");
            return nullptr;
        }
        position++;
        Node* newtree = tree->Create_node(Func, Sqrt);
        newtree->right = val;
        val->parent = newtree;
        val = newtree;
        return val;
    }
    else
    {
        printf("Error in the function Get_sqrt!\n");
    }
    return nullptr;
}

Node* Rdp::Get_sin(Tree* tree)
{
    if( formula_str[position] == '(')
    {
        position++;
        Node* val = GetE(tree);
        if(val == nullptr)
        {
            printf("The func Get_sin get a nullptr!\n");
            return nullptr;
        }
        if( formula_str[position] != ')')
        {
             printf("Error in the func Get_sin()\n");
            return nullptr;
        }
        position++;
        Node* newtree = tree->Create_node(Func, Sin);
        newtree->right = val;
        val->parent = newtree;
        val = newtree;
        return val;
    }
    else
    {
        printf("Error in the function Get_sin!\n");
    }
    return nullptr;
}

Node* Rdp::Get_cos(Tree* tree)
{
    if( formula_str[position] == '(')
    {
        position++;
        Node* val = GetE(tree);
        if(val == nullptr)
        {
            printf("The func Get_cos get a nullptr!\n");
            return nullptr;
        }
        if( formula_str[position] != ')')
        {
             printf("Error in the func Get_cos()\n");
             return nullptr;

        }
        position++;
        Node* newtree = tree->Create_node(Func, Cos);
        newtree->right = val;
        val->parent = newtree;
        newtree->left = nullptr;
        val = newtree;
        return val;
    }
    else
    {
        printf("Error in the function Get_cos!\n");
    }
    return nullptr;
}

Node* Rdp::Get_tg(Tree* tree)
{
    if( formula_str[position] == '(')
    {
        position++;
        Node* val = GetE(tree);
        if(val == nullptr)
        {
            printf("The func Get_tg get a nullptr!\n");
            return nullptr;
        }
        if( formula_str[position] != ')')
        {
             printf("Error in the func Get_tg()\n");
            return nullptr;
        }
        position++;
        Node* newtree = tree->Create_node(Func, Tan);
        newtree->right = val;
        val->parent = newtree;
        val = newtree;
        return val;
    }
    else
    {
        printf("Error in the function Get_tg!\n");
    }
    return nullptr;
}

Node* Rdp::Get_ctg(Tree* tree)
{
    if( formula_str[position] == '(')
    {
        position++;
        Node* val = GetE(tree);
        if(val == nullptr)
        {
            printf("The func Get_ctg get a nullptr!\n");
            return nullptr;
        }
        if( formula_str[position] != ')')
        {
             printf("Error in the func Get_ctg()\n");
            return nullptr;
        }
        position++;
        Node* newtree = tree->Create_node(Func, Cotan);
        newtree->right = val;
        val->parent = newtree;
        val = newtree;
        return val;
    }
    else
    {
        printf("Error in the function Get_ctg!\n");
    }
    return nullptr;
}
