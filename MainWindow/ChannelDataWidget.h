#ifndef CHANNELDATAWIDGET_H
#define CHANNELDATAWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QImage>
#include <QPainter>
#include "WaveFile/WavFileChannelVisualizer.h"

class ChannelDataWidget : public QFrame
{
  Q_OBJECT
public:
  //explicit ChannelDataWidget(QWidget *parent = 0);
  ChannelDataWidget(CWavFileChannelVisualizer* lpWfVis);
  ~ChannelDataWidget(void);

private:  
  CWavFileChannelVisualizer* m_lpWfVis;
  int m_lastX;  

  enum LBTN_STATE {
    BS_UP, BS_DOWN
  } m_lBtnState;  

signals:

public slots:

  // QWidget interface
protected:
  virtual void paintEvent(QPaintEvent *e_paint);
  virtual void resizeEvent(QResizeEvent */*e_resize*/);
  virtual void mouseDoubleClickEvent(QMouseEvent *mouse_event);
  virtual void mouseReleaseEvent(QMouseEvent */*mouse_event*/);
  virtual void mousePressEvent(QMouseEvent *mouse_event);
  virtual void mouseMoveEvent(QMouseEvent *mouse_event);
};

#endif // CHANNELDATAWIDGET_H
