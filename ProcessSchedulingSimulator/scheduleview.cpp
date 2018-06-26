#include "scheduleview.h"

ScheduleView::ScheduleView(QWidget *parent) : QWidget(parent)
{
  setStyleSheet(QString("border:1px solid black;background-color:white;"));

}
void ScheduleView::paintEvent(QPaintEvent *e){
  QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    if(!runMsgs.empty()){
        int lineNum=taskNames.size()+1;
        int lineGap=height()/(lineNum+1);
        QPen baseline(Qt::gray);
        baseline.setStyle(Qt::DotLine);
        p.setPen(baseline);
        //绘制基线
        for(int i=1;i<=lineNum;++i){
            p.drawLine(0,lineGap*i,width(),lineGap*i);
          }

        //绘制运行状态线
        QPen runline(Qt::green);
        runline.setWidth(3);
        p.setPen(runline);
        for(auto& m:runMsgs){
            p.drawLine(diff+m.start*runTimeStep,tasksID[m.name]*lineGap,diff+m.end*runTimeStep,tasksID[m.name]*lineGap);
          }
        //绘制空闲时间的状态线
        QPen freeline(Qt::red);
        freeline.setWidth(3);
        p.setPen(freeline);
        //先绘制开始和结束时候的情况
        p.drawLine(2,lineNum*lineGap,runMsgs.at(0).start*runTimeStep+diff,lineNum*lineGap);
        p.drawLine(runMsgs.at(runMsgs.size()-1).end*runTimeStep+diff,lineNum*lineGap,width()-2,lineNum*lineGap);
        //绘制空闲片段
        if(runMsgs.size()>=2){
            for(int i=0;i<runMsgs.size()-1;++i){
                if(runMsgs[i].end<runMsgs[i+1].start){
                    p.drawLine(runMsgs[i].end*runTimeStep+diff,lineNum*lineGap,
                               runMsgs[i+1].start*runTimeStep+diff,lineNum*lineGap);
                  }
              }
          }
        //绘制提示文字
        QPen msgline(Qt::black);
        p.setPen(msgline);
        for(auto& n:taskNames){
            p.drawText(2,lineGap*tasksID[n]-3,n);
          }
        p.drawText(0,lineGap*lineNum-10,tr("空闲"));
        for(auto& m:runMsgs){
            //绘制开始时间坐标轴注释
            p.drawLine(diff+m.start*runTimeStep,lineNum*lineGap,
                diff+m.start*runTimeStep,lineNum*lineGap-3);
            p.drawText(8+m.start*runTimeStep,lineNum*lineGap+12,QString::number(m.start));
            //绘制结束时间坐标轴注释
            p.drawLine(diff+m.end*runTimeStep,lineNum*lineGap,
                diff+m.end*runTimeStep,lineNum*lineGap-3);
            p.drawText(8+m.end*runTimeStep,lineNum*lineGap+12,QString::number(m.end));
          }
      }

}
void ScheduleView::getDarwData(vector<QString> taskNames, vector<RunMsg> runMsgs){

 this->taskNames=taskNames;
 this->runMsgs=runMsgs;
  tasksID.clear();
  if(taskNames.empty()||runMsgs.empty())return;
  for(int i=0;i<taskNames.size();++i){
      tasksID[taskNames[i]]=i+1;
    }
  //调整runTimeStep
  int lastEndTime=runMsgs.at(runMsgs.size()-1).end;
  runTimeStep=(width()-20)/lastEndTime;
 repaint();
}
