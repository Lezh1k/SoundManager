#ifndef CHANNELDATAWIDGET_H
#define CHANNELDATAWIDGET_H

#include <QWidget>
#include <QFrame>
#include "WaveFile/WavFileVisualizer.h"

class ChannelDataWidget : public QFrame
{
  Q_OBJECT
public:
  //explicit ChannelDataWidget(QWidget *parent = 0);
  ChannelDataWidget(CWavFileVisualizer* lpWfVis, int channelNum);

private:
  int m_channelNum;
  CWavFileVisualizer* m_lpWfVis;

signals:

public slots:

  // QWidget interface
protected:
  void paintEvent(QPaintEvent *e_paint);
  void resizeEvent(QResizeEvent *e_resize);
  void mouseDoubleClickEvent(QMouseEvent *);
};

#endif // CHANNELDATAWIDGET_H
