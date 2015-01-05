#include <QPainter>
#include <QMouseEvent>
#include "ChannelDataWidget.h"
#include "Commons/Commons.h"

ChannelDataWidget::ChannelDataWidget(CWavFileChannelVisualizer *lpWfVis) :
  m_lpWfVis(lpWfVis)
{
  this->setFrameShape(QFrame::Box);
  this->setLineWidth(1);
}

ChannelDataWidget::~ChannelDataWidget()
{
  if (m_lpWfVis)
    delete m_lpWfVis;
}
//////////////////////////////////////////////////////////////////////////

void ChannelDataWidget::paintEvent(QPaintEvent *e_paint)
{
  QFrame::paintEvent(e_paint);
  if (m_lpWfVis == NULL) return;
  QPainter painter;
  painter.begin(this);  
  double coeff = (this->size().height() - 20)  / m_lpWfVis->ChannelMax();
  int median = this->size().height() >> 1;
  for (int i = 0; i < this->size().width(); ++i) {
    int y0 = median - m_lpWfVis->ChannelsData()[i] * coeff / 2.0;
    int y1 = y0 + m_lpWfVis->ChannelsData()[i] * coeff;
    painter.drawLine(i, y0, i, y1);
  }
  painter.end();
}
//////////////////////////////////////////////////////////////////////////

void ChannelDataWidget::resizeEvent(QResizeEvent *e_resize)
{
  if (m_lpWfVis == NULL) return;
  m_lpWfVis->set_size(this->size().width(), this->size().height());
}
//////////////////////////////////////////////////////////////////////////

void ChannelDataWidget::mouseDoubleClickEvent(QMouseEvent *mouse_event)
{
  if (m_lpWfVis == NULL) return;  
}
//////////////////////////////////////////////////////////////////////////

void ChannelDataWidget::mouseReleaseEvent(QMouseEvent *mouse_event)
{
  if (m_lpWfVis == NULL) return;
  if (mouse_event->button() == Qt::LeftButton) {
    //grow
    double diff = m_lpWfVis->end_sec() - m_lpWfVis->start_sec();
    diff /= 4.0;
    m_lpWfVis->set_time(m_lpWfVis->start_sec() + diff, m_lpWfVis->end_sec() - diff);
  }
  else if (mouse_event->button() == Qt::RightButton) {
    //reduce
    double diff = m_lpWfVis->end_sec() - m_lpWfVis->start_sec();
    diff *= 2.0;
    m_lpWfVis->set_time(m_lpWfVis->start_sec() - diff, m_lpWfVis->end_sec() + diff);
  }
  this->update();
}
//////////////////////////////////////////////////////////////////////////
