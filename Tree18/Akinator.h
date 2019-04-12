#ifndef TREE18_AKINATOR_H
#define TREE18_AKINATOR_H

#include "tree.h"

#define    LENGTH 50

extern const char* ans_yes;
extern const char* ans_no;

Tree*   Create_new_game();
void    Questions(Node* root);
void    Akinator(Tree* tree);
void    Menu();
void    PrintTree(Node* root,FILE * fin);
Node*   BuildingTree(FILE * fin);
long    sizeof_file(FILE *fin);
void    input(char *buff, int size, FILE *fin);
Node*   Add_node(char* buff, int i);
void    Ending_the_game(Node* root);
void    SaveTree(Node* root);
void    Free_Mem_Node(Node* root);
void    Rec_Find(Node* root, char* answer);


void FindTree(Node* root);

#endif //TREE18_AKINATOR_H
