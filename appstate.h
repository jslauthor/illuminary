#ifndef APPSTATE_H
#define APPSTATE_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QUrl>
#include <QAbstractListModel>
#include "nlpanalysismodel.h"
#include "colormodel.h"
#include "nlpanalysisthread.h"

#include "freeling.h"
using namespace freeling;

class AppState : public QObject
{
  Q_OBJECT
  Q_PROPERTY(NLPAnalysisModel* analysis READ analysis NOTIFY analysisChanged)
  Q_PROPERTY(ColorModel* colors READ colors NOTIFY colorsChanged)
  Q_PROPERTY(QString corpus READ corpus WRITE setCorpus NOTIFY corpusChanged)
  Q_PROPERTY(int averageWordLength READ averageWordLength NOTIFY analysisChanged)
  Q_PROPERTY(qreal analysisProgress READ analysisProgress WRITE setAnalysisProgress NOTIFY analysisProgressChanged)
  Q_PROPERTY(bool isAnalysisRunning READ isAnalysisRunning NOTIFY analysisRunningChanged)
public:
  AppState();
  ~AppState() override;
  Q_INVOKABLE void loadFile(const QString&);

  NLPAnalysisModel* analysis() const;
  ColorModel* colors() const;

  QString corpus() const;
  void setCorpus(const QString&);

  bool isAnalysisRunning();
  int averageWordLength() const;

  qreal analysisProgress() const;
  void setAnalysisProgress(const qreal &analysisProgress);

Q_SIGNALS:
  void analysisChanged();
  void corpusChanged();
  void colorsChanged();
  void analysisProgressChanged();
  void analysisRunningChanged();

public Q_SLOTS:
  void onAnalysisProgress(qreal);
  void onAnalysisStarted();
  void onAnaylsisComplete(CompletedAnalysis);

protected:
  int m_averageWordLength;
  NLPAnalysisModel *m_analysis = nullptr;
  ColorModel *m_colors = nullptr;
  QString m_corpus;

  qreal m_analysisProgress = 0.0;
  bool m_isAnalysisRunning = false;

  NLPAnalysisThread *m_analysisThread;
};

#endif // APPSTATE_H
