#pragma once
#include "ShadowTreeNode.h"
//为了实现打印操作，采用队列存储影子树的节点,包括判空删除、入队等操作
class ShadowTreeQueue{
     public:
        ShadowTreeNode *TNode[1000] = {NULL};
        int begin = 0, end = -1;//begin是队头，end是队尾,begin>end时队列为空
        bool empty() {
            return begin > end;
        }
        void push(ShadowTreeNode* node) {
            TNode[++end] = node;
        }
        void pop() {
            begin++;
        }
        ShadowTreeNode* front() {
             return TNode[begin];
        }
};


