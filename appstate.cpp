#include "appstate.h"

AppState::AppState()
{
  m_parser = new NLPParser();
  m_colors = new ColorModel();
}

AppState::~AppState() {
  delete m_parser;
  delete m_analysis;
  delete m_colors;
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

int AppState::averageWordLength() const
{
  return m_averageWordLength;
}

void AppState::loadFile(const QString& filename) {
  QFile file(QUrl(filename).toLocalFile());
  if (!file.open(QIODevice::ReadOnly)) {
    qWarning("%s", file.errorString().toStdString().c_str());
  }
  QTextStream in(&file);
  setCorpus(in.readAll());

  list<freeling::sentence> sentences = m_parser->parse(m_corpus.toStdWString());

  if (m_analysis) {
    delete m_analysis;
    m_analysis = nullptr;
  }

  m_analysis = new NLPAnalysisModel(this);
  sentence::const_iterator word;
  qreal runningWordLength = 0;
  for (list<freeling::sentence>::iterator is = sentences.begin(); is != sentences.end(); is++) {
    for (word = is->begin(); word != is->end(); word++) {
      NLPWord nlpword;
      nlpword.parseWord(*word);
      m_analysis->addWord(nlpword);
      runningWordLength += nlpword.word().length();
    }
  }

  m_averageWordLength = static_cast<int>(runningWordLength / m_analysis->rowCount());
  file.close();
  Q_EMIT analysisChanged();
}


