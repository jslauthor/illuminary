#include "appstate.h"

AppState::AppState()
{
  m_parser = new NLPParser();
}

AppState::~AppState() {
  delete m_parser;
  delete m_sentences;
}

NLPSentenceModel* AppState::sentences() const {
  return m_sentences;
}

QString AppState::corpus() const {
  return m_corpus;
}

void AppState::setCorpus(const QString &corpus) {
  m_corpus = corpus;
  Q_EMIT corpusChanged();
}

void AppState::loadFile(const QString& filename) {
  QFile file(QUrl(filename).toLocalFile());
  if (!file.open(QIODevice::ReadOnly)) {
    qWarning("%s", file.errorString().toStdString().c_str());
  }
  QTextStream in(&file);
  setCorpus(in.readAll());

  list<freeling::sentence> sentences = m_parser->parse(m_corpus.toStdWString());

  if (m_sentences) {
    delete m_sentences;
    m_sentences = nullptr;
  }

  m_sentences = new NLPSentenceModel(this);
  sentence::const_iterator word;
  for (list<freeling::sentence>::iterator is = sentences.begin(); is != sentences.end(); is++) {
    NLPSentenceModel nlpsentence;
    for (word = is->begin(); word != is->end(); word++) {
      NLPWord nlpword;
      nlpword.parseWord(*word);
      m_sentences->addWord(nlpword);
    }
  }

  file.close();
  Q_EMIT sentencesChanged();
}


