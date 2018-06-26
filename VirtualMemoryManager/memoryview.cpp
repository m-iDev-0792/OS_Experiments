#include "memoryview.h"

MemoryView::MemoryView(QWidget *parent) : QWidget(parent)
{
  mode=0;
}
void MemoryView::paintEvent(QPaintEvent *e){
  QStyleOption opt;
  opt.init(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
  if(memories.empty())return;
  float boxHeight=(float)(height()-vertGap*(memories.size()+1))/memories.size();
  int boxWidth=width()-2*horiGap;
  int oldest=100000;
  int oldestIndex=0;
  int recent=-1;
  int recentIndex=0;
  for(int i=0;i<memories.size();++i){
      p.drawRect(horiGap,i*(boxHeight+vertGap)+vertGap,boxWidth,boxHeight);
      auto m=memories.at(i);
      QString msg=QString("内存页%1 逻辑页%4 装载时间%2 最近使用时间%3 ").arg(m.id==-1?tr("无"):QString::number(m.id)).arg(m.loadTime==-1?tr("无"):QString::number(m.loadTime)).arg(m.lastUsedTime==-1?tr("无"):QString::number(m.lastUsedTime)).arg(m.storedPage==-1?tr("无"):QString::number(m.storedPage));
      p.drawText(horiGap+2,i*(boxHeight+vertGap)+vertGap+15,msg);
      if(mode==0){
          if(m.loadTime<oldest){
              oldest=m.loadTime;
              oldestIndex=i;
            }
        }else{
          if(m.lastUsedTime<oldest){
              oldest=m.loadTime;
              oldestIndex=i;
            }
        }

      if(m.lastUsedTime>recent){
          recent=m.lastUsedTime;
          recentIndex=i;
        }
    }
  QPen oldPen(Qt::red);
  oldPen.setWidth(2);
  p.setPen(oldPen);
  if(memories.at(oldestIndex).loadTime>=0)
  p.drawRect(horiGap,oldestIndex*(boxHeight+vertGap)+vertGap,boxWidth,boxHeight);
  QPen recentPen(Qt::green);
  recentPen.setWidth(2);
  p.setPen(recentPen);
  if(memories.at(recentIndex).loadTime>=0)
  p.drawRect(horiGap,recentIndex*(boxHeight+vertGap)+vertGap,boxWidth,boxHeight);
}
void MemoryView::updateMemories(vector<Memory> m){
  memories=m;
  repaint();
}
