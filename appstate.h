#ifndef APPSTATE_H
#define APPSTATE_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QUrl>
#include <QAbstractListModel>
#include "nlpparser.h"
#include "nlpanalysismodel.h"
#include "colormodel.h"

#include "freeling.h"
using namespace freeling;

class AppState : public QObject
{
  Q_OBJECT
  Q_PROPERTY(NLPAnalysisModel* analysis READ analysis NOTIFY analysisChanged)
  Q_PROPERTY(ColorModel* colors READ colors NOTIFY colorsChanged)
  Q_PROPERTY(QString corpus READ corpus WRITE setCorpus NOTIFY corpusChanged)
  Q_PROPERTY(int averageWordLength READ averageWordLength NOTIFY analysisChanged)
public:
  AppState();
  ~AppState() override;
  Q_INVOKABLE void loadFile(const QString&);

  NLPAnalysisModel* analysis() const;
  ColorModel* colors() const;

  QString corpus() const;
  void setCorpus(const QString&);

  int averageWordLength() const;

Q_SIGNALS:
  void analysisChanged();
  void corpusChanged();
  void colorsChanged();

protected:
  int m_averageWordLength;
  NLPParser *m_parser;
  NLPAnalysisModel *m_analysis = nullptr;
  ColorModel *m_colors = nullptr;
  QString m_corpus;
};

#endif // APPSTATE_H
