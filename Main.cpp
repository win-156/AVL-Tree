#include <iostream>
#include "StructNode.h"
#include "Algorithm_AVL.h"
using namespace std;


int main()
{
    int a[8] = {35, 17, 66, 25, 50, 71, 68, 94};
    Node *pRoot = NULL;
    for (int i = 0; i < 8; i++)
    {
        InsertNode(pRoot, a[i]);
    }
    LevelOrder(pRoot); cout << endl;

    bool AVL__test = isAVL(pRoot);
    if (AVL__test == true)
    {
        cout << "chinh xac\n";
    }
    else
        cout << "sai\n";
    
    // cout << endl << Hight(pRoot) << endl;
    return 0;
}