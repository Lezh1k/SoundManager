#include <QPainter>
#include <QMouseEvent>
#include "ChannelDataWidget.h"
#include "Commons/Commons.h"

ChannelDataWidget::ChannelDataWidget(CWavFileChannelVisualizer *lpWfVis) :
  m_lpWfVis(lpWfVis),
  m_lastX(0),
  m_lBtnState(BS_UP)
{
  this->setFrameShape(QFrame::Box);
  this->setLineWidth(1);
  this->setMouseTracking(true);
}

ChannelDataWidget::~ChannelDataWidget()
{
  if (m_lpWfVis) delete m_lpWfVis;
}
/////////////////////////////////////////////////////////////////////////

void ChannelDataWidget::paintEvent(QPaintEvent *e_paint)
{
  QFrame::paintEvent(e_paint);
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

void ChannelDataWidget::resizeEvent(QResizeEvent */*e_resize*/)
{
  m_lpWfVis->set_size(this->size().width(), this->size().height());
}
//////////////////////////////////////////////////////////////////////////

void ChannelDataWidget::mouseDoubleClickEvent(QMouseEvent *mouse_event)
{
  double diff = m_lpWfVis->end_sec() - m_lpWfVis->start_sec();  
  const double center_sec =
      mouse_event->pos().x() * (diff / m_lpWfVis->vis_width());

  if (mouse_event->button() == Qt::LeftButton)
    diff /= 4.0;

  m_lpWfVis->set_time(center_sec - diff, center_sec + diff);
  this->update();
}
//////////////////////////////////////////////////////////////////////////

void ChannelDataWidget::mouseReleaseEvent(QMouseEvent */*mouse_event*/)
{
  m_lBtnState = BS_UP;
}
//////////////////////////////////////////////////////////////////////////

void ChannelDataWidget::mousePressEvent(QMouseEvent *mouse_event)
{
  if (mouse_event->button() == Qt::LeftButton) {
    m_lastX = mouse_event->x();  
    m_lBtnState = BS_DOWN;
  }
}
//////////////////////////////////////////////////////////////////////////

void ChannelDataWidget::mouseMoveEvent(QMouseEvent *mouse_event)
{  
  if (m_lBtnState == BS_UP) return;

  do {
    double diff = (mouse_event->x() - m_lastX) * m_lpWfVis->time_per_pixel();
    double start_time = m_lpWfVis->start_sec() - diff;
    if (start_time <= m_lpWfVis->min_time()) {
      m_lpWfVis->set_time(m_lpWfVis->min_time(), m_lpWfVis->vis_width()*m_lpWfVis->time_per_pixel());
      break;
    }
    double end_time = m_lpWfVis->end_sec() - diff;
    if (end_time >= m_lpWfVis->max_time()) {
      m_lpWfVis->set_time(m_lpWfVis->max_time() - m_lpWfVis->vis_width()*m_lpWfVis->time_per_pixel(),
                          m_lpWfVis->max_time());
      break;
    }
    m_lpWfVis->set_time(start_time, end_time);
  } while (0);
  m_lastX = mouse_event->x();
  this->update();
  mouse_event->accept();
}
//////////////////////////////////////////////////////////////////////////
