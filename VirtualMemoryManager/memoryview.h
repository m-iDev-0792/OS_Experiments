#ifndef MEMORYVIEW_H
#define MEMORYVIEW_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <vector>
using namespace std;
struct Memory{
  int id;
  int loadTime;
  int lastUsedTime;
  int storedPage;
  Memory()=default;
  Memory(int _id,int _loadTime,int _lastUsedTime,int _storedPage):id(_id),loadTime(_loadTime),lastUsedTime(_lastUsedTime),storedPage(_storedPage){}
};
class MemoryView : public QWidget
{
  Q_OBJECT
public:
  explicit MemoryView(QWidget *parent = nullptr);
  const int vertGap=5;
  const int horiGap=5;
  int mode;
signals:
protected:
  virtual void paintEvent(QPaintEvent* e);

public slots:
  void updateMemories(vector<Memory> m);
private:
  vector<Memory> memories;
};

#endif // MEMORYVIEW_H
