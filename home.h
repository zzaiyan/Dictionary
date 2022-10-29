#ifndef HOME_H
#define HOME_H

#include <bits/stdc++.h>
#include <QEvent>
#include <QLabel>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QString>
#include <QStringList>
#include <QWidget>
#include "AVLTree.h"
#include "wNode.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class Home;
}
QT_END_NAMESPACE

class Home : public QWidget {
  Q_OBJECT

 public:
  Home(QWidget* parent = nullptr);
  vector<QString> vectorForEnglish;
  vector<QString> vectorForChinese;
  bool eventFilter(QObject* watched, QEvent* event);
  QStandardItemModel* standItemModel;
  QStandardItemModel* standItemModel2;
  ~Home();
  int SearchModelChoice = 0;
  // Search
  void BasicSearch(QString s);
  void BSTSearch(QString s) {}
  void AVLSearch(QString s);
  void RBSearch(QString s);
  void TreapSearch(QString s) {}
  void TrieSearch(QString s) {}

  void Search(QString s) {
    wCmp = 0;
    switch (SearchModelChoice) {
      case 0:
        BasicSearch(s);
        break;
      case 1:
        BSTSearch(s);
        break;
      case 2:
        AVLSearch(s);
        break;
      case 3:
        RBSearch(s);
        break;
      case 4:
        TreapSearch(s);
        break;
      case 5:
        TrieSearch(s);
        break;
      default:
        break;
    };
  }
  ///////////////////////////////////////////////////////Search函数///////////////////////////////////////////////
 private slots:

  void on_comboBox_currentIndexChanged(int index);

  void on_lineEdit_textChanged(const QString& arg1);

  void on_pushButton_clicked();

  void on_tableWidget_cellDoubleClicked(int row, int column);

 private:
  Ui::Home* ui;

  int getPre(const QString& str1, const QString& str2) const;
  void record(int t);

  // Data
  vector<wNode> seq;
  AVLTree* avl;
  map<rbNode, QString> rbt;
  void build();
};
#endif  // HOME_H
