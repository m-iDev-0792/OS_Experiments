#include "headstateitem.h"

HeadStateItem::HeadStateItem(QObject *parent) : QObject(parent)
{
  m_curPos=m_totalMovement=0;
}
int HeadStateItem::totalMovement()const{
  return m_totalMovement;
}
int HeadStateItem::curPos()const{
  return m_curPos;
}
void HeadStateItem::setCurPos(int _curPos){
  m_curPos=_curPos;
  update(boundingRect());
}
void HeadStateItem::setTotalMovement(int _totalMovement){
  m_totalMovement=_totalMovement;
  update(boundingRect());
}
QRectF HeadStateItem::boundingRect()const{
  return QRectF(0,0,200,100);
}
void HeadStateItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
  painter->setFont(QFont(QString("雅痞-简"),20,20));
  painter->drawText(5,30,QString("当前磁道:")+QString::number(m_curPos));
  painter->drawText(5,60,QString("移动总距离:")+QString::number(m_totalMovement));

}
