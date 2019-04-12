#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <unistd.h>
#include <assert.h>

#include "Akinator.h"

const char* ans_yes = "yes";
const char* ans_no = "no";
const char* poison = "POISON!";

void Akinator(Tree* tree)
{
    assert(tree);
    FILE * fin = fopen("base.txt", "r");
    assert(fin);
    if(sizeof_file(fin) != 0)
    {
        Ending_the_game(tree->root);
        tree->root = BuildingTree(fin);
    }
    fclose(fin);
    //Menu();
    Questions(tree->root);
    SaveTree(tree->root);
    //FindTree(tree->root);
    tree->root->PrintDot("base_akinator.dot");
    Free_Mem_Node(tree->root);
}

void FindTree(Node* root)
{
    assert(root);
    char* answer = (char*)calloc (LENGTH, sizeof(char));
    //printf("AAAAA\n");
    scanf("%s", answer);
    //printf("AAAAA\n");
    Rec_Find(root, answer);
    free(answer);
}

void Rec_Find(Node* root, char* answer)
{
    assert(root);
    assert(answer);
    if((strcmp(answer, root->value) != 0) && root->left != nullptr)
    {
        Rec_Find(root->left, answer);
    }
    if((strcmp(answer, root->value) != 0) && root->right != nullptr)
    {
        Rec_Find(root->right, answer);
    }
    if(strcmp(answer, root->value) == 0)
    {
        while(root->parent != nullptr)
        {
            if(root->parent->left == root)
            {
                printf("It is: %s\n", root->parent->value );
            }
            if(root->parent->right == root)
            {
                printf("It is not : %s\n", root->parent->value );
            }
            root = root->parent;
        }
    }
}

void SaveTree(Node* root)
{
    assert(root);
    FILE * fin = fopen("base.txt", "w");
    assert(fin);
    PrintTree(root, fin);
    fclose(fin);
}

void Ending_the_game(Node* root)
{
    assert(root);
    root->~Node();
}

void Free_Mem_Node(Node* root)
{
    assert(root);
    delete root->left;
    free((void*)root->left->value);
    delete root->right;
    free((void*)root->right->value);

}

Node* BuildingTree(FILE * fin)
{
    assert(fin);
    long sizebuff = sizeof_file(fin);
    char *buff = (char*) calloc((size_t)sizebuff, sizeof(char));
    assert(buff);
    input(buff, (int)sizebuff, fin);
    int j = 0;

    char* str_val1 = (char*) calloc(LENGTH, sizeof(char));
    assert(str_val1);
    for(int i = 1; buff[i] != '{' ; i++)
    {
        str_val1[j] = buff[i];
        j++;
    }
    Node* root = new Node((char*)poison);
    assert(root);
    root->value = (char*) calloc(LENGTH, sizeof(char));
    assert(root->value);
    strcpy((char*) root->value, str_val1);
    free(str_val1);

    for(int i = 1; i < sizebuff - 1; i++)
    {
        if(buff[i] == '{')
        {
            Node* nod = Add_node(buff,i);
            if(!(root->left))
            {
                root->left = nod;
                nod->parent = root;
                root = root->left;
            }
            else
            {
                root->right = nod;
                nod->parent = root;
                root = root->right;
            }
        }
        if(buff[i] == '}')
        {
            root = root->parent;
        }


    }
    free(buff);
    return root;

}

Node* Add_node(char* buff, int i)
{
    assert(buff);
    char* str_val2 = (char*)calloc(LENGTH, sizeof(char));
    i++;
    int j = 0;
    for(i; buff[i] != '}' && buff[i] != '{' ; i++)
    {
        str_val2[j] = buff[i];
        j++;
    }
    Node* nod = new Node((char*)poison);
    nod->value = (char*) calloc(LENGTH, sizeof(char));
    strcpy((char*) nod->value, str_val2);
    free(str_val2);
    return nod;
}

void PrintTree(Node* root, FILE* fin)
{
    assert(root);
    assert(fin);
    fprintf(fin, "{%s", root->value);

    if(root->left)
    {
        PrintTree(root->left, fin);
    }

    if(root->right)
    {
        PrintTree(root->right, fin);
        fprintf(fin, "}");
    }

    if(!(root->left) || !(root->right))
    {
        fprintf(fin, "}");
    }
}


void Questions(Node* root)
{
    assert( root);
    if(root->left && root->right)
    {
        printf("    \t\t\t\t\tIt is \"%s\"?\n", root->value);
        system("espeak \"It is  \"");
        const char* esp = "espeak ";
        char* res = (char*) calloc (LENGTH, sizeof(char));
        const char* val = root->value;
        res = strcat(strcat(res, esp), val);
        //printf("%s\n", res);
        system(res);
        free(res);

        char* answer = (char*) calloc (LENGTH, sizeof(char));
        scanf("%s", answer);

        if(strcmp(answer, ans_no) == 0)
        {
            Questions(root->right);
        }
        else if(strcmp(answer, ans_yes) == 0)
        {
            Questions(root->left);
        }
        else if(strcmp(answer, ans_no) != 0 && strcmp(answer, ans_yes) != 0)
        {
            printf("\t\t\t\tPlease, answer exactly \"yes\" or \"no\" !");
            system("espeak \"Please, answer exactly yes or   no\n");
            while(root->parent)
            {
                root = root->parent;
            }
            Questions(root);

        }
        free(answer);
    }
    else
    {
        printf("    \t\t\tAnd the last question. It is : \"%s\" ?\n", root->value);
        system("espeak \"And the last question.  It is  :\"");
        const char* esp = "espeak ";
        char* res = (char*) calloc (LENGTH, sizeof(char));
        const char* val = root->value;
        res = strcat(strcat(res, esp), val);
        //printf("%s\n", res);
        system(res);
        free(res);

        char* answer2 = (char*)calloc (LENGTH, sizeof(char));
        scanf("%s", answer2);

        if (strcmp(answer2, ans_yes) == 0)
        {
            printf("\t\t\t\t\tIt was very easy for_Me!\n");
            printf("\t\t\t\t   Do you want to start a new game?\n");
            system("espeak \"It was very easy for_Me!   Do you want to start a new game?\"");

            char* answer5 = (char*)calloc (LENGTH, sizeof(char));
            scanf("%s", answer5);

            if(strcmp(answer5, ans_yes) == 0)
            {
                free(answer2);
                free(answer5);
                while(root->parent)
                {
                    root = root->parent;
                }
                Questions(root);
            }
            else
            {
                printf("\t\t\tIt was interesting to play with you! Good buy!\n\n\n\n");
                system("espeak \"It was interesting to play with you! Good buy!\"");
                while(root->parent)
                {
                    root = root->parent;
                }
                free(answer5);
                free(answer2);
            }
        }
        else if(strcmp(answer2, ans_no) == 0)
        {
            printf("\t\t\t\t\tWhat's the difference?\n");
            system("espeak \"What's  the  difference?\"");

            char* answer3 = (char*)calloc (LENGTH, sizeof(char));
            scanf("%s", answer3);

            Node* nod_diff = new Node(poison);
            nod_diff->value = (char*) calloc(LENGTH, sizeof(char));
            strcpy((char*)nod_diff->value, (const char*) answer3);


            printf("\t\t\t\t\t   Who is it?\n");
            system("espeak \"   Who is it?\"");

            char* answer4 = (char*)calloc (LENGTH, sizeof(char));
            scanf("%s", answer4);

            Node* nod_true_ans = new Node(poison);
            nod_true_ans->value = (char*) calloc(LENGTH, sizeof(char));
            strcpy((char*)nod_true_ans->value, (const char*) answer4);


            free(answer3);
            free(answer4);


            if(root == root->parent->left)
            {
                root->parent->left = nod_diff;
            }
            if(root == root->parent->right)
            {
                root->parent->right = nod_diff;
            }

            nod_diff->parent = root->parent;
            nod_diff->left = nod_true_ans;
            nod_diff->right = root;
            root->parent = nod_diff;
            nod_true_ans->parent = nod_diff;



            while(root->parent)
            {
                root = root->parent;
            }

            printf("\t\t\t    Next time I'll guess it!\n\n");
            printf("\t\t\t   Do you want to start a new game?\n");
            system("espeak \"Next time I'll guess it!    Do you want to start a new game?\"");

            char* answer6 = (char*)calloc (LENGTH, sizeof(char));
            scanf("%s", answer6);

            if(strcmp(answer6, ans_yes) == 0)
            {
                Questions(root);
            }
            else
            {
                printf("\t\t\tIt was interesting to play with you! Good buy!\n");
                system("espeak \"It was interesting to play with you! Good buy!\"");
            }
            free(answer6);
            free(answer2);

        }
        else if(strcmp(answer2, ans_no) != 0 && strcmp(answer2, ans_yes) != 0)
        {
            printf("\t\t\t\tPlease, answer exactly \"yes\" or \"no\" !");
            system("espeak \"Please, answer exactly yes or   no\n");
            while(root->parent)
            {
                root = root->parent;
            }
            Questions(root);
            free(answer2);

        }
    }
}


Tree* Create_new_game()
{
    Tree* tree =  new Tree("Female");
    tree->root->value = (char*) calloc(LENGTH, sizeof(char));
    strcpy((char*)tree->root->value, "Female");

    tree->Add_Right_Tree("Sashin_Alexey", tree->root);
    tree->root->right->value = (char*) calloc(LENGTH, sizeof(char));
    strcpy((char*)tree->root->right->value, "Sashin_Alexey");


    tree->Add_Left_Tree("Angela_Merkel", tree->root);
    tree->root->left->value = (char*) calloc(LENGTH, sizeof(char));
    strcpy((char*)tree->root->left->value, "Angela_Merkel");

    return tree;
}

void Menu()
{
    printf("\t\t\t\tHello! Nice to meet you! I'm a clever program.\n\n");
    sleep(1);
    printf("\t\tI am going to ask you some questions trying to guess the person you have thought!\n\n");
    sleep(2);
    printf("\t   There're some rules. Please, give your answer in such strict forms: \"with_clorophil\", or \"not_alive\"\n\n");
    sleep(3);
    printf("\t\t\t\tPrint Yes or no ( yes/no ) as the answer to my questions.\n\n");
    sleep(2);
    printf("\t\t\t\tIf all the rules are clear for you, print now \"yes\"\n\n");
    char* ans = (char*)calloc(LENGTH, sizeof(char));
    scanf("%s", ans);
    if(strcmp(ans, ans_yes) != 0)
    {
        printf("Try again next time!\n");
        exit(34);
    }
    printf("\t\t\t\t\tGreat! Let's start :)\n\n\n");
    sleep(3);
}

long sizeof_file(FILE *fin)
{
    assert(fin);
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

void input(char *buff, int size, FILE *fin)
{
    assert(buff);
    assert(fin);
    fread(buff, sizeof(char), (size_t ) size, fin);
}













