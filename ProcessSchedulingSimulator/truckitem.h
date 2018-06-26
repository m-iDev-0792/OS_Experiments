#ifndef TRUCKITEM_H
#define TRUCKITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
class TruckItem : public QObject,public QGraphicsItem
{
  Q_OBJECT
  Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
  Q_PROPERTY(QPointF pos READ pos WRITE setPos)
  Q_PROPERTY(float quantity READ quantity WRITE setQuantity)
public:
  explicit TruckItem(QObject *parent = nullptr);
  TruckItem(QString _taskName,int _quantity,QObject* parent=0);
  void setQuantity(float _quantity);
  float quantity()const;
  QRectF boundingRect() const;
  void paint(QPainter *painter,
                 const QStyleOptionGraphicsItem *option,
                 QWidget *widget);
  QString taskName;//lazy
private:
  float m_quantity;
  QPixmap truckImg;
signals:

public slots:
};

#endif // TRUCKITEM_H
