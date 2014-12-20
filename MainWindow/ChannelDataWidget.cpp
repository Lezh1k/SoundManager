#include <QPainter>
#include "ChannelDataWidget.h"
#include "Commons/Commons.h"

//ChannelDataWidget::ChannelDataWidget(QWidget *parent) :
//  QWidget(parent),
//  m_lpWfVis(NULL)
//{
//}

ChannelDataWidget::ChannelDataWidget(CWavFileVisualizer *lpWfVis, int channelNum) :
  m_channelNum(channelNum),
  m_lpWfVis(lpWfVis)
{
  this->setFrameShape(QFrame::Box);
  this->setLineWidth(1);
}
//////////////////////////////////////////////////////////////////////////

void ChannelDataWidget::paintEvent(QPaintEvent *e_paint)
{
  QFrame::paintEvent(e_paint);
  if (m_lpWfVis == NULL) return;
  QPainter painter;
  painter.begin(this);
  for (int i = 0; i < m_lpWfVis->vis_p_count(); ++i) {
    int y0 = this->size().height() / 2 - m_lpWfVis->ChannelsData()[m_channelNum][i] * 0.1;
    int y1 = y0 + m_lpWfVis->ChannelsData()[m_channelNum][i] * 0.1;
    painter.drawLine(i, y0, i, y1);
  }
  painter.end();
}
//////////////////////////////////////////////////////////////////////////

void ChannelDataWidget::resizeEvent(QResizeEvent *e_resize)
{
  if (m_lpWfVis == NULL) return;
  m_lpWfVis->set_vis_p_count(this->size().width());
  m_lpWfVis->RecountChannelData();
}
//////////////////////////////////////////////////////////////////////////
