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
  void BasicSearch(QString s,
                   vector<QString>& vForEnglish,
                   vector<QString>& vForChinese) {
    for (int i = 1; i <= 10; i++) {
      vForEnglish.push_back(s + QString::number(i));
      vForChinese.push_back("12123");
    }
  }
  void BSTSearch(QString s,
                 vector<QString>& vForEnglish,
                 vector<QString>& vForChinese) {}
  void AVLSearch(QString s,
                 vector<QString>& vForEnglish,
                 vector<QString>& vForChinese);
  void RBSearch(QString s,
                vector<QString>& vForEnglish,
                vector<QString>& vForChinese) {}
  void TreapSearch(QString s,
                   vector<QString>& vForEnglish,
                   vector<QString>& vForChinese) {}
  void TrieSearch(QString s,
                  vector<QString>& vForEnglish,
                  vector<QString>& vForChinese) {}

  void Search(QString s) {
    switch (SearchModelChoice) {
      case 0:
        BasicSearch(s, vectorForEnglish, vectorForChinese);
        break;
      case 1:
        BSTSearch(s, vectorForEnglish, vectorForChinese);
        break;
      case 2:
        AVLSearch(s, vectorForEnglish, vectorForChinese);
        break;
      case 3:
        RBSearch(s, vectorForEnglish, vectorForChinese);
        break;
      case 4:
        TreapSearch(s, vectorForEnglish, vectorForChinese);
        break;
      case 5:
        TrieSearch(s, vectorForEnglish, vectorForChinese);
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

  bool havePre(const QString& str, const QString& pre);

  // Data
  vector<wNode> seq;
  AVLTree* avl;
  set<wNode> rbt;
  void build();
};
#endif  // HOME_H
