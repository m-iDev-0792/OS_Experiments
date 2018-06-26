#ifndef DISKVIEW_H
#define DISKVIEW_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <vector>
#include <iostream>
#include <QtGlobal>
#include <QDebug>
using namespace std;
struct file{
  QString fileName;
  float size;
  int startBlock;
  int blockNum;
  file(QString fn,float s,int sb,int bn):fileName(fn),size(s),startBlock(sb),blockNum(bn){}
  file(){
    startBlock=-1;
    blockNum=0;
  }
};
struct listNode{
    int blockNum;
    int startBlock;
    listNode* next;
    listNode()=default;
    listNode(int bn,int sb,listNode *n):blockNum(bn),startBlock(sb),next(n){}
};
class DiskView : public QWidget
{
  Q_OBJECT
public:
  explicit DiskView(QWidget *parent = nullptr);
  listNode const* head;
  int mode;
signals:

public slots:
  void getFileList(vector<file> &newFileList);
private:
  float horiGap;
  float vertGap;
  vector<QColor> colorList;
  vector<file> fileList;
  const int blocksize=2;
  void drawConnectLine(QPainter &p);
protected:
  virtual void paintEvent(QPaintEvent* e);
};

#endif // DISKVIEW_H
