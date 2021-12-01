#include <iostream>
#include <queue>
#include "StructNode.h"

Node *CreateNode(int Key)
{
    Node *pRoot = new Node;

    pRoot->Key = Key;
    pRoot->pLeft = NULL;
    pRoot->pLeft = NULL;

    return pRoot;
}
int Hight(Node *pRoot)
{
    int Left, Right, MaxSub;
    if (pRoot == NULL)
    {
        return 0;
    }

    Left = Hight(pRoot->pLeft);
    Right = Hight(pRoot->pRight);

    if (Left > Right)
    {
        return Left + 1;
    }
    else
    {
        return Right + 1;
    }
}
void LRotate(Node *&pRoot)
{
    Node *p = pRoot->pRight;

    pRoot->pRight = p->pLeft;
    p->pLeft = pRoot;
    pRoot = p;
}
void RRotate(Node *&pRoot)
{
    Node *p = pRoot->pLeft;

    pRoot->pLeft = p->pRight;
    p->pRight = pRoot;
    pRoot = p;
}
void InsertNode(Node *&pRoot, int Key)
{
    if (pRoot == NULL)
    {
        pRoot = CreateNode(Key);
        return;
    }
    if (pRoot->Key < Key)
    {
        InsertNode(pRoot->pRight, Key);
    }
    if (pRoot->Key > Key)
    {
        InsertNode(pRoot->pLeft, Key);
    }

    int Balance = Hight(pRoot->pRight) - Hight(pRoot->pLeft);

    if (Balance >= 2) // Mat can bang phai
    {
        if (Hight(pRoot->pRight->pRight) >= Hight(pRoot->pRight->pLeft)) // R R
        {
            LRotate(pRoot); // quay trai
        }
        if (Hight(pRoot->pRight->pRight) < Hight(pRoot->pRight->pLeft)) // R R
        {
            RRotate(pRoot->pRight); // quay phai subtree
            LRotate(pRoot);         // quay trai pRoot
        }
    }
    if (Balance <= -2)
    {
        if (Hight(pRoot->pLeft->pLeft) >= Hight(pRoot->pLeft->pRight)) // R R
        {
            RRotate(pRoot); // Quay phai
        }
        if (Hight(pRoot->pRight->pRight) < Hight(pRoot->pRight->pLeft)) // R R
        {
            LRotate(pRoot->pLeft);
            RRotate(pRoot);
        }
    }
}
void LevelOrder(Node *&pRoot)
{
    if (pRoot == NULL)
        return;
    std::queue<Node *> Q;
    Q.push(pRoot);
    while (!Q.empty())
    {
        Node *p = Q.front(); // lấy giá trị phần tử đầu tiên
        Q.pop();             // xóa giá trị đầu tiên trong queue
        std::cout << p->Key << "  ";
        if (p->pLeft != NULL)
            Q.push(p->pLeft);
        if (p->pRight != NULL)
            Q.push(p->pRight);
        
    }
}

void Remove(Node *&pRoot, int x)
{
    if (pRoot == NULL)
    {
        return;
    }
    if (x > pRoot->Key)
    {
        Remove(pRoot->pRight, x);
    }
    if (x < pRoot->Key)
    {
        Remove(pRoot->pLeft, x);
    }
    if (pRoot->Key == x)
    {
        if (pRoot->pLeft == NULL && pRoot->pRight == NULL)
        {
            delete pRoot;
            pRoot = NULL;
        }
        else if (pRoot->pLeft != NULL && pRoot->pRight == NULL)
        {
            Node *p = pRoot;
            pRoot = pRoot->pLeft;
            delete p;
        }
        else if (pRoot->pLeft == NULL && pRoot->pRight != NULL)
        {
            Node *p = pRoot;
            pRoot = pRoot->pRight;
            delete p;
        }
        else if (pRoot->pLeft != NULL && pRoot->pRight != NULL)
        {
            Node *p = pRoot->pRight;
            while (p->pLeft != NULL)
            {
                p = p->pLeft;
            }
            pRoot->Key = p->Key;
            Remove(pRoot->pRight, pRoot->Key);
        }
    }
}
int Max(Node *pRoot)
{
    if(pRoot == NULL)
        return -10000000;
    
    int Left, Right, MaxSub;
    Left = Max(pRoot->pLeft);
    Right = Max(pRoot->pRight);

    if (Left > Right) {
        MaxSub = Left;
    }
    else
        MaxSub = Right;

    if (MaxSub > pRoot->Key){
        return MaxSub;
    }
    return pRoot->Key;
}

int Min(Node *pRoot)
{
    if(pRoot == NULL)
        return 100000000;
    
    int Left, Right, MinSub;
    Left = Min(pRoot->pLeft);
    Right = Min(pRoot->pRight);

    if (Left < Right) {
        MinSub = Left;
    }
    else
        MinSub = Right;

    if (MinSub < pRoot->Key){
        return MinSub;
    }
    return pRoot->Key;

}

bool isAVL(Node* pRoot)
{
    if (pRoot == NULL)
        return true;

    std::queue<Node*> Q; 
    Q.push(pRoot);
    while (!Q.empty())
    {
        Node *Temp = Q.front();
        Q.pop();

        std::cout << Temp->Key << " ";
        // Cac dieu kien thoa mang AVL
        if(Temp->Key < Max(Temp->pLeft) || Temp->Key > Min(Temp->pRight))
            return false;

        // chieu cao cua subTree chenh len nhau khong qua 1
        int Balance = Hight(Temp->pRight) - Hight(Temp->pLeft);
        if (Balance > 1 && Balance < -1)
            return false;
        
        // xet Node de dua vao Q
        if (Temp->pLeft != NULL)
            Q.push(Temp->pLeft);
        if (Temp->pRight != NULL)
            Q.push(Temp->pRight);
    }
    return true;  
}