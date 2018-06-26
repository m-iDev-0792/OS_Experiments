#ifndef SCHEDULEVIEW_H
#define SCHEDULEVIEW_H

#include <QWidget>
#include <QPainter>
#include <iostream>
#include <vector>
#include <QStyleOption>
#include <map>
struct RunMsg{
  int start;
  int end;
  QString name;
  RunMsg()=default;
  RunMsg(QString n,int s,int e):name(n),start(s),end(e){}
};

using namespace std;
class ScheduleView : public QWidget
{
  Q_OBJECT
public:
  explicit ScheduleView(QWidget *parent = nullptr);

signals:

public slots:
  virtual void paintEvent(QPaintEvent* e);
  void getDarwData(vector<QString> taskNames,vector<RunMsg> runMsgs);
private:
  vector<QString> taskNames;//进程的名字列表
  vector<RunMsg> runMsgs;//进程运行信息的列表
  map<QString,int> tasksID;//进程名字-》id的映射
  int runTimeStep;//单位时间的线长度
  const int diff=10;
};

#endif // SCHEDULEVIEW_H
