#pragma once
#include "TNode.h"
#include "ShadowTreeNode.h"
class AVLTree {
    public:
        TNode *root=NULL;

        AVLTree() {
            root = NULL;
        }
        ~AVLTree() {
            Memory_Release(root);
        }
        //内存释放
        void Memory_Release(TNode *node) {
            if (node->left) {
                Memory_Release(node->left);
            }
            if (node->right) {
                Memory_Release(node->right);
            }
            delete node;
        }

        /****************正向打印AVL树相关*****************/
        int Get_Max_Username_Length(TNode* Tree);//获取以Tree节点为root的树的各个username中的最大值 为了实现打印格式的设置
        ShadowTreeNode* Build_ShadowTree(TNode* Tree, ShadowTreeNode* ShadowTree, int Treelevel);//生成对应的影子树用于打印
        void display();//实现正向打印二叉树

        /****************删除与增加节点以及对应的将树平衡操作*****************/
        TNode* SearchTNode(TNode* Tree, string username);//查找username对应节点，用于添加(存在则不添加)和删除（不存在则无法删除）
        
        //实现二叉树的左旋和右旋
        TNode* Left_Rotation(TNode* tree);
        TNode* Right_Rotation(TNode* tree);
       
        //结合左旋与右旋
        TNode* Rotation1(TNode* tree);
        TNode* Rotation2(TNode* tree);

        void addUser(string usrename, string password);//添加用户功能
        TNode *addTNode(TNode *tnode, string username, string password);//用于添加节点
    
        void deleteUser(string username);//删除用户功能 如果存在则删除节点 不然则不删除
        TNode *deleteTNode(TNode *tnode, string username);//删除对应节点
        TNode *maxTNode(TNode *tnode);//返回最大节点
        TNode *minTNode(TNode *tnode);//返回最小节点

        void getmessage();
        void savemessage(TNode *tree);//保存树到文件
        
};

