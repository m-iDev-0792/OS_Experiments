#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <iostream>
#include <QMessageBox>
#include <QResizeEvent>
#include <queue>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QGraphicsTextItem>
#include <QDebug>
#include <QPixmap>
#include "scheduleview.h"
#include "truckitem.h"
using namespace std;
namespace Ui {
  class MainWindow;
}
struct Process{
  QString name;
  int createdTime;
  int serveTime;
  Process()=default;
  Process(QString n,int c,int s):name(n),createdTime(c),serveTime(s){}

};
struct HRNNode{
  Process p;
  float priority;
  bool operator <(const HRNNode& n)const{
    return !(priority<n.priority);
  }
  HRNNode()=default;
  HRNNode(Process _p,float _priority):p(_p),priority(_priority){}
};

struct RunResult{
  QString name;
  int finishedTime;
  int turnaroundTime;
  float weightedTurnaroundTime;
  RunResult()=default;
  RunResult(QString n,int f,int t,float w):name(n),finishedTime(f),turnaroundTime(t),weightedTurnaroundTime(w){}
};

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void addProcessToTable(QString n,QString c,QString s);
  void updateResult();
  void FCFS();
  void SJF();
  void RR(int slice);
  void HRN();
protected:
  virtual void resizeEvent(QResizeEvent *e);
private slots:
  void on_addTask_clicked();
  void on_deleteTask_clicked();
  void on_run_clicked();
private:
  Ui::MainWindow *ui;
  vector<Process> tasks;
  vector<RunResult> runResults;
  vector<RunMsg> runMsgs;
  void initLayout();

  QGraphicsView* view;
  QGraphicsScene* scene;
  void createAnimation(int slice=100086);
  QGraphicsPixmapItem* cpu;
  QGraphicsPixmapItem* parkinglotIcon;
  QGraphicsPixmapItem* banner;
  int parkingSpaceState[6];//0 means no one use it,1 means someone used it
signals:
  void sendDarwData(vector<QString> taskNames,vector<RunMsg> runMsgs);
private:
  int allocParkingSpace();
  void releaseParkingSpace(int pos);
};

#endif // MAINWINDOW_H
