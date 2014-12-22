#include <QPainter>
#include "ChannelDataWidget.h"
#include "Commons/Commons.h"

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
  double coeff = (this->size().height() - 20)  / m_lpWfVis->ChannelMax(m_channelNum);
  int median = this->size().height() >> 1;
  for (int i = 0; i < m_lpWfVis->vis_p_count(); ++i) {
    int y0 = median - m_lpWfVis->ChannelsData()[m_channelNum][i] * coeff / 2.0;
    int y1 = y0 + m_lpWfVis->ChannelsData()[m_channelNum][i] * coeff;
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

void ChannelDataWidget::mouseDoubleClickEvent(QMouseEvent *)
{
  if (m_lpWfVis == NULL) return;

}
//////////////////////////////////////////////////////////////////////////
