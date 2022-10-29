#ifndef WNODE_H
#define WNODE_H

#include <QString>
extern int wCmp;

struct wNode {
  QString en, zh;
  bool operator<(const wNode& b) const {
    wCmp++;
    return en < b.en;
  }
};

struct rbNode {
  QString data;
  bool operator<(const rbNode& b) const {
    wCmp++;
    return data < b.data;
  }
};

#endif  // WNODE_H
