#ifndef NLPANALYSISTHREAD_H
#define NLPANALYSISTHREAD_H

#include <QObject>
#include <QThread>

#include "nlpparser.h"
#include "nlpanalysismodel.h"

#include "freeling.h"
using namespace freeling;

// Add all of the metadata here
struct CompletedAnalysis {
  NLPAnalysisModel model;
  int averageWordLength;
};

Q_DECLARE_METATYPE(CompletedAnalysis)

class NLPAnalysisThread : public QThread
{
  Q_OBJECT
public:
  NLPAnalysisThread();
  ~NLPAnalysisThread() override;
  void run() override;

  void setDocument(const std::wstring &document);

Q_SIGNALS:
  void progressUpdate(qreal);
  void analysisStarted();
  void analysisComplete(CompletedAnalysis);

private:
  std::wstring m_document;
  NLPParser *m_parser;
};

#endif // NLPANALYSISTHREAD_H
