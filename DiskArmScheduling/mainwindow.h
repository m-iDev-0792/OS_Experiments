#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <vector>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QGraphicsTextItem>
#include <QDebug>
#include <QPixmap>
#include <random>
#include <ctime>
#include <functional>
#include "mypicitem.h"
#include "headstateitem.h"
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
  void getResultUsingSSTF(vector<int> tasks,int defaultPos);
  void getResultUsingSCAN(vector<int> tasks,int defaultPos,int direction);
private slots:
  void on_run_clicked();

  void on_setting_clicked();

  void on_SCAN_clicked();

  void on_leftDirection_clicked();

  void on_rightDirection_clicked();

  void on_SSTF_clicked();

  void on_play_clicked();

  void on_random_clicked();

private:
  Ui::MainWindow *ui;
  vector<int> tasks;
  int direction;
  QGraphicsScene* scene;
  QGraphicsView* view;
  MyPicItem* disk;
  MyPicItem* head;
  vector<int> paintQueue;
  int currentDiskTrack;
  int textIndex;
  int defaultPos;
  HeadStateItem* headStateText;
signals:
  void sendResult(vector<int> paintQueue,int defaultPos,int totalMovement);
public slots:
  void updateDiskTrackText();
};

#endif // MAINWINDOW_H
