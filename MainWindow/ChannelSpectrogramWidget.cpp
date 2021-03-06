#include <QPainter>
#include "ChannelSpectrogramWidget.h"

ChannelSpectrogramWidget::ChannelSpectrogramWidget(CWaveFileSpectrogramVisualizer *lpWfsVis) :
  m_lpWfsVis(lpWfsVis)
{
  this->setFrameShape(QFrame::Box);
  this->setLineWidth(1);
}

ChannelSpectrogramWidget::~ChannelSpectrogramWidget()
{
  if (m_lpWfsVis) delete m_lpWfsVis;
}
/////////////////////////////////////////////////////////////////////////

void ChannelSpectrogramWidget::paintEvent(QPaintEvent *pe)
{
  QFrame::paintEvent(pe);
  QPainter painter;
  painter.begin(this);

  painter.end();
}
/////////////////////////////////////////////////////////////////////////

void ChannelSpectrogramWidget::resizeEvent(QResizeEvent */*re*/)
{
}
/////////////////////////////////////////////////////////////////////////
