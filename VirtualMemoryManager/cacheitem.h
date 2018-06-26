#ifndef CACHEITEM_H
#define CACHEITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
class CacheItem : public QObject,public QGraphicsItem
{
  Q_OBJECT
  Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
  Q_PROPERTY(QPointF pos READ pos WRITE setPos)
  Q_PROPERTY(int loadTime READ loadTime WRITE setLoadTime USER false)
  Q_PROPERTY(int lastUsedTime READ lastUsedTime WRITE setLastUsedTime USER false)
  Q_PROPERTY(int ID READ ID WRITE setID USER false)
public:

  explicit CacheItem(QObject *parent = nullptr);
  CacheItem(QRectF _rect,QObject *parent = nullptr);
  CacheItem(int width,int height,QObject *parent = nullptr);
  QRectF boundingRect() const;
  void paint(QPainter *painter,
                 const QStyleOptionGraphicsItem *option,
                 QWidget *widget);
  int loadTime()const;
  int lastUsedTime()const;
  void setLoadTime(int _loadTime);
  void setLastUsedTime(int _lastUsedTime);
  int ID()const;
  void setID(int id);
signals:

public slots:
private:
  QRectF rect;
  QRectF chipOuterRect;
  QRectF chipInnerRect;
  int pinLen;
  int cacheID;
  int m_loadTime;
  int m_lastUsedTime;
};

#endif // CACHEITEM_H
