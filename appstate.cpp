#include "appstate.h"

AppState::AppState()
{
  m_colors = new ColorModel();
  m_analysisThread = new NLPAnalysisThread();

  QObject::connect(m_analysisThread, SIGNAL(progressUpdate(qreal)), this, SLOT(onAnalysisProgress(qreal)));
  QObject::connect(m_analysisThread, SIGNAL(analysisStarted()), this, SLOT(onAnalysisStarted()));
  QObject::connect(m_analysisThread, SIGNAL(analysisComplete(CompletedAnalysis)), this, SLOT(onAnaylsisComplete(CompletedAnalysis)));
}


AppState::~AppState() {
  if (m_analysis) {
    delete m_analysis;
  }
  delete m_colors;
  delete m_analysisThread;
}

NLPAnalysisModel* AppState::analysis() const {
  return m_analysis;
}

ColorModel* AppState::colors() const {
  return m_colors;
}

QString AppState::corpus() const {
  return m_corpus;
}

void AppState::setCorpus(const QString &corpus) {
  m_corpus = corpus;
  Q_EMIT corpusChanged();
}

bool AppState::isAnalysisRunning()
{
  return m_isAnalysisRunning;
}

int AppState::averageWordLength() const
{
  return m_averageWordLength;
}

qreal AppState::analysisProgress() const
{
  return m_analysisProgress;
}

void AppState::setAnalysisProgress(const qreal &analysisProgress)
{
  m_analysisProgress = std::clamp(analysisProgress, 0.0, 100.0);
  Q_EMIT analysisProgressChanged();
}

void AppState::onAnalysisProgress(qreal progress)
{
  setAnalysisProgress(progress);
}

void AppState::onAnalysisStarted() {
  m_isAnalysisRunning = true;
  Q_EMIT analysisRunningChanged();
}

void AppState::onAnaylsisComplete(CompletedAnalysis analysis)
{
    if (m_analysis) {
      delete m_analysis;
      m_analysis = nullptr;
    }

    m_analysis = &analysis.model;
    m_averageWordLength = analysis.averageWordLength;

    Q_EMIT analysisChanged();

    m_isAnalysisRunning = false;
    Q_EMIT analysisRunningChanged();
}

void AppState::loadFile(const QString& filename) {
    if (!m_isAnalysisRunning) {
        QFile file(QUrl(filename).toLocalFile());
    if (!file.open(QIODevice::ReadOnly)) {
      qWarning("%s", file.errorString().toStdString().c_str());
    }
    QTextStream in(&file);
    setCorpus(in.readAll());

    m_analysisThread->setDocument(m_corpus.toStdWString());
    m_analysisThread->start();

    file.close();
  }
}


