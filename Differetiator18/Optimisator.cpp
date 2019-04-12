#include "Differentiator.h"
#include <assert.h>

void Dif::Optimisation(Node * root)
{
    One_Nul_Opt(root);
    double a = 0;
    while(a != POISON)
    {
       a = OptConst(root);
    }
}



void Dif::One_Nul_Opt(Node * root)
{
    if(root->left && root->right)
    {
        One_Nul_Opt(root->left);
    }

    if(root->type == Func && root->value == Multy && root->left->type == Const && root->left->value == 1)
    {
        One_left_multy_tex(root);
        delete root->left;
        root->left = nullptr;
        Node* A = root->right;
        root->value = root->right->value;
        root->type = root->right->type;
        root->left = root->right->left;
        root->right = root->right->right;
        delete A;

    }

    if(root->type == Func && root->value == Multy && root->right->type == Const && root->right->value == 1)
    {
        One_right_multy_tex(root);
        delete root->right;
        root->right = nullptr;
        Node* A = root->left;
        root->value = root->left->value;
        root->type = root->left->type;
        root->right = root->left->right;
        root->left = root->left->left;
        delete A;

    }
    if(root->type == Func && root->value == Minus && root->right->type == Const && root->right->value == 0)
    {
        Null_right_minus_tex(root);
        delete root->right;
        root->right = nullptr;
        Node* A = root->left;
        root->value = root->left->value;
        root->type = root->left->type;
        root->right = root->left->right;
        root->left = root->left->left;
        delete A;

    }
    if(root->type == Func && root->value == Plus && root->right->type == Const && root->right->value == 0)
    {
        Null_right_plus_tex(root);
        delete root->right;
        root->right = nullptr;
        Node* A = root->left;
        root->value = root->left->value;
        root->type = root->left->type;
        root->right = root->left->right;
        root->left = root->left->left;
        delete A;

    }
    if(root->type == Func && root->value == Plus && root->left->type == Const && root->left->value == 0)
    {
        Null_left_plus_tex(root);
        delete root->left;
        root->left = nullptr;
        Node* A = root->right;
        root->value = root->right->value;
        root->type = root->right->type;
        root->left = root->right->left;
        root->right = root->right->right;
        delete A;

    }
    if(root->type == Func && root->value == Multy && root->left->type == Const && root->left->value == 0)
    {
        Null_left_multy_tex(root);
        delete root->left;
        root->right = nullptr;
        delete root->right;
        root->left = nullptr;
        root->type = Const;
        root->value = 0;

    }
    if(root->type == Func && root->value == Multy && root->right->type == Const && root->right->value == 0)
    {
        Null_right_multy_tex(root);
        delete root->left;
        root->left = nullptr;
        delete root->right;
        root->right = nullptr;
        root->type = Const;
        root->value = 0;

    }

    if(root->left && root->right)
    {
        One_Nul_Opt(root->right);
    }
}

double Dif::OptConst(Node *root)
{
    assert(root);
    switch((int)root->type)
    {
        case Func:
            switch((int)root->value)
            {
                case Plus:
                {
                    double l_1 = this->OptConst(root->left);
                    double r_1 = this->OptConst(root->right);
                    if(l_1 != POISON && r_1 != POISON)
                    {
                        root->left->value = l_1;
                        root->right->value = r_1;
                        Plus_opt_tex(root);
                        double sum = l_1 + r_1;
                        delete root;
                        root = nullptr;
                        return sum;
                    }
                    if(r_1 == POISON && l_1 == POISON)
                    {
                        return POISON;
                    }
                    if(r_1 == POISON && l_1 != POISON)
                    {
                        root->left = new Node(Const, l_1);
                        root->left->parent = root;
                        return POISON;
                    }
                    if(r_1 != POISON && l_1 == POISON)
                    {
                        root->right = new Node(Const, r_1);
                        root->right->parent = root;
                        return POISON;
                    }
                }
                case Minus:
                {
                    double l_2 = this->OptConst(root->left);
                    double r_2 = this->OptConst(root->right);
                    if(l_2 != POISON && r_2 != POISON)
                    {
                        root->left->value = l_2;
                        root->right->value = r_2;
                        Minus_opt_tex(root);
                        double sum = l_2 - r_2;
                        delete root;
                        root = nullptr;
                        return sum;
                    }
                    if(r_2 == POISON && l_2 == POISON)
                    {
                        return POISON;
                    }
                    if(r_2 == POISON && l_2 != POISON)
                    {
                        root->left = new Node(Const, l_2);
                        root->left->parent = root;
                        return POISON;
                    }
                    if(r_2 != POISON && l_2 == POISON)
                    {
                        root->right = new Node(Const, r_2);
                        root->right->parent = root;
                        return POISON;
                    }
                }
                case Multy:
                {
                    double l_3 = this->OptConst(root->left);
                    double r_3 = this->OptConst(root->right);
                    if(l_3 != POISON && r_3 != POISON)
                    {
                        root->left->value = l_3;
                        root->right->value = r_3;
                        Multy_opt_tex(root);
                        double sum = l_3 * r_3;
                        delete root;
                        root = nullptr;
                        //printf("root = %p", root);
                        return sum;
                    }
                    if(r_3 == POISON && l_3 == POISON)
                    {
                        return POISON;
                    }
                    if(r_3 == POISON && l_3 != POISON)
                    {
                        root->left = new Node(Const, l_3);
                        root->left->parent = root;
                        return POISON;
                    }
                    if(r_3 != POISON && l_3 == POISON)
                    {
                        root->right = new Node(Const, r_3);
                        root->right->parent = root;
                        return POISON;
                    }
                }
                case Divide:
                {
                    double l_4 = this->OptConst(root->left);
                    double r_4 = this->OptConst(root->right);
                    if(l_4 != POISON && r_4 != POISON)
                    {
                        root->left->value = l_4;
                        root->right->value = r_4;
                        Divide_opt_tex(root);
                        double sum = l_4 / r_4;
                        delete root;
                        root = nullptr;
                        return sum;
                    }
                    if(r_4 == POISON && l_4 == POISON)
                    {
                        return POISON;
                    }
                    if(r_4 == POISON && l_4 != POISON)
                    {
                        root->left = new Node(Const, l_4);
                        root->left->parent = root;
                        return POISON;
                    }
                    if(r_4 != POISON && l_4 == POISON)
                    {
                        root->right = new Node(Const, r_4);
                        root->right->parent = root;
                        return POISON;
                    }
                }
                case Sin:
                {
                    double r_5 = this->OptConst(root->right);
                    if(r_5 != POISON)
                    {
                        //printf("Sin!!!!!!!11");
                        root->right = new Node(Const, r_5);
                        return POISON;
                    }
                    else
                    {
                        return POISON;
                    }
                }
                case Cos:
                {
                    double r_6 = this->OptConst(root->right);
                    if(r_6 != POISON)
                    {
                        //printf("Sin!!!!!!!11");
                        root->right = new Node(Const, r_6);
                        return POISON;
                    }
                    else
                    {
                        return POISON;
                    }
                }
                case Tan:
                {
                    double r_7 = this->OptConst(root->right);
                    if(r_7 != POISON)
                    {
                        //printf("Sin!!!!!!!11");
                        root->right = new Node(Const, r_7);
                        return POISON;
                    }
                    else
                    {
                        return POISON;
                    }
                }
                case Cotan:
                {
                    double r_8 = this->OptConst(root->right);
                    if(r_8 != POISON)
                    {
                        //printf("Sin!!!!!!!11");
                        root->right = new Node(Const, r_8);
                        return POISON;
                    }
                    else
                    {
                        return POISON;
                    }
                }
                case Exp:
                {
                    double r_9 = this->OptConst(root->right);
                    if (r_9 != POISON)
                    {
                        //printf("Sin!!!!!!!11");
                        root->right = new Node(Const, r_9);
                        return POISON;
                    }
                    else
                    {
                        return POISON;
                    }
                }
                case Sqrt:
                {
                    double r_10 = this->OptConst(root->right);
                    if(r_10 != POISON)
                    {
                        //printf("Sin!!!!!!!11");
                        root->right = new Node(Const, r_10);
                        return POISON;
                    }
                    else
                    {
                        return POISON;
                    }
                }
                case Log:
                {
                    double r_11 = this->OptConst(root->right);
                    if(r_11 != POISON)
                    {
                        root->right = new Node(Const, r_11);
                        return POISON;
                    }
                    else
                    {
                        return POISON;
                    }
                }
                default:
                    break;
            }
            break;
        case Var:
            switch((int)root->value)
            {
                case Var_x:
                    return POISON;
                case Var_y:
                    return POISON;
                default:
                    break;
            }
            break;
        case Const:
        {
            double x = root->value;
            delete root;
            root = nullptr;
            return x;
        }
        default:
            break;
    }
    return POISON;
}


