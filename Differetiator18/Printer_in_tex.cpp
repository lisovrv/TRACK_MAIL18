#include "Differentiator.h"
#include "assert.h"
#include <unistd.h>


void Dif::PrintTEX(Node * tree)
{
    assert(tree);
    FILE * fin = fopen("Document777.tex", "w+");

    fprintf(fin,"\\documentclass[a4paper,12pt]{article}\n\\"
                "usepackage{graphicx}\n\\usepackage{wrapfig}\n\\usepackage{hyperref}\n\\"
                "usepackage[rgb]{xcolor}\n\\usepackage[T2A]{fontenc}\n\\usepackage[utf8]{inputenc}\n"
                "\\usepackage[russian, english]{babel}\n\\usepackage{amsmath,amsfonts,amssymb,amsthm,"
                "mathtools}\n\\usepackage{wasysym}\n\\author{Roman Lisov}\n\\title{Derivative "
                "with a tree in \\LaTeX{}}\n\\date{\\today}\n\\begin{document}\n\\maketitle\n"
                "\\tableofcontents\n\\newpage\n\n\\section{Our formula}\n\n");

    fprintf(fin, "\\begin{equation}\\label{formula}\n");
    Print_only_formula(fin, tree);
    fprintf(fin, "\n\\end{equation}\n\n");

    fprintf(fin, "\\section{Derivate with rules}\n\nWe see the formula. Let's start. "
                 "Firstly we see :\n\n ");
    fclose(fin);
    Node* tree_dif = this->Differentiator(tree);

    fin = fopen("Document777.tex", "aw");
    fprintf(fin, "\\textbf{After applying all known rules, we have : }\\[ ");
    Print_only_formula(fin, tree_dif);
    fprintf(fin, "\\]\n\n\n\n");


    fprintf(fin, "\\section{Optimisation}\n\nWe can optimize our formula :\n\n");
    fclose(fin);

    this->Optimisation(tree_dif);
    fin = fopen("Document777.tex", "aw");
    fprintf(fin, "\\section{Result}\n\\textbf{In the end we have :} \\[ ");
    Print_only_formula(fin, tree_dif);
    fprintf(fin, "\\]\n\\end{document}\n");

    fclose(fin);
    system("pdflatex Document777.tex");
    system("evince Document777.pdf");

}

#define FIRST_BRACKET fprintf(fin, "(")
#define SECOND_BRACKET fprintf(fin, ")")
#define PRINT_LEFT Print_only_formula(fin, root->left)
#define PRINT_RIGHT Print_only_formula(fin, root->right)
#define BRL_AND_PR FIRST_BRACKET; PRINT_LEFT
#define BRR_AND_PR PRINT_RIGHT; SECOND_BRACKET
#define ASSERT     assert(fin); assert(root)

void Dif::Print_only_formula(FILE *fin, Node *root)
{
    ASSERT;
    switch((int)root->type)
    {
        case Func:
            switch((int)root->value)
            {
                case Plus:
                {
                    BRL_AND_PR;
                    fprintf(fin, " + ");
                    BRR_AND_PR;
                    break;
                }
                case Minus:
                {
                    BRL_AND_PR;
                    fprintf(fin, " - ");
                    BRR_AND_PR;
                    break;
                }
                case Multy:
                {
                    if(root->left->type == Const && root->right->type == Var)
                    {
                        PRINT_LEFT;
                        PRINT_RIGHT;
                    }
                    else
                    {
                        PRINT_LEFT;
                        fprintf(fin, " \\cdot ");
                        PRINT_RIGHT;
                    }
                    break;
                }
                case Sin:
                {
                    fprintf(fin, " sin(");
                    BRR_AND_PR;
                    break;
                }
                case Cos:
                {
                    fprintf(fin, " cos(");
                    BRR_AND_PR;
                    break;
                }
                case Tan:
                {
                    fprintf(fin, " tan(");
                    BRR_AND_PR;
                    break;
                }
                case Cotan:
                {
                    fprintf(fin, " cot(");
                    BRR_AND_PR;
                    break;
                }
                case Log:
                {
                    fprintf(fin, " ln(");
                    BRR_AND_PR;
                    break;
                }
                case Exp:
                {
                    fprintf(fin, " e^{");
                    PRINT_RIGHT;
                    fprintf(fin, " }");
                    break;
                }
                case Sqrt:
                {
                    fprintf(fin, " sqrt{");
                    PRINT_RIGHT;
                    fprintf(fin, " }");
                    break;
                }
                case Divide:
                {
                    fprintf(fin, "\\frac{");
                    PRINT_LEFT;
                    fprintf(fin, " }{ ");
                    PRINT_RIGHT;
                    fprintf(fin, " }");
                    break;

                }
                default:
                    break;
                }
                case Var:
                    switch((int)root->value)
                    {
                        case Var_x:
                            fprintf(fin, "x");
                            break;
                        case Var_y:
                            fprintf(fin, "y");
                            break;
                        default:
                            break;
                    }
                    break;
                case Const:
                {
                    fprintf(fin, "%lg", root->value);
                }
                    break;
                default:
                    break;
            }
    }



void Dif::Multy_tex(FILE* fin, Node * root)
{
    ASSERT;
    fprintf(fin, "\\textbf{Now you see :}\n\n");
    fprintf(fin, "\\[f(x) \\cdot g(x)\\]\t");
    fprintf(fin, "Taking into account :\n\n \\[ f'(x)\\cdot g(x) + g'(x)\\cdot f(x) \\]\n\n");

    fprintf(fin, "\nThen, derivative is :\n\n\\begin{equation}\n(");
    Print_only_formula(fin, root->left);
    fprintf(fin, ")' \\cdot (");
    Print_only_formula(fin, root->right);
    fprintf(fin, ") + (");
    Print_only_formula(fin, root->right);
    fprintf(fin, ")' \\cdot (");
    Print_only_formula(fin, root->left);
    fprintf(fin, ")\n\\end{equation}\n\n");
}

void Dif::Divide_tex(FILE* fin, Node * root)
{
    ASSERT;
    fprintf(fin, "\\textbf{In this part is :}\n\n");
    fprintf(fin, "\\[\\frac{f(x)}{g(x)}\\]\t");
    fprintf(fin, "I can't imagine, but in this case mathematical rules in taking the derivative are :\n\n \\[ \\frac{f'(x)\\cdot g(x) - g'(x)\\cdot f(x)}{(g(x))^2}\\]\n\n");

    fprintf(fin, "\nThen, derivative is :\n\n\\begin{equation}\n");
    fprintf(fin, "\\frac{ (");
    Print_only_formula(fin, root->left);
    fprintf(fin, ")' \\cdot (");
    Print_only_formula(fin, root->right);
    fprintf(fin, ") - (");
    Print_only_formula(fin, root->right);
    fprintf(fin, ")' \\cdot (");
    Print_only_formula(fin, root->left);
    fprintf(fin, ") }{ (");
    Print_only_formula(fin, root->right);
    fprintf(fin, ")^2}\n\\end{equation}\n\n");
}

void Dif::Plus_tex(FILE* fin, Node * root)
{
    ASSERT;
    fprintf(fin, "\\textbf{We see :}\n\n");
    fprintf(fin, "\\[f(x) + g(x)\\]");
    fprintf(fin, "In this case mathematical rules for the sign <<plus>> are :\n\n \\[ f'(x) + g'(x) \\]\n\n");

    fprintf(fin, "\nThen, derivative is :\n\n\\begin{equation}\n(");
    Print_only_formula(fin, root->left);
    fprintf(fin, ")' + (");
    Print_only_formula(fin, root->right);
    fprintf(fin, ")'\n\\end{equation}\n\n");

}


void Dif::Minus_tex(FILE* fin, Node * root)
{
    ASSERT;
    fprintf(fin, "\\textbf{Formula :}\n\n");
    fprintf(fin, "\\[f(x) - g(x)\\]");
    fprintf(fin, "It is obvious :\n\n \\[ f'(x) + g'(x) \\]\n\n");

    fprintf(fin, "\nThen, derivative is :\n\n\\begin{equation}\n(");
    Print_only_formula(fin, root->left);
    fprintf(fin, ")' - (");
    Print_only_formula(fin, root->right);
    fprintf(fin, ")'\n\\end{equation}\n\n");
}

void Dif::Sin_tex(FILE* fin, Node * root)
{
    ASSERT;
    fprintf(fin, "\\textbf{Here we have :}\n\n");
    fprintf(fin, "\\[\\sin f(x)\\]\t");
    fprintf(fin, "I'm sure , you know :\n\n \\[ \\cos f(x)\\cdot f'(x) \\]\n\n");

    fprintf(fin, "\nThen, derivative is :\n\n\\begin{equation}\n\\cos ");
    Print_only_formula(fin, root->right);
    fprintf(fin, " \\cdot (");
    Print_only_formula(fin, root->right);
    fprintf(fin, ")'\n\\end{equation}\n\n");
}

void Dif::Cos_tex(FILE* fin, Node * root)
{
    ASSERT;
    fprintf(fin, "\\textbf{As for cosinus :}\n\n");
    fprintf(fin, "\\[\\cos f(x)\\]\t");
    fprintf(fin, "It is widely known, that in this case mathematical rules in taking the derivative is :\n\n \\[ - sin f(x)\cdot f'(x) \\]\n\n");
    fprintf(fin, "\nThen, derivative is :\n\n\\begin{equation}\n - \\sin ");
    Print_only_formula(fin, root->right);
    fprintf(fin, " \\cdot (");
    Print_only_formula(fin, root->right);
    fprintf(fin, ")'\n\\end{equation}\n\n");
}

void Dif::Tan_tex(FILE* fin, Node * root)
{
    ASSERT;
    fprintf(fin, "\\textbf{Here we have :}\n\n");
    fprintf(fin, "\\[\\tan f(x)\\]\t");
    fprintf(fin, "It is widely known, that in this case mathematical rules in taking the derivative is :\n\n \\[ \\frac{f'(x)}{\\cos^2f(x)} \\]\n\n");

    fprintf(fin, "\nThen, derivative is :\n\n\\begin{equation}\n \\frac{( ");
    Print_only_formula(fin, root->right);
    fprintf(fin, " )'}{ \\cos^2 (");
    Print_only_formula(fin, root->right);
    fprintf(fin, ")}\n\\end{equation}\n\n");
}

void Dif::Cotan_tex(FILE* fin, Node * root)
{
    ASSERT;
    fprintf(fin, "\\textbf{Cotangens now :}\n\n");
    fprintf(fin, "\\[\\cot f(x)\\]");
    fprintf(fin, "It is widely known, that in this case mathematical rules in taking the derivative is :\n\n \\[ - \\frac{f'(x)}{\\sin^2f(x)} \\]\n\n");

    fprintf(fin, "\nThen, derivative is :\n\n\\begin{equation}\n - \\frac{( ");
    Print_only_formula(fin, root->right);
    fprintf(fin, " )'}{ \\sin^2 (");
    Print_only_formula(fin, root->right);
    fprintf(fin, ")}\n\\end{equation}\n\n");
}

void Dif::Log_tex(FILE* fin, Node * root)
{
    ASSERT;
    fprintf(fin, "\\textbf{Look at this function :}\n\n");
    fprintf(fin, "\\[\\ln f(x)\\]");
    fprintf(fin, "It is widely known, that in this case mathematical rules in taking the derivative is :\n\n \\[ \\frac{f'(x)}{f(x)} \\]\n\n");

    fprintf(fin, "\nThen, derivative is :\n\n\\begin{equation}\n \\frac{( ");
    Print_only_formula(fin, root->right);
    fprintf(fin, " )'}{ ");
    Print_only_formula(fin, root->right);
    fprintf(fin, " }\n\\end{equation}\n\n");
}

void Dif::Exp_tex(FILE* fin, Node * root)
{
    ASSERT;
    fprintf(fin, "\\textbf{Here we have :}\n\n");
    fprintf(fin, "\\[e^{f(x)}\\]");
    fprintf(fin, "It is widely known, that in this case mathematical rules in taking the derivative is :\n\n \\[ f'(x) \\cdot e^{f(x)} \\]\n\n");

    fprintf(fin, "\nThen, derivative is :\n\n\\begin{equation}\n e^{ ");
    Print_only_formula(fin, root->right);
    fprintf(fin, " } \\cdot (");
    Print_only_formula(fin, root->right);
    fprintf(fin, ")'\n\\end{equation}\n\n");
}

void Dif::Sqrt_tex(FILE* fin, Node * root)
{
    ASSERT;
    fprintf(fin, "\\textbf{We have a formula :}\n");
    fprintf(fin, "\\[\\sqrt{f(x)}\\]");
    fprintf(fin, "Believe me or not :\n\n \\[ \\frac{f'(x)}{ 2 \\cdot \\sqrt{f(x)}} \\]\n\n");

    fprintf(fin, "\nThen, derivative is :\n\n\\begin{equation}\n \\frac{( ");
    Print_only_formula(fin, root->right);
    fprintf(fin, " )'}{ 2 \\cdot \\sqrt{ ");
    Print_only_formula(fin, root->right);
    fprintf(fin, "}}\n\\end{equation}\n\n");
}

void Dif::Var_x_tex(FILE *fin, Node *root)
{
    ASSERT;
    fprintf(fin, "Here derivative is :\n\n\\begin{equation}\\label{f'(x)}\n (x)' = 1\n");
    fprintf(fin, "\\end{equation}\n\n");
}

void Dif::Const_tex(FILE *fin, Node *root)
{
    ASSERT;
    fprintf(fin, "All of us know :\n\n\\begin{equation}\\label{f'(x)}\n (%lg)' = 0\n", root->value);
    fprintf(fin, "\\end{equation}\n\n");
}

void Dif::Var_y_tex(FILE *fin, Node *root)
{
    ASSERT;
    fprintf(fin, "All of us know :\n\n\\begin{equation}\\label{f'(x)}\n (y)' = 0 \n");
    fprintf(fin, "\\end{equation}\n\n");
    fprintf(fin, "We are taking the derivative as the function of x\n\n");
}

///------------------------------------------------------------------------------------------------------
///-----------------------------------------OPT_PRINT----------------------------------------------------
///------------------------------------------------------------------------------------------------------

void Dif::One_left_multy_tex(Node* root)
{
    FILE * fin = fopen("Document777.tex", "aw");
    ASSERT;
    fprintf(fin, "\\textbf{Look at it:}\n\n");
    fprintf(fin, "\\[ 1  \\cdot  a\\]");
    fprintf(fin, "It is widely known, that :\n");
    fprintf(fin, "\\begin{equation}\n");
    fprintf(fin, "1 \\cdot %lg = %lg", root->right->value, root->right->value);
    fprintf(fin, "\n\\end{equation}\n\n");
    fclose(fin);
}

void Dif::One_right_multy_tex(Node* root)
{
    FILE * fin = fopen("Document777.tex", "aw");
    ASSERT;
    fprintf(fin, "\\textbf{Oh, whauu:}\n\n");
    fprintf(fin, "\\[ a  \\cdot  1\\]");
    fprintf(fin, "It is widely known, that :\n");
    fprintf(fin, "\\begin{equation}\n");
    fprintf(fin, " %lg \\cdot 1 = %lg", root->left->value, root->left->value);
    fprintf(fin, "\n\\end{equation}\n\n");
    fclose(fin);
}

void Dif::Null_right_plus_tex(Node* root)
{
    FILE * fin = fopen("Document777.tex", "aw");
    ASSERT;
    fprintf(fin, "\\textbf{It sounds tempting:}\n\n");
    fprintf(fin, "\\[ a  +  0\\]");
    fprintf(fin, "It is widely known, that :\n");
    fprintf(fin, "\\begin{equation}\n");
    fprintf(fin, " %lg + 0 = %lg", root->left->value, root->left->value);
    fprintf(fin, "\n\\end{equation}\n\n");
    fclose(fin);
}

void Dif::Null_right_minus_tex(Node* root)
{
    FILE * fin = fopen("Document777.tex", "aw");
    ASSERT;
    fprintf(fin, "\\textbf{Believe me or not:}\n\n");
    fprintf(fin, "\\[ a  -  0\\]");
    fprintf(fin, "It is widely known, that :\n");
    fprintf(fin, "\\begin{equation}\n");
    fprintf(fin, " %lg - 0 = %lg", root->left->value, root->left->value);
    fprintf(fin, "\n\\end{equation}\n\n");
    fclose(fin);
}

void Dif::Null_left_plus_tex(Node* root)
{
    FILE * fin = fopen("Document777.tex", "aw");
    ASSERT;
    fprintf(fin, "\\textbf{Look here:}\n\n");
    fprintf(fin, "\\[ 0 + a\\]");
    fprintf(fin, "It is widely known, that :\n");
    fprintf(fin, "\\begin{equation}\n");
    fprintf(fin, " 0 + %lg = %lg", root->right->value, root->right->value);
    fprintf(fin, "\n\\end{equation}\n\n");
    fclose(fin);
}

void Dif::Null_left_multy_tex(Node* root)
{
    FILE * fin = fopen("Document777.tex", "aw");
    ASSERT;
    fprintf(fin, "\\textbf{Something unincredible:}\n\n");
    fprintf(fin, "\\[ 0 \\cdot a\\]");
    fprintf(fin, "It is widely known, that :\n");
    fprintf(fin, "\\begin{equation}\n");
    fprintf(fin, " 0 \\cdot %lg = 0", root->right->value);
    fprintf(fin, "\n\\end{equation}\n\n");
    fclose(fin);
}

void Dif::Null_right_multy_tex(Node* root)
{
    FILE * fin = fopen("Document777.tex", "aw");
    ASSERT;
    fprintf(fin, "\\textbf{We see the construction:}\n\n");
    fprintf(fin, "\\[ a \\cdot 0\\]");
    fprintf(fin, "SHOCK!, that :\n");
    fprintf(fin, "\\begin{equation}\n");
    fprintf(fin, " %lg \\cdot 0 = 0", root->left->value);
    fprintf(fin, "\n\\end{equation}\n\n");
    fclose(fin);
}





void Dif::Plus_opt_tex(Node* root)
{
    FILE * fin = fopen("Document777.tex", "aw");
    ASSERT;
    fprintf(fin, "\\textbf{Stop, but:}\n\n");
    fprintf(fin, "\\[ a + b\\]");
    fprintf(fin, "It is widely known, that :\n");
    fprintf(fin, "\\begin{equation}\n");
    fprintf(fin, "%lg + %lg = %lg", root->left->value, root->right->value,
            (root->left->value + root->right->value));
    fprintf(fin, "\n\\end{equation}\n\n");
    fclose(fin);
}

void Dif::Minus_opt_tex(Node* root)
{
    FILE * fin = fopen("Document777.tex", "aw");
    ASSERT;
    fprintf(fin, "\\textbf{It is strictly:}\n\n");
    fprintf(fin, "\\[ a - b\\]");
    fprintf(fin, "All know, that :\n");
    fprintf(fin, "\\begin{equation}\n");
    fprintf(fin, "%lg - %lg = %lg", root->left->value, root->right->value,
            (root->left->value - root->right->value));
    fprintf(fin, "\n\\end{equation}\n\n");
    fclose(fin);
}

void Dif::Multy_opt_tex(Node* root)
{
    FILE * fin = fopen("Document777.tex", "aw");
    ASSERT;
    fprintf(fin, "\\textbf{ You are sure:}\n\n");
    fprintf(fin, "\\[ a \\cdot b\\]");
    fprintf(fin, "\\begin{equation}\n");
    fprintf(fin, "%lg \\cdot %lg = %lg", root->left->value, root->right->value, root->left->value * root->right->value);
    fprintf(fin, "\n\\end{equation}\n\n");
    fclose(fin);
}

void Dif::Divide_opt_tex(Node* root)
{
    FILE * fin = fopen("Document777.tex", "aw");
    ASSERT;
    fprintf(fin, "\\textbf{Let's guess it:}\n\n");
    fprintf(fin, "\\[ \\frac{ a }{ b } \\]");
    fprintf(fin, "\nIt is not a joke ;))) but :\n");
    fprintf(fin, "\\begin{equation}\n");
    fprintf(fin, "\\frac{ %lg }{ %lg } = %lg", root->left->value, root->right->value, root->left->value / root->right->value);
    fprintf(fin, "\n\\end{equation}\n\n");
    fclose(fin);
}

