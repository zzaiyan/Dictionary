#include "wNode.h"

int wCmp, builded;

void mark(const QString& a, const QString& b) {
  if (a < b)
    qDebug() << a << "<" << b;
  else if (a > b)
    qDebug() << a << ">" << b;
  else
    qDebug() << a << "==" << b;
}
