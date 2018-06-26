#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QGraphicsTextItem>
#include <QDebug>
#include <QPixmap>
#include <vector>
#include "cacheitem.h"
#include "memoryview.h"
#include "mypicitem.h"
using namespace std;
namespace Ui {
  class MainWindow;
}


class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void FIFO(int page);
  void LRU(int page);
  void playLoadPageAnimation(int index,int loadPageNum,int loadTime,int lastUsedTime,bool needKick=false);
  void shootAt(int index);
public slots:
  void makeKickUnvisible();
private slots:
  void on_setPageNum_clicked();

  void on_requestPage_clicked();

  void on_resetHistory_clicked();

  void updateMemoryInfo();

private:
  Ui::MainWindow *ui;
  vector<Memory> memories;
  int pageNum;
  int requestNum;
  QGraphicsView* view;
  QGraphicsScene* scene;
  vector<CacheItem*> caches;
  vector<QGraphicsTextItem*> storedPageTexts;
  const int chipWidth=250;
  const int chipHeight=80;
  MyPicItem* hand;
  MyPicItem* kick;
  MyPicItem* arrow;
  Memory lastVisitedMemory;
signals:
};

#endif // MAINWINDOW_H
