#include "AVLTree.h"

int AVLTree::Search(const QString s, AVLNode* ptr) {
  // Alert: ptr != nullptr
  wCmp++;
  if (s < getEn(ptr) && ptr->left)
    return Search(s, ptr->left);
  if (s > getEn(ptr) && ptr->right)
    return Search(s, ptr->right);
  if (s == getEn(ptr)) {
    return ptr->num;
  }
  return -1 * ptr->num;  // Last Before Failure
}

void AVLTree::RotateL(AVLNode*& ptr) {
  AVLNode* subL = ptr;
  ptr = subL->right;
  subL->right = ptr->left;
  ptr->left = subL;
  ptr->bf = subL->bf = 0;
}

void AVLTree::RotateR(AVLNode*& ptr) {
  AVLNode* subR = ptr;
  ptr = subR->left;
  subR->left = ptr->right;
  ptr->right = subR;
  ptr->bf = subR->bf = 0;
}

void AVLTree::RotateLR(AVLNode*& ptr) {
  AVLNode *subR = ptr, *subL = subR->left;
  ptr = subL->right;
  subL->right = ptr->left;
  ptr->left = subL;
  if (ptr->bf <= 0)
    subL->bf = 0;
  else
    subL->bf = -1;
  subR->left = ptr->right;
  ptr->right = subR;
  if (ptr->bf == -1)
    subR->bf = 1;
  else
    subR->bf = 0;
  ptr->bf = 0;
}

void AVLTree::RotateRL(AVLNode*& ptr) {
  AVLNode *subL = ptr, *subR = subL->right;
  ptr = subR->left;
  subR->left = ptr->right;
  ptr->right = subR;
  if (ptr->bf >= 0)
    subR->bf = 0;
  else
    subR->bf = 1;
  subL->right = ptr->left;
  ptr->left = subL;
  if (ptr->bf == 1)
    subL->bf = -1;
  else
    subR->bf = 0;
  ptr->bf = 0;
}

bool AVLTree::Insert(int n, AVLNode*& ptr) {
  AVLNode* pr = nullptr;
  AVLNode *p = ptr, *q;
  auto s = vec[n].en;
  int lable;  //标签
  stack<AVLNode*>
      st;  //栈记录查找路径,当插入元素后，通过出栈回溯，平衡化祖先节点
  while (p != nullptr) {
    if (s == getEn(p))
      return false;  //存在值为x的结点，不插入
    pr = p;          // pr存储插入节点的父结点
    st.push(pr);     //存储搜索路径
    if (s < getEn(p))
      p = p->left;
    else
      p = p->right;
  }
  p = new AVLNode(n);
  if (p == nullptr) {
    qDebug() << "存储空间分配错误！";
    exit(1);
  }
  if (pr == nullptr) {
    ptr = p;
    return true;  //空树，新插入结点为根节点
  }
  if (s < getEn(pr)) {
    pr->left = p;
  } else {
    pr->right = p;
  }
  while (st.empty() == false) {  //将插入新结点后得到的树重新平衡化
    pr = st.top();
    st.pop();
    if (p == pr->left)
      pr->bf--;
    else
      pr->bf++;
    if (pr->bf == 0)
      break;  //插入后父结点平衡因子为0，无需调整，直接退出
    if (abs(pr->bf) == 1)
      p = pr;  //插入后父结点平衡因子为1，回溯判断
    if (abs(pr->bf) == 2) {
      lable = (pr->bf < 0) ? -1 : 1;  //记录父结点平衡因子符号，判断单旋还是双旋
      if (p->bf == lable)  //两结点平衡因子同号，单旋
      {
        if (lable == 1)
          RotateL(pr);
        else
          RotateR(pr);
      } else  //两节点平衡因子异号，双旋
      {
        if (lable == 1)
          RotateRL(pr);
        else
          RotateLR(pr);
      }
      break;
    }
  }
  if (st.empty()) {
    root = ptr = pr;
  } else  //将AVL树重新链接好
  {
    q = st.top();
    if (getEn(q) > getEn(pr)) {
      q->left = pr;
    } else {
      q->right = pr;
    }
  }
  return true;
}
