#include "truckitem.h"

TruckItem::TruckItem(QObject *parent) : QObject(parent)
{
  truckImg.load("/image/truck.png");
  setQuantity(0);
}
TruckItem::TruckItem(QString _taskName, int _quantity, QObject *parent):QObject(parent){
  taskName=_taskName;
  setQuantity(_quantity);
  truckImg.load(":/image/truck.png");
}

QRectF TruckItem::boundingRect()const{
  return QRectF(0,0,110,60);
}
void TruckItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
  painter->setBrush(QBrush(QColor(139,21,39)));
  painter->drawPixmap(0,14,110,46,truckImg);
  painter->drawText(36,15,taskName+QString(":")+QString::number(m_quantity>0?m_quantity:0));
  //we set 10px per quantity
  if(m_quantity>0)
  painter->drawRect(32,18,m_quantity*10,27);
}
void TruckItem::setQuantity(float _quantity){
  m_quantity=_quantity;
  update();
}
float TruckItem::quantity()const{
  return m_quantity;
}

