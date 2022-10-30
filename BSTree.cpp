#include "BSTree.h"

int BSTree::Search(const QString& s, BSTNode* ptr) {
  // Alert: ptr != nullptr
  wCmp++;
  if (builded) {
    qDebug() << QString("Cmp %1 with %2").arg(s).arg(getEn(ptr));
  }
  if (s < getEn(ptr) && ptr->left)
    return Search(s, ptr->left);
  if (s > getEn(ptr) && ptr->right)
    return Search(s, ptr->right);
  if (s == getEn(ptr)) {
    return ptr->num;
  }
  return -1 * ptr->num;  // Last Before Failure
}

bool BSTree::Insert(int n, BSTNode*& ptr) {
  BSTNode* pr = nullptr;
  BSTNode *p = ptr, *q;
  auto s = vec[n].en;
  stack<BSTNode*>
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
  p = new BSTNode(n);
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
  }
  if (st.empty()) {
    root = ptr = pr;
  } else {
    q = st.top();
    if (getEn(q) > getEn(pr)) {
      q->left = pr;
    } else {
      q->right = pr;
    }
  }
  return true;
}
