#ifndef RBTREE_H
#define RBTREE_H

#include <iomanip>
#include <iostream>
using namespace std;

// 基本定义
enum RBTColor { RED, BLACK };
template <class T>
class RBTNode {
 public:
  RBTColor color;   // 颜色
  T key;            // 键值
  RBTNode* left;    // 左孩子
  RBTNode* right;   // 右孩子
  RBTNode* parent;  // 父节点
  RBTNode(T value, RBTColor c, RBTNode* p, RBTNode* l, RBTNode* r)
      : key(value), color(c), parent(p), left(l), right(r) {}
};

template <class T>
class RBTree {
 private:
  RBTNode<T>* mRoot;

 public:
  RBTree();
  ~RBTree();
  // 前序遍历
  void preOrder();
  // 中序遍历
  void inOrder();
  // 后序遍历
  void postOrder();
  RBTNode<T>* iterativeSearch(T key);
  // (递归实现)查找”红黑树“中键值为key的节点
  RBTNode<T>* search(T key);
  // 查找最小节点：返回最小节点的键值
  T minimum();
  // 查找最大节点：返回最大节点的键值
  T maximum();
  // 将节点（key为节点键值）插入到红黑树中
  void insert(T key);
  // 删除节点（key为节点键值）
  void remove(T key);
  // 销毁红黑树
  void destroy();
  // 打印红黑树
  void print();

 private:
  // 前序遍历”红黑树“
  void preOrder(RBTNode<T>* tree) const;
  // 中序遍历”红黑树“
  void inOrder(RBTNode<T>* tree) const;
  // 后续遍历“红黑树”
  void postOrder(RBTNode<T>* tree) const;

  // (递归实现)查找”红黑树“中键值为key的节点
  RBTNode<T>* search(RBTNode<T>* x, T key) const;
  // (非递归实现)查找”红黑树“中键值为key的节点
  RBTNode<T>* iterativeSearch(RBTNode<T>* x, T key) const;

  // 查找最小节点：返回最小节点的键值
  RBTNode<T>* minimum(RBTNode<T>* tree);
  // 查找最大节点：返回最大节点的键值
  RBTNode<T>* maximum(RBTNode<T>* tree);

  // 查找节点(X)的后继节点，即查找在红黑树中大于该节点值的最小节点
  RBTNode<T>* successor(RBTNode<T>* x);
  // 查找节点(X)的前驱节点，即查找在红黑树中小于该节点值的最大节点
  RBTNode<T>* predecessor(RBTNode<T>* x);

  // 左旋
  void leftRotate(RBTNode<T>*& root, RBTNode<T>* x);
  // 右旋
  void rightRotate(RBTNode<T>*& root, RBTNode<T>* y);
  // 插入函数
  void insert(RBTNode<T>*& root, RBTNode<T>* node);
  // 插入修正函数
  //	void insertFixUp(RBTNode<T>*&root, RBTNode<T>* node, RBTNode<T>*
  // parent);
  void insertFixUp(RBTNode<T>*& root, RBTNode<T>* node);
  // 删除的修正函数
  void removeFixUp(RBTNode<T>*& root, RBTNode<T>* node, RBTNode<T>* parent);
  // 查找需要替代删除的节点
  RBTNode<T>* findReplaceNode(RBTNode<T>* node);
  // 查找需要替代的节点，真实的节点替代
  RBTNode<T>* findReplaceNode2(RBTNode<T>*& root, RBTNode<T>* node);
  RBTNode<T>* exchange_node(RBTNode<T>*& root,
                            RBTNode<T>* node1,
                            RBTNode<T>* node2);
  // 因插入或删除节点引起父节点与子节点为两个红色，造成错误的结构
  void fixUpNode(RBTNode<T>*& root, RBTNode<T>* node);

  // 销毁红黑树
  void destroy(RBTNode<T>*& tree);
  // 打印红黑树
  void print(RBTNode<T>*& tree, T key, int direction);

#define rb_parent(r) ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r) ((r)->color == RED)
#define rb_is_black(r) ((r)->color == BLACK)
#define rb_set_black(r) \
  do {                  \
    (r)->color = BLACK; \
  } while (0)
#define rb_set_red(r) \
  do {                \
    (r)->color = RED; \
  } while (0)
#define rb_set_parent(r, p) \
  do {                      \
    (r)->parent = (p);      \
  } while (0)
#define rb_set_color(r, c) \
  do {                     \
    (r)->color = (c);      \
  } while (0)
};
/**
 *构造函数
 */
template <class T>
RBTree<T>::RBTree() : mRoot(NULL) {
  // mRoot = NULL;
}
/**
 * 析构函数
 */
template <class T>
RBTree<T>::~RBTree() {
  destroy();
}
/**
 * 前序遍历”红黑树“
 */
template <class T>
void RBTree<T>::preOrder(RBTNode<T>* tree) const {
  if (tree != NULL) {
    cout << tree->key << " ";
    preOrder(tree->left);
    preOrder(tree->right);
  }
}
template <class T>
void RBTree<T>::preOrder() {
  this->preOrder(mRoot);
}
/**
 * 中序遍历”红黑树“
 */
template <class T>
void RBTree<T>::inOrder(RBTNode<T>* tree) const {
  if (tree != NULL) {
    inOrder(tree->left);
    cout << tree->key << " ";
    inOrder(tree->right);
  }
}
template <class T>
void RBTree<T>::inOrder() {
  this->inOrder(mRoot);
}
/**
 * 后序遍历”红黑树“
 */
template <class T>
void RBTree<T>::postOrder(RBTNode<T>* tree) const {
  if (tree != NULL) {
    postOrder(tree->left);
    postOrder(tree->right);
    cout << tree->key << " ";
  }
}
template <class T>
void RBTree<T>::postOrder() {
  this->postOrder(mRoot);
}

/**
 * (递归实现)查找”红黑树“中键值为key的节点
 */
template <class T>
RBTNode<T>* RBTree<T>::search(RBTNode<T>* x, T key) const {
  if (x == NULL || x->key == key) {
    return x;
  }
  if (key < x->key) {
    return search(x->left, key);
  } else {
    return search(x->right, key);
  }
}
template <class T>
RBTNode<T>* RBTree<T>::search(T key) {
  return search(mRoot, key);
}
// (非递归实现)查找”红黑树“中键值为key的节点
template <class T>
RBTNode<T>* RBTree<T>::iterativeSearch(RBTNode<T>* x, T key) const {
  while (x != NULL && x->key != key) {
    if (key < x->key) {
      return iterativeSearch(x->left, key);
    } else {
      return iterativeSearch(x->right, key);
    }
  }
  return x;
}
template <class T>
RBTNode<T>* RBTree<T>::iterativeSearch(T key) {
  return iterativeSearch(mRoot, key);
}
/**
 * 查找最小节点：返回最小节点的键值
 */
template <class T>
RBTNode<T>* RBTree<T>::minimum(RBTNode<T>* tree) {
  if (tree == NULL) {
    return NULL;
  }
  while (tree->left != NULL) {
    tree = tree->left;
  }
  return tree;
}
template <class T>
T RBTree<T>::minimum() {
  RBTNode<T>* p = minimum(mRoot);
  if (p != NULL) {
    return p->key;
  }
  return 0;
}
/**
 * 查找最大节点：返回最大节点的键值
 */
template <class T>
RBTNode<T>* RBTree<T>::maximum(RBTNode<T>* tree) {
  if (tree == NULL) {
    return NULL;
  }
  while (tree->right != NULL) {
    tree = tree->right;
  }
  return tree;
}
template <class T>
T RBTree<T>::maximum() {
  RBTNode<T>* p = maximum(mRoot);
  if (p != NULL) {
    return p->key;
  }
  return 0;
}

/**
 * 查找节点(X)的后继节点，即查找在红黑树中大于该节点值的最小节点
 */
template <class T>
RBTNode<T>* RBTree<T>::successor(RBTNode<T>* x) {
  // 如果x存在右孩子，则x的后继节点为其右孩子作为根节点子树的最小节点
  if (x->right != NULL) {
    return minimum(x->right);
  }
  // 如果x没有右孩子，则x有一下两种可能
  // 1.x是父节点的左孩子，则x的后继节点为父节点
  // 2.x是父节点的右孩子，则需要循环查找x的最低父节点，并且该父节点具有左孩子
  RBTNode<T>* y = x->parent;
  while (y != NULL && x != y->left) {
    x = y;
    y = y->parent;
  }
  return y;
}
/**
 * 查找节点(X)的前驱节点，即查找在红黑树中小于该节点值的最大节点
 */
template <class T>
RBTNode<T>* RBTree<T>::predecessor(RBTNode<T>* x) {
  // 如果x存在左孩子，则x的后继节点为其右孩子作为根节点子树的最大节点
  if (x->left != NULL) {
    return maximum(x->left);
  }
  // 如果x没有左孩子，则x有一下两种可能
  // 1.x是父节点的右孩子，则x的后继节点为父节点
  // 2.x是父节点的左孩子，则需要循环查找x的最低父节点，并且该父节点具有右孩子
  RBTNode<T>* y = x->parent;
  while (y != NULL && x != y->right) {
    x = y;
    y = y->parent;
  }
  return y;
}

/**
左旋
                 px
px /	         对x进行左旋转                 / x             ------------> y
          / \										 /
\ lx  y                                      x   ry
                / \ 								   / \
           ly  ry lx ly
*/

template <class T>
void RBTree<T>::leftRotate(RBTNode<T>*& root, RBTNode<T>* x) {
  // 设置x的右孩子y
  RBTNode<T>* y = x->right;
  // 将y的左孩子设为x的右孩子
  // 如果y的左孩子非空，将x设为y的左孩子的父亲
  x->right = y->left;
  if (y->left != NULL) {
    y->left->parent = x;
  }
  // 将x的父节点设置为y的父节点
  y->parent = x->parent;
  if (x->parent == NULL) {
    root = y;  // 如果x的父节点为空，则将y设为根节点
  } else {
    if (x->parent->left == x) {
      x->parent->left =
          y;  // 如果x是他父节点的左孩子，则将y设为x的父节点的左孩子
    } else {
      x->parent->right =
          y;  // 如果x是他父节点的右孩子，则将y设为x的父节点的右孩子
    }
  }
  // 将x设为y的左孩子
  y->left = x;
  // 将x的父节点设为y
  x->parent = y;
}
/**
右旋转
                        py
py /							   / y
x
                 / \	  对y进行右旋转 		 / \
                x   ry    ------------>     	lx  y
           / \								   / \
          lx  rx							  rx  ry
*/
template <class T>
void RBTree<T>::rightRotate(RBTNode<T>*& root, RBTNode<T>* y) {
  // 获取节点x
  RBTNode<T>* x = y->left;
  // 如果x的右孩子非空,则将x的右孩子设置为y的左孩子
  y->left = x->right;
  if (x->right != NULL) {
    x->right->parent = y;
  }
  // 将x的父节点指向y的父节点
  x->parent = y->parent;
  if (y->parent == NULL) {
    root = x;  // 如果y为根节点，则将x变为新的根节点
  } else {
    if (y->parent->left == y) {
      y->parent->left = x;  // 如果y为父节点的左孩子，则将x设置为父节点的左孩子
    } else {
      y->parent->right = x;  // 如果y为父节点的右孩子，则将x设置为父节点的右孩子
    }
  }
  y->parent = x;  // 将y的父节点设置为x
  x->right = y;   // 将x的右孩子设置为y
}

/**
红黑树插入修正函数
在向红黑树中插入节点之后（失去平衡），再调用该函数 ；
目的是将它重新塑造成一颗红黑树
参数说明：
        root 红黑树的根
        node 插入的节点
*/
//#define rb_parent(r) ((r)->parent)
//#define rb_color(r) ((r)->color)
//#define rb_is_red(r) ((r)->color == RED)
//#define rb_is_black(r) ((r)->color == BLACK)
//#define rb_set_black(r) do{(r)->color = BLACK;}while(0)
//#define rb_set_red(r) do{(r)->color = RED;}while(0)
//#define rb_set_parent(r, p) do{(r)->parent=(p);}while(0)
//#define rb_set_color(r,c) do{(r)->color = (c);}while(0)
/**
        初始插入节点是红色
        1.插入位置为根，直接染黑
        2.父亲节点如果是黑色，则不需要染色或者旋转
        3.父亲节点是红色，叔叔节点也是红色。父亲和叔叔节点染成黑色，爷爷染成红色，
          把爷爷看成新插入的节点，循环向上插入
        4.父亲节点是红色，叔叔节点是黑色。
                （1）当前节点是其父节点的左节点且父节点是祖父节点的左孩子，
                         则父节点右旋转，父节点变黑，祖父节点变红，父节点的右子树变为祖父节点的左子树。
                （2）当前节点是其父节点的右孩子且父节点是祖父节点的右孩子，
                         则父节点左旋，父节点变黑，祖父节点变红，父节点的左孩子变为祖父节点的右孩子。
        5. 父亲节点是红色，叔叔节点是黑色
                （1） 当前节点是其父节点的右节点且父节点是祖父节点的左节点，
                          则先以父节点进行左旋转，再以祖父节点右旋转【4.1】
                （2） 当前节点是父节点的左节点且父节点是祖父节点的右节点，
                          则先以父节点右旋转，再以祖父节点左旋转【4.2】
*/
template <class T>
void RBTree<T>::insertFixUp(RBTNode<T>*& root, RBTNode<T>* node) {
  // 定义父节点和祖父节点
  RBTNode<T>* parent;
  RBTNode<T>* gparent;
  RBTNode<T>* uncle;
  parent = rb_parent(node);
  // 1.插入位置为根，直接染黑
  if (parent == NULL) {
    rb_set_black(node);
    root = node;
    return;
  }
  // 2.父亲节点如果是黑色，则不需要染色或者旋转
  if (rb_is_black(parent)) {
    return;
  }
  RBTNode<T>* curNode = node;
  parent = rb_parent(curNode);
  while (parent != NULL && rb_is_red(parent)) {
    gparent = rb_parent(parent);
    // 先讨论父节点是祖父节点左孩子的情况
    if (parent == gparent->left) {
      uncle = gparent->right;
      if (uncle == NULL || rb_is_black(uncle)) {
        if (curNode == parent->right) {
          // 5.若插入节点为父节点的右孩子，且父节点为红色，叔叔节点为黑色，
          // 则先根据父节点左转，（再根据祖父右转，将当前染黑，祖父染红）跳转到4
          leftRotate(root, parent);
          curNode = parent;
          parent = rb_parent(curNode);
        }
        if (curNode == parent->left) {
          // 4.父节点为祖父节点的左孩子，若插入的节点的父节点为红色且为父节点的左孩子，叔叔节点为黑色，
          // 则根据祖父节点右旋，将父节点染黑，祖父染红
          rightRotate(root, gparent);
          rb_set_black(parent);  // 将父节点染黑
          rb_set_red(gparent);   // 将祖父节点染红
          break;
        }
      }
    }  // 父节点是祖父节点右孩子的情况
    else {
      uncle = gparent->left;
      if (uncle == NULL || rb_is_black(uncle)) {
        if (curNode == parent->left) {
          // 7.父节点为祖父节点的右孩子，若插入节点为父节点的左孩子，且父节点为红色，叔叔节点为黑色，
          // 则先根据父节点右转，（再根据祖父左转，将当前染黑，祖父染红）跳转到6
          rightRotate(root, parent);
          curNode = parent;
          parent = rb_parent(curNode);
        }
        if (curNode == parent->right) {
          // 6.父节点为祖父节点的右孩子，若父节点为红色且插入节点为父节点的右孩子，叔叔节点为黑色，
          //则根据祖父左旋，将父节点染黑，祖父染红
          leftRotate(root, gparent);
          rb_set_black(parent);  // 将父节点染黑
          rb_set_red(gparent);   // 将祖父节点染红
          break;
        }
      }
    }
    // 3.父亲节点是红色，叔叔节点也是红色。父亲和叔叔节点染成黑色，
    //   爷爷染成红色，把爷爷看成新插入的节点，循环向上插入
    if (uncle != NULL && rb_is_red(uncle)) {
      rb_set_black(parent);  // 将父节点染黑
      rb_set_black(uncle);   // 将叔叔节点染黑
      rb_set_red(gparent);   // 将祖父节点染红
      curNode = gparent;
      parent = rb_parent(curNode);
    }
  }
  // 将根节点设为黑色
  rb_set_black(root);
}
// 插入函数
/**
 * 将节点插入到红黑树中
 * root : 红黑树的根节点
 * node : 插入的节点
 */
template <class T>
void RBTree<T>::insert(RBTNode<T>*& root, RBTNode<T>* node) {
  RBTNode<T>* y = NULL;
  RBTNode<T>* x = root;
  node->left = NULL;
  node->right = NULL;
  // 1. 将红黑树当作一颗二叉查找树，将节点添加到二叉树中
  while (x != NULL) {
    y = x;
    if (node->key < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  node->parent = y;
  if (y != NULL) {
    if (node->key < y->key) {
      y->left = node;
    } else {
      y->right = node;
    }
  } else {
    root = node;
  }
  // 2.设置节点的颜色为红色
  node->color = RED;
  // 3.将它重新修正为一颗红黑树
  insertFixUp(root, node);
}
/**
 * 将节点（key为节点键值）插入到红黑树中
 * 参数说明
 * key ：插入点的键值
 */
template <class T>
void RBTree<T>::insert(T key) {
  RBTNode<T>* z = NULL;
  // 如果新建节点失败，则返回
  if ((z = new RBTNode<T>(key, RED, NULL, NULL, NULL)) == NULL) {
    return;
  }
  insert(mRoot, z);
}
/**
 红黑树删除修正函数
 在从红黑树中删除插入节点之后（红黑树失去平衡），再调用该函数，目的是将它重新塑造成一颗红黑树
 参数说明：
 root : 红黑树的根
 node : 待修正的节点
删除操作：
主题思想是：若删除的节点不是叶子节点，则可以查找该节点的后继节点的值将其代替，再删除替代它的节点，因为后继节点一般是叶节点，
                        则删除操作可以简化为对叶节点进行操作。
        1.叶节点是红色，直接删除
        2.
*/

// 查找需要替代删除的节点 ,叶子节点即可
template <class T>
RBTNode<T>* RBTree<T>::findReplaceNode(RBTNode<T>* node) {
  // 1.node本身就是叶子节点
  // 2.node存在左孩子或者右孩子
  RBTNode<T>* curNode = node;
  RBTNode<T>* preNode = node;
  while (curNode->left != NULL || curNode->right != NULL) {
    // 先找后继节点
    if (curNode->right != NULL) {
      curNode = this->successor(curNode);
    }
    preNode->key = curNode->key;
    preNode = curNode;
    // 查找前驱节点
    if (curNode->left != NULL) {
      curNode = this->predecessor(curNode);
    }
    preNode->key = curNode->key;
    preNode = curNode;
  }
  return curNode;
}
/**
 * 交换两个节点
 */
template <class T>
RBTNode<T>* RBTree<T>::exchange_node(RBTNode<T>*& root,
                                     RBTNode<T>* preNode,
                                     RBTNode<T>* curNode) {
  RBTNode<T>* cur_p = NULL;
  RBTNode<T>* cur_l = NULL;
  RBTNode<T>* cur_r = NULL;
  RBTColor cur_rb;
  RBTNode<T>* pre_p = NULL;
  RBTNode<T>* pre_l = NULL;
  RBTNode<T>* pre_r = NULL;
  RBTColor pre_rb;

  cur_p = curNode->parent;
  cur_l = curNode->left;
  cur_r = curNode->right;
  cur_rb = curNode->color;
  pre_p = preNode->parent;
  pre_l = preNode->left;
  pre_r = preNode->right;
  pre_rb = preNode->color;

  curNode->parent = pre_p;
  if (pre_p == NULL) {
    root = curNode;
  } else {
    if (pre_p->left == preNode) {
      pre_p->left = curNode;
    } else {
      pre_p->right = curNode;
    }
  }
  // 1.curNode是preNode的子节点
  if (cur_p == preNode) {
    preNode->parent = curNode;
    preNode->left = cur_l;
    preNode->right = cur_r;
    if (preNode->left == curNode) {
      curNode->left = preNode;
      curNode->right = pre_r;
    } else {
      curNode->right = preNode;
      curNode->left = pre_l;
    }
  }  // 2.curNode不是preNode的子节点
  else {
    // curNode节点的左孩子
    curNode->left = pre_l;
    if (pre_l != NULL) {
      pre_l->parent = curNode;
    }
    // curNode节点的右孩子
    curNode->right = pre_r;
    if (pre_r != NULL) {
      pre_r->parent = curNode;
    }
    // preNode节点的父节点
    preNode->parent = cur_p;
    if (cur_p->left == curNode) {
      cur_p->left = preNode;
    } else {
      cur_p->right = preNode;
    }
    // preNode节点的左孩子
    preNode->left = cur_l;
    if (cur_l != NULL) {
      cur_l->parent = preNode;
    }
    // preNode节点的右孩子
    preNode->right = cur_r;
    if (cur_r != NULL) {
      cur_r->parent = preNode;
    }
  }
  curNode->color = pre_rb;
  preNode->color = cur_rb;
  return preNode;
}

// 查找需要替代的节点，真实的节点替代
template <class T>
RBTNode<T>* RBTree<T>::findReplaceNode2(RBTNode<T>*& root, RBTNode<T>* node) {
  // 1.node本身就是叶子节点
  // 2.node存在左孩子或者右孩子
  RBTNode<T>* curNode = node;
  RBTNode<T>* preNode = node;
  RBTNode<T>* p = NULL;
  RBTNode<T>* l = NULL;
  RBTNode<T>* r = NULL;
  RBTNode<T>* preParent = NULL;
  RBTColor rb;
  while (curNode->left != NULL || curNode->right != NULL) {
    // 先找后继节点
    if (curNode->right != NULL) {
      curNode = this->successor(curNode);
    }
    if (curNode != preNode) {
      curNode = exchange_node(root, preNode, curNode);
    }
    // 查找前驱节点
    if (curNode->left != NULL) {
      curNode = this->predecessor(curNode);
    }
    if (curNode != preNode) {
      curNode = exchange_node(root, preNode, curNode);
    }
  }
  return curNode;
}

// 因插入或删除节点引起父节点与子节点为两个红色，造成错误的结构
template <class T>
void RBTree<T>::fixUpNode(RBTNode<T>*& root, RBTNode<T>* node) {
  if (node != NULL) {
    fixUpNode(root, node->left);
    fixUpNode(root, node->right);
    this->insert(root, node);
  }
}

//#define rb_parent(r) ((r)->parent)
//#define rb_color(r) ((r)->color)
//#define rb_is_red(r) ((r)->color == RED)
//#define rb_is_black(r) ((r)->color == BLACK)
//#define rb_set_black(r) do{(r)->color = BLACK;}while(0)
//#define rb_set_red(r) do{(r)->color = RED;}while(0)
//#define rb_set_parent(r, p) do{(r)->parent=(p);}while(0)
//#define rb_set_color(r,c) do{(r)->color = (c);}while(0)

template <class T>
void RBTree<T>::removeFixUp(RBTNode<T>*& root,
                            RBTNode<T>* node,
                            RBTNode<T>* parent) {
  RBTNode<T>* x =
      this->findReplaceNode2(root, node);  // 将删除的节点转移到叶子节点
  //	RBTNode<T>* x = this->findReplaceNode(node); //
  //将删除的节点转移到叶子节点
  RBTNode<T>* p = rb_parent(x);
  RBTNode<T>* y = NULL;
  RBTNode<T>* l = NULL;
  RBTNode<T>* r = NULL;
  // 判断是否删除最后一个节点了
  if (p == NULL) {
    delete x;
    root = NULL;
    return;
  }
  // 先判断删除的叶子节点为父节点的左孩子情况
  if (x == p->left) {
    y = p->right;  // x的兄弟节点
    if (y != NULL) {
      l = y->left;
      r = y->right;
    }
    // 删除的节点为黑色节点
    if (rb_is_black(x)) {
      p->left = NULL;
      delete x;
      // X的兄弟节点y为黑色
      if (rb_is_black(y)) {
        // 2.删除的节点x为黑色，且其兄弟节点Y为叶节点且为黑色，则将x删除，p变为黑色，Y变为红色
        if (l == NULL && r == NULL) {
          rb_set_black(p);
          rb_set_red(y);
        } else if (l != NULL && rb_is_red(l) && r == NULL) {
          // 3.节点x与Y为黑色，节点X的兄弟节点Y，只包含左孩子L且为红色，则删除节点X后，
          // 需要先根据Y右旋，再据P左旋，将L变为P的颜色，再将P染黑
          rightRotate(root, y);  // 根据y右旋
          leftRotate(root, p);   // 根据p左旋
          l->color = p->color;
          rb_set_black(p);
        } else if (l == NULL && r != NULL && rb_is_red(r)) {
          //  4.节点X与Y为黑色，节点X的兄弟节点Y，只包含右孩子R且为红色，
          // 则删除节点X后，据P左旋，再将Y变为P的颜色，将P和R染黑。
          leftRotate(root, p);  // 根据p左旋
          y->color = p->color;
          rb_set_black(p);
          rb_set_black(r);
        } else if (l != NULL && r != NULL && rb_is_red(r) && rb_is_red(l)) {
          // 5.节点X和其兄弟节点Y都为黑色，Y的左孩子与右孩子都为红色，
          // 将节点X删除，再根据P进行左旋，再将Y变为P的颜色，P和R变黑
          leftRotate(root, p);  // 根据p左旋
          y->color = p->color;
          rb_set_black(p);
          rb_set_black(r);
        }
      } else {
        // 6.
        // 被删除的节点X为黑色，其兄弟节点Y为红色，则Y的左孩子与右孩子为黑色。
        // 删除节点X，在根据P进行左旋，再将Y染黑，L染红
        if (l != NULL && r != NULL && rb_is_black(r) && rb_is_black(l)) {
          leftRotate(root, p);  // 根据p左旋
          rb_set_black(y);
          rb_set_red(l);
          l->left = NULL;
          l->right = NULL;
          fixUpNode(root, l->left);
          fixUpNode(root, l->right);
        }
      }
    } else {
      // 1. 删除节点为红色，不管是父节点的左孩子还是右孩子，则直接删除
      p->left = NULL;
      delete x;
    }
  }  // 再判断删除的叶子节点为父节点的右孩子情况
  else {
    y = p->left;  // x的兄弟节点
    if (y != NULL) {
      l = y->left;
      r = y->right;
    }
    // 删除的节点为黑色节点
    if (rb_is_black(x)) {
      p->right = NULL;
      delete x;
      // X的兄弟节点y为黑色
      if (rb_is_black(y)) {
        // 2.删除的节点x为黑色，且其兄弟节点Y为叶节点且为黑色，则将x删除，p变为黑色，Y变为红色
        if (l == NULL && r == NULL) {
          rb_set_black(p);
          rb_set_red(y);
        } else if (l != NULL && rb_is_red(l) && r == NULL) {
          // 3.节点x与Y为黑色，节点X的兄弟节点Y，只包含左孩子L且为红色，则删除节点X后，
          // P右旋，将Y变为P的颜色，P和L染黑
          rightRotate(root, p);  // 根据p右旋
          y->color = p->color;
          rb_set_black(p);
          rb_set_black(l);
        } else if (l == NULL && r != NULL && rb_is_red(r)) {
          // 4.
          // 节点X为父节点的右节点，节点X与Y为黑色，且节点X的兄弟节点Y只包含右孩子R且为红色，
          //则删除节点X后，需要先根据Y左旋，再据P右旋，将R变为P的颜色，再将P染黑
          leftRotate(root, y);   // 根据p左旋
          rightRotate(root, p);  // 根据p左旋
          r->color = p->color;
          rb_set_black(p);
        } else if (l != NULL && r != NULL && rb_is_red(r) && rb_is_red(l)) {
          // 5.节点X为父节点的右节点，节点X和其兄弟节点Y都为黑色，Y的左孩子与右孩子都为红色，将节点X删除，
          // 再根据P进行右旋，再将Y变为P的颜色，P和L变黑
          rightRotate(root, p);  // 根据p左旋
          y->color = p->color;
          rb_set_black(p);
          rb_set_black(l);
        }
      } else {
        // 6.节点X为父节点的右孩子，被删除的节点X为黑色，其兄弟节点Y为红色，则Y的左孩子与右孩子为黑色。
        // 删除节点X，在根据P进行右旋，再将Y染黑，R染红
        if (l != NULL && r != NULL && rb_is_black(r) && rb_is_black(l)) {
          rightRotate(root, p);  // 根据p左旋
          rb_set_black(y);
          rb_set_red(r);
          r->left = NULL;
          r->right = NULL;
          fixUpNode(root, r->left);
          fixUpNode(root, r->right);
        }
      }
    } else {
      // 1. 删除节点为红色，不管是父节点的左孩子还是右孩子，则直接删除
      p->right = NULL;
      delete x;
    }
  }
}
// 删除节点（key为节点键值）
template <class T>
void RBTree<T>::remove(T key) {
  RBTNode<T>* node;
  // 查找key对应的节点node，找到的话就删除该节点
  if ((node = search(mRoot, key)) != NULL) {
    removeFixUp(mRoot, node, NULL);
  }
}
/**
 * 销毁红黑树
 */
template <class T>
void RBTree<T>::destroy(RBTNode<T>*& tree) {
  if (tree == NULL) {
    return;
  }
  destroy(tree->left);
  destroy(tree->right);
  delete tree;
  tree = NULL;
}
template <class T>
void RBTree<T>::destroy() {
  destroy(mRoot);
}
/**
* 打印二叉查找树
 key 节点的键值
 direction    0 表示该节点是根节点
                          -1 表示该节点是它的父节点的左孩子
                          1  表示该节点是它父节点的右孩子
*/
template <class T>
void RBTree<T>::print(RBTNode<T>*& tree, T key, int direction) {
  if (tree != NULL) {
    if (direction == 0) {  // tree是根节点
      cout << setw(2) << tree->key << "(B) is root" << endl;
    } else {
      cout << setw(2) << tree->key << (rb_is_red(tree) ? "(R)" : "(B)")
           << " is " << setw(2) << key << " 's " << setw(12)
           << (direction == 1 ? "right child" : "left child") << endl;
    }
    print(tree->left, tree->key, -1);
    print(tree->right, tree->key, 1);
  }
}
template <class T>
void RBTree<T>::print() {
  if (mRoot != NULL) {
    print(mRoot, mRoot->key, 0);
  }
}
int main() {
  //	cout << "hello1111" << endl;
  int a[] = {10, 40, 30, 60, 90, 70, 20, 50, 80};
  int check_insert = 0;  // “插入”动作的检测开关（0，关闭；1，打开）
  int check_remove = 0;  // “删除”动作的检测开关（0，关闭；1，打开）
  int i;
  int len = (sizeof(a)) / sizeof(a[0]);
  RBTree<int>* tree = new RBTree<int>();
  cout << "====原始数据：";
  for (i = 0; i < len; i++) {
    cout << a[i] << " ";
  }
  cout << endl;
  for (i = 0; i < len; i++) {
    tree->insert(a[i]);
    // 设置check_insert=1，测试“添加函数”
    if (check_insert) {
      cout << "==添加节点：" << a[i] << endl;
      cout << "==树的详细信息：" << endl;
      tree->print();
      cout << endl;
    }
  }
  cout << "==前序遍历：";
  tree->preOrder();
  cout << endl;
  cout << "==中序遍历：";
  tree->inOrder();
  cout << endl;
  cout << "==后序遍历：";
  tree->postOrder();
  cout << endl;
  cout << "==最小值：" << tree->minimum() << endl;
  cout << "==最大值：" << tree->maximum() << endl;
  cout << "==树的详细信息：" << endl;
  tree->print();
  cout << endl;
  // 设置check_remove = 1，测试“删除函数”
  check_remove = 1;
  if (check_remove) {
    for (i = 0; i < len; i++) {
      tree->remove(a[i]);
      cout << "==删除节点：" << a[i] << endl;
      cout << "==树的详细s信息：" << endl;
      tree->print();
      cout << endl;
    }
  }
  //	int b = 0;
  //	b = 10;
  //	tree->remove(b);
  //	b = 40;
  //	tree->remove(b);
  //	b = 30;
  //	cout << "==删除节点：" << b << endl;
  //	cout << "==树的详细信息：" << endl;
  //	tree->remove(b);
  //	tree->print();
  //	cout << endl;
  // 销毁红黑树
  tree->destroy();
  return 0;
}

#endif  // RBTREE_H
