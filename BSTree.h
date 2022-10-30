#ifndef BSTREE_H
#define BSTREE_H

#include <QDebug>
#include <QString>
#include <queue>
#include <stack>
#include "wNode.h"
using namespace std;

struct BSTNode {
  int bf, num;
  BSTNode *left, *right, *ne;
  BSTNode() : bf(0), num(-1), left(nullptr), right(nullptr), ne(nullptr) {}
  BSTNode(int n, BSTNode* l = nullptr, BSTNode* r = nullptr)
      : bf(0), num(n), left(l), right(r), ne(nullptr) {}
};

class BSTree {
 private:
  BSTNode* root;

  const QString& getEn(BSTNode* p) { return vec[p->num].en; }
  const QString& getZh(BSTNode* p) { return vec[p->num].zh; }

 public:
  vector<wNode> vec;

  BSTree(const vector<wNode>& v) : root(nullptr), vec(v) {
    // Random Distribute
    int len = vec.size();
    for (int i = len - 1; i >= 0; --i) {
      srand(i * i * rand());
      swap(vec[rand() % (i + 1)], vec[i]);
    }
    for (int i = 0; i < len; i++)
      Insert(i);
  }
  ~BSTree(){};
  BSTNode* getRoot() { return root; }
  bool Insert(int n, BSTNode*& ptr);
  bool Insert(int n) { return Insert(n, root); }
  BSTNode* Search(const QString& s, BSTNode* ptr = nullptr);
  BSTNode* Search(const QString& s) { return Search(s, root); }
  void makeClue();
  void joinQue(BSTNode*, queue<BSTNode*>& q);

  void midOrder(BSTNode* p) {
    if (p) {
      midOrder(p->left);
      qDebug() << getEn(p) << getZh(p);
      midOrder(p->right);
    }
  }
};

#endif  // BSTREE_H
