#pragma once
#include "AVLTree.h"
#include "ShadowTreeNode.h"
#include "ShadowTreeQueue.h"
#include <cstring>
#include <fstream>
#include<algorithm>
int AVLTree::Get_Max_Username_Length(TNode* Treenode) {
    int MaxLength = Treenode->getusername().length();
    if (Treenode->left) {
        MaxLength = max(MaxLength, Get_Max_Username_Length(Treenode->left));
    }
    if (Treenode->right) {
        MaxLength = max(MaxLength, Get_Max_Username_Length(Treenode->right));
    }
    return MaxLength;
}

//建立AVL树对应的影子树
ShadowTreeNode* AVLTree::Build_ShadowTree(TNode* Tree, ShadowTreeNode* ShadowTree, int Treelevel) {
    //先左子树再根点再右子树
    if (Tree != NULL){
        static int TreeColumn;//由于每次出现一个新的点，它的列坐标需要+1，所以需要定义为静态局部变量
        if (Treelevel == 1) {
            TreeColumn = 1;
        }
        ShadowTree = new ShadowTreeNode();
        ShadowTree->left = Build_ShadowTree(Tree->left, ShadowTree->left, Treelevel + 1);
        ShadowTree->column = TreeColumn;
        TreeColumn++;
        ShadowTree->level = Treelevel;
        ShadowTree->username = Tree->getusername();
        //cout << ShadowTree->username << ShadowTree->level << ShadowTree->column<<endl;
        ShadowTree->right = Build_ShadowTree(Tree->right, ShadowTree->right, Treelevel + 1);
    }
    return ShadowTree;
}

//通过建立影子树实现正向打印二叉树
void AVLTree::display() {
    if (root == NULL) return;//根节点为空不打印
    //创建影子树和对应队列
    ShadowTreeNode* ShadowTree = NULL;
    ShadowTree = Build_ShadowTree(root, ShadowTree, 1);
    ShadowTreeQueue q;
    q.push(ShadowTree);
    int nowlevel = 1, nowcolumn = 0;
    int MaxLength = Get_Max_Username_Length(root);//由于username的长度不同，获取最大值进行计算
    //同二叉树的层次遍历
    while (!q.empty()) {
        ShadowTreeNode* firstnode = q.front();
        q.pop();
        string new_username = firstnode->username;
        //设置打印格式，对于名字较短的后面补空格
        while (new_username.length() < MaxLength) {
            new_username = new_username.append(" ");
        }
        //如果当前节点所指向行数大于当前行数，则重设当前行数，列数
        if (firstnode->level > nowlevel) {
            cout << endl;
            nowlevel = firstnode->level;
            nowcolumn = 0;
        }
        //输出前置空格
        for (int i = 1; i < firstnode->column - nowcolumn; i++) {
            for (int j = 0; j < MaxLength; j++) 
                cout << ' ';
        }
        cout << new_username;
        nowcolumn = firstnode->column;
        if (firstnode->left != NULL) q.push(firstnode->left);//如果左子树非空，将其加入打印队列
        if (firstnode->right != NULL) q.push(firstnode->right);
    }
    cout << endl;
}

TNode* AVLTree::SearchTNode(TNode* tnode,string username) {
    if (tnode == NULL) return NULL;//找到最后为空即找不到则返回空指针
    if (tnode->getusername() == username) {//找到了就返回对应节点指针
        return tnode;
    }
    //如果现节点内容大于要查找的内容，则到左子树上找，不然则去右子树上找，如此递归
    else if (tnode->getusername() > username){
        return SearchTNode(tnode->left,username);
    }
    else {
        return SearchTNode(tnode->right,username);
    }
}
//左旋 旋转后重设高度
TNode* AVLTree::Left_Rotation(TNode* tree) {
    TNode* right = tree->right;
    tree->right = right->left;
    right->left = tree;
    tree->setheight(max(tree->left->getheight(), tree->right->getheight()) + 1);
    right->setheight(max(right->left->getheight(), right->right->getheight()) + 1);
    return right;
}
//右旋 旋转后重设高度
TNode* AVLTree::Right_Rotation(TNode* tree) {
    TNode* left = tree->left;
    tree->left = left->right;
    left->right = tree;
    tree->setheight(max(tree->left->getheight(), tree->right->getheight()) + 1);
    left->setheight(max(left->left->getheight(), left->right->getheight()) + 1);
    return left;
}

//左子树的右子树与左子树的左子树比较旋转
TNode* AVLTree::Rotation1(TNode* tnode) {
    //如果高度差为2，则要进行旋转操作
    if ((tnode->left->getheight() - tnode->right->getheight()) == 2) {
        //左子树的右子树不高于左子树，右旋，不然先左旋后右旋
        if (tnode->left->left->getheight() >= tnode->left->right->getheight()) {
            tnode = Right_Rotation(tnode);
        }
        else {
            tnode->left = Left_Rotation(tnode->left);
            tnode = Right_Rotation(tnode);
        }
    }
    return tnode;
}

//右子树的右子树与右子树的左子树比较旋转
TNode* AVLTree::Rotation2(TNode* tnode) {
    //如果高度差为2，则要进行旋转操作
    if ((tnode->right->getheight() - tnode->left->getheight()) == 2) {
        //右子树的左子树不高于右子树，左旋，不然先右旋后左旋
        if (tnode->right->left->getheight() <= tnode->right->right->getheight()) {
            tnode = Left_Rotation(tnode);
        }
        else {
            tnode->right = Right_Rotation(tnode->right);
            tnode = Left_Rotation(tnode);
        }
    }
    return tnode;
}
//添加用户功能，如果存在则不添加，不然则不添加
void AVLTree::addUser(string username, string password) {
    //如果已存在该用户，则不添加，不然则调用addTNode增加节点
    if (SearchTNode(root,username) != NULL) {
        cout << "\n\n\t\t\t\t已存在该用户";
        return;
    }
    root = addTNode(root, username, password);
}

//添加节点，找到对应位置插入，再自底向上进行旋转平衡调整
TNode *AVLTree::addTNode(TNode *tnode, string username, string password) {
    //如果找到空节点则插入，不然则继续递归查找
    if (tnode == NULL) {
        tnode = new TNode(username, password);
        return tnode;
    }
    //如果现节点内容大于要插入节点的内容，则到左子树上找，不然则去右子树上找，如此递归
    else if (username < tnode->getusername()){
        tnode->left = addTNode(tnode->left, username, password);
        tnode=Rotation1(tnode);
    } else {
        tnode->right = addTNode(tnode->right, username, password);
        tnode = Rotation2(tnode);
    }
    //调整树高
    tnode->setheight(max(tnode->left->getheight(), tnode->right->getheight()) + 1);
    return tnode;
}
//删除用户功能，如果存在则删除，不然则不删除
void AVLTree::deleteUser(string username) {
    //如果不存在则不删除，不然调用函数就删除username对应节点
    if (SearchTNode(root, username) == NULL) {
        cout << "\n\n\t\t\t\t该用户不存在";
        return;
    }
    root = deleteTNode(root, username);
}

//删除节点，找到对应位置删除，再自底向上进行旋转平衡调整
TNode *AVLTree::deleteTNode(TNode *tnode, string username) {
    //找到空节点即返回空指针 不操作
    if (tnode == NULL) return NULL;
    //如果现节点内容大于要删除节点的内容，则到左子树上找，不然则去右子树上找，如此递归
    if (username < tnode->getusername()) {
        tnode->left = deleteTNode(tnode->left, username);
        tnode=Rotation1(tnode);
    } else if (username > tnode->getusername()) {
        tnode->right = deleteTNode(tnode->right, username);
        tnode = Rotation2(tnode);
    } else {//如果找到了要删除的点
        if (tnode->left != NULL && tnode->right != NULL) {
            //如果该点两侧都有子树，如果左子树高于右子树，则用左子树的最大值替换该节点
            if (tnode->left->getheight() > tnode->right->getheight()) {
                TNode *maxnode = maxTNode(tnode->left);
                tnode->setusername(maxnode->getusername());
                tnode->setpassword(maxnode->getpassword());
                tnode->left = deleteTNode(tnode->left, maxnode->getusername());//删除左子树最大点
            } else {
                //用右子树的最小值替换该节点
                TNode* minnode = minTNode(tnode->right);
                tnode->setusername(minnode->getusername());
                tnode->setpassword(minnode->getpassword());
                tnode->right = deleteTNode(tnode->right, minnode->getusername());
            }
        } else {//如果树的一侧为空，就直接删除，后将子树替换为该点
            TNode *node = tnode;
            if (tnode->left != NULL) {
                tnode = tnode->left;
            } else {
                tnode = tnode->right;
            }
            delete node;//删除节点
        }
    }
    if (tnode != NULL) {
        tnode->setheight(max(tnode->left->getheight(), tnode->right->getheight()) + 1);
    }
    return tnode;
}

//获取值最大的节点
TNode *AVLTree::maxTNode(TNode *tnode) {
    //存在右子树则右子树更大，不然根点最大
    if (tnode->right != NULL) {
        return maxTNode(tnode->right);
    }
    return tnode;
}
//获取值最小的节点
TNode *AVLTree::minTNode(TNode *tnode) {
    //存在右子树则右子树更大，不然根点最小
    if (tnode->left != NULL) {
        return minTNode(tnode->left);
    }
    return tnode;
}
 

void AVLTree::getmessage() {
    string username, password;
    ifstream infile;
    infile.open("database.dat", ios::in);
    while (infile >> username >> password) {
        addUser(username, password);
    }
    infile.close();
}
void AVLTree::savemessage(TNode* tree) {
    //将树存入文件，对于空节点则表明递归结束
    if (tree == NULL) {
        return;
    }
    ofstream out;
    //根点表明第一次输入，清除原文件，而如果不是第一次输入，则继续写入
    if (tree == root) {
        out.open("database.dat");
    }
    else {
        out.open("database.dat", ios::app);
    }
    out << tree->getusername() << " " << tree->getpassword() << endl;
    out.close();
    savemessage(tree->left);//递归遍历左子树
    savemessage(tree->right);//递归遍历右子树
}