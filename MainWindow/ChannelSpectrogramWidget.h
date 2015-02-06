#ifndef CHANNELSPECTROGRAMWIDGET_H
#define CHANNELSPECTROGRAMWIDGET_H

#include <QFrame>
#include "WaveFile/WaveFileSpectrogramVisualizer.h"

class ChannelSpectrogramWidget : public QFrame
{
  Q_OBJECT
public:
  explicit ChannelSpectrogramWidget(CWaveFileSpectrogramVisualizer* lpWfsVis);
  ~ChannelSpectrogramWidget(void);

private:

  CWaveFileSpectrogramVisualizer* m_lpWfsVis;
  // QWidget interface
protected:
  virtual void paintEvent(QPaintEvent *pe);
  virtual void resizeEvent(QResizeEvent */*re*/);
};

#endif // CHANNELSPECTROGRAMWIDGET_H

