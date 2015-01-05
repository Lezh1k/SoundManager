#ifndef CHANNELDATAWIDGET_H
#define CHANNELDATAWIDGET_H

#include <QWidget>
#include <QFrame>
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

signals:

public slots:

  // QWidget interface
protected:
  void paintEvent(QPaintEvent *e_paint);
  void resizeEvent(QResizeEvent *e_resize);
  void mouseDoubleClickEvent(QMouseEvent *mouse_event);
  void mouseReleaseEvent(QMouseEvent *mouse_event);
};

#endif // CHANNELDATAWIDGET_H
