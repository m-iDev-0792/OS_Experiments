#ifndef HEADSTATEITEM_H
#define HEADSTATEITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
class HeadStateItem : public QObject,public QGraphicsItem
{
  Q_OBJECT
  Q_PROPERTY(QPointF pos READ pos WRITE setPos)
  Q_PROPERTY(int curPos READ curPos WRITE setCurPos USER false)
  Q_PROPERTY(int totalMovement READ totalMovement WRITE setTotalMovement USER false)
public:
  explicit HeadStateItem(QObject *parent = nullptr);
  QRectF boundingRect()const;
  void setCurPos(int _curPos);
  void setTotalMovement(int _totalMovement);
  int curPos()const;
  int totalMovement()const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
signals:

public slots:
private:
  int m_curPos;
  int m_totalMovement;
};

#endif // HEADSTATEITEM_H
