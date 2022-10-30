#ifndef WNODE_H
#define WNODE_H

#include <QDebug>
#include <QString>
extern int wCmp, builded;

struct wNode {
  QString en, zh;
  bool operator<(const wNode& b) const {
    wCmp++;
    //    if (builded) {
    //      qDebug() << QString("Cmp %1 %2").arg(en).arg(b.en);
    //    }
    return en < b.en;
  }
};

struct rbNode {
  QString data;
  bool operator<(const rbNode& b) const {
    wCmp++;
    if (builded) {
      qDebug() << QString("Cmp %1 with %2").arg(data).arg(b.data);
    }
    return data < b.data;
  }
};

#endif  // WNODE_H
