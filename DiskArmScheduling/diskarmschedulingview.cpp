#include "diskarmschedulingview.h"

DiskArmSchedulingView::DiskArmSchedulingView(QWidget *parent) : QWidget(parent)
{

}
void DiskArmSchedulingView::paintEvent(QPaintEvent *e){
  QStyleOption opt;
  opt.init(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
  if(paintQueue.empty())return;
  int num=paintQueue.size();
  int diff=20;
  float gap=(float)height()/(num+1);
  int maxValue=max(*max_element(paintQueue.begin(),paintQueue.end()),defaultPos);
  int minValue=min(*min_element(paintQueue.begin(),paintQueue.end()),defaultPos);
  float pixelPerUnit=(float)(width()-2*diff)/(maxValue-minValue);

  //绘制虚线
  QPen dotlinePen(Qt::gray);
  dotlinePen.setStyle(Qt::DotLine);
  p.setPen(dotlinePen);
  for(int i=1;i<=num;++i){
      p.drawLine(0,gap*i,width(),gap*i);
      p.drawText(5,gap*i-3,QString("第")+QString::number(i)+QString("次访问"));
    }
  //绘制实线
  QPen solidlinePen(Qt::green);
  solidlinePen.setWidth(3);
  p.setPen(solidlinePen);
  p.drawLine(diff+(pixelPerUnit*(defaultPos-minValue)),0,diff+(pixelPerUnit*(paintQueue[0]-minValue)),gap*(1));
  for(int i=1;i<num;++i){
      p.drawLine(diff+(pixelPerUnit*(paintQueue[i-1]-minValue)),gap*i,diff+(pixelPerUnit*(paintQueue[i]-minValue)),gap*(i+1));
    }
  QPen circlePen(Qt::red);//绘制圆
  p.setPen(circlePen);
  for(int i=0;i<num;++i){
      p.drawEllipse(QPoint(diff+(pixelPerUnit*(paintQueue[i]-minValue)),gap*(i+1)),5,5);
    }

  //绘制文字标记
  QPen textPen(Qt::black);
  p.setPen(textPen);
  for(auto& t:paintQueue){
      p.drawLine(diff+pixelPerUnit*(t-minValue),0,diff+pixelPerUnit*(t-minValue),5);
      p.drawText(diff+pixelPerUnit*(t-minValue)-5,20,QString::number(t));
    }
  p.drawText(10,height()-15,QString("磁头移动总距离:")+QString::number(totalMovement));
}
void DiskArmSchedulingView::getResult(vector<int> _paintQueue, int _defaultPos, int _totalMovement){
  paintQueue=_paintQueue;
  defaultPos=_defaultPos;
  totalMovement=_totalMovement;
  repaint();
}
