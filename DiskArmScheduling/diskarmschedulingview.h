#ifndef DISKARMSCHEDULINGVIEW_H
#define DISKARMSCHEDULINGVIEW_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include <vector>
#include <iostream>
#include <QDebug>
using namespace std;
class DiskArmSchedulingView : public QWidget
{
  Q_OBJECT
public:
  explicit DiskArmSchedulingView(QWidget *parent = nullptr);
private:
  vector<int> paintQueue;
  int defaultPos;
  int totalMovement;
signals:

public slots:
  void getResult(vector<int> _paintQueue,int _defaultPos,int _totalMovement);
protected:
  virtual void paintEvent(QPaintEvent* e);
};

#endif // DISKARMSCHEDULINGVIEW_H
