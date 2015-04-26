
#include <QFileDialog>
#include <QMessageBox>

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "ChannelDataWidget.h"
#include "WaveFile/WaveFileSpectrogramVisualizer.h"
#include "ChannelSpectrogramWidget.h"


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  m_wavFile(NULL)
{
  ui->setupUi(this),
  connect(ui->m_mnuFileExit, SIGNAL(triggered()), this, SLOT(MnuFileExit_Clicked()));
  connect(ui->m_mnuFileOpen, SIGNAL(triggered()), this, SLOT(MnuFileOpen_Clicked()));
}

MainWindow::~MainWindow() {
  delete ui;
  if (m_wavFile) delete m_wavFile;
}
//////////////////////////////////////////////////////////////////////////

void MainWindow::ResetWavFile(const std::string &fileName)
{
  if (m_wavFile) { delete m_wavFile; m_wavFile = NULL; }

  m_wavFile = new CWavFile(fileName.c_str());
  if (m_wavFile->LastError() != WFE_SUCCESS) {
    //todo handle this.
    return;
  }  

  while(ui->m_grdlChannels->count() > 0) {
    QWidget* widget = ui->m_grdlChannels->itemAt(0)->widget();
    if(widget) {
      ui->m_grdlChannels->removeWidget(widget);
      delete widget;
    }
  }

  for (int i = 0; i < m_wavFile->Header()->fmt.options.numChannels; ++i) {
    CWavFileChannelVisualizer *visualizer = new CWavFileChannelVisualizer(m_wavFile, i);
    ChannelDataWidget* widget = new ChannelDataWidget(visualizer);

    CWaveFileSpectrogramVisualizer *sp_visualizer
        = new CWaveFileSpectrogramVisualizer(m_wavFile, i);
    ChannelSpectrogramWidget *sp_widget = new ChannelSpectrogramWidget(sp_visualizer);

    ui->m_grdlChannels->addWidget(widget, i, 0);
    ui->m_grdlChannels->addWidget(sp_widget, i, 1);
  }
  ui->m_grdlChannels->invalidate();
}
//////////////////////////////////////////////////////////////////////////

void MainWindow::MnuFileExit_Clicked() {
  this->close();
}
//////////////////////////////////////////////////////////////////////////

void MainWindow::MnuFileOpen_Clicked() {
  QString fileName = QFileDialog::getOpenFileName(this,
                                                  tr("Open wav file"),
                                                  QString(),
                                                  tr("Sound Files (*.wav *.wave)"));
  if (fileName.isEmpty()) return;
  ResetWavFile(fileName.toStdString());
}
//////////////////////////////////////////////////////////////////////////
