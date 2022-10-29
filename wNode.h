#ifndef WNODE_H
#define WNODE_H

#include <QString>

struct wNode {
  QString en, zh;
  bool operator<(const wNode& b) const { return en < b.en; }
};

#endif  // WNODE_H
