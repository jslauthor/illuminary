#include "nlpanalysisthread.h"

NLPAnalysisThread::NLPAnalysisThread()
{
  m_parser = new NLPParser();
}

NLPAnalysisThread::~NLPAnalysisThread() {
  delete m_parser;
}

void NLPAnalysisThread::run()
{
  Q_EMIT progressUpdate(0.0);

  list<freeling::sentence> sentences = m_parser->parse(m_document);

  CompletedAnalysis runningAnalysis;
  sentence::const_iterator word;
  qreal runningWordLength = 0;

  for (list<freeling::sentence>::iterator is = sentences.begin(); is != sentences.end(); is++) {
    Q_EMIT progressUpdate(static_cast<double>(std::distance(sentences.begin(), is)) / sentences.size());

    for (word = is->begin(); word != is->end(); word++) {
      NLPWord nlpword;
      nlpword.parseWord(*word);
      runningAnalysis.model.addWord(nlpword);
      runningWordLength += nlpword.word().length();
    }
  }

  runningAnalysis.averageWordLength = static_cast<int>(runningWordLength / runningAnalysis.model.rowCount());

  // All done
  Q_EMIT progressUpdate(1.0);
  Q_EMIT analysisComplete(runningAnalysis);
}

void NLPAnalysisThread::setDocument(const std::wstring &document)
{
  m_document = document;
}
