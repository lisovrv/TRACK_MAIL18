#include <stdio.h>
#include "Akinator.h"

int main()
{
    Tree* tree =  Create_new_game();
    Akinator(tree);
    return 0;
}

/*int main()
{
    Tree* tree =  new Tree("Human");
    value = tree->Add_Left_Tree("Women", tree->root);
    tree->Add_Right_Tree("Men", tree->root);
    tree->Add_Left_Tree("Boy", tree->root->right);
    tree->Add_Right_Tree("Boss", tree->root->right);
    tree->Add_Right_Tree("Mam", tree->root->left);
    tree->Add_Left_Tree("Girl", tree->root->left);
    tree->root->left->parent = tree->root->left;
    error_tree error = NO_ERR;
    tree->Test(error);
    tree->Dump();
    tree->root->PrintDot("tree.dot");
    delete tree;

    return 0;
}*/
