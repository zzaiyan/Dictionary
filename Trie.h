#ifndef TRIE_H
#define TRIE_H

#include <vector>
#include "wNode.h"
using std::vector;

constexpr int MAXN = 5e5 + 5;

class Trie {
  int nex[MAXN][26], cnt = 0;
  int exist[MAXN];  // 该结点结尾的字符串是否存在
  vector<wNode> vec;

 public:
  Trie(const vector<wNode>& v) : vec(v) {
    for (int i = 0; i < vec.size(); i++)
      insert(vec[i].en, i);
  }

  void insert(char* s, int l, int val) {  // 插入字符串
    int p = 0;
    for (int i = 0; i < l; i++) {
      int c = s[i] - 'a';
      if (!nex[p][c])
        nex[p][c] = ++cnt;  // 如果没有，就添加结点
      p = nex[p][c];
    }
    exist[p] = val + 1;
  }

  void insert(const QString& s, int val) {
    insert(s.toStdString().data(), s.length(), val);
  }

  int find(char* s, int l) {  // 查找字符串
    if (l <= 0)
      return 0;
    int p = 0;
    //    wCmp = 0;w
    for (int i = 0; i < l; i++) {
      wCmp++;
      int c = s[i] - 'a';
      if (nex[p][c] == 0) {
        return 0;
      }
      p = nex[p][c];
    }
    //    qDebug() << QString("exist[%1] = %2").arg(p).arg(exist[p]);
    int r = exist[p];

    return r > 0 ? r : find(s, l - 1);
  }

  int find(const QString& s) {
    return find(s.toStdString().data(), s.length());
  }
};

#endif  // TRIE_H
