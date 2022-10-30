#ifndef AVLTREE_H
#define AVLTREE_H

#include <QDebug>
#include <QString>
#include <stack>
#include "wNode.h"
using namespace std;

struct AVLNode {
  int bf, num;
  AVLNode *left, *right;
  AVLNode() : bf(0), num(-1), left(nullptr), right(nullptr) {}
  AVLNode(int n, AVLNode* l = nullptr, AVLNode* r = nullptr)
      : bf(0), num(n), left(l), right(r) {}
};

class AVLTree {
 private:
  AVLNode* root;
  void RotateL(AVLNode*& ptr);
  void RotateR(AVLNode*& ptr);
  void RotateLR(AVLNode*& ptr);
  void RotateRL(AVLNode*& ptr);

  const QString& getEn(AVLNode* p) { return vec[p->num].en; }
  const QString& getZh(AVLNode* p) { return vec[p->num].zh; }

 public:
  vector<wNode> vec;

  AVLTree(const vector<wNode>& v) : root(nullptr), vec(v) {}
  ~AVLTree(){};
  AVLNode* getRoot() { return root; }
  bool Insert(int n, AVLNode*& ptr);
  bool Insert(int n) { return Insert(n, root); }
  int Search(const QString& s, AVLNode* ptr);
  int Search(const QString& s) { return Search(s, root); }

  void midOrder(AVLNode* p) {
    if (p) {
      midOrder(p->left);
      qDebug() << getEn(p) << getZh(p);
      midOrder(p->right);
    }
  }
};

#endif  // AVLTREE_H
