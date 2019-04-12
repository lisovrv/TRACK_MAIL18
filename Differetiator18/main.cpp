#include <stdio.h>
#include <locale.h>

#include "Differentiator.h"


int main()
{

    Rdp* _rdp_ = new Rdp();

    Tree* tree = _rdp_->GetTree("sin(exp(x+2)*(x+x))");
    if(tree == nullptr)
    {
        printf("Error while building a tree!\n");
        exit(222);
    }

    //tree->root->PrintDot("function_tree.dot");

    Dif* diff_tree = new Dif();
    diff_tree->PrintTEX(tree->root);

    delete tree;
    delete diff_tree;
    delete _rdp_;


    return 0;
}

