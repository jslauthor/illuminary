#ifndef APPSTATE_H
#define APPSTATE_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QUrl>
#include <QAbstractListModel>
#include "nlpparser.h"
#include "nlpsentence.h"

#include "freeling.h"
using namespace freeling;

class AppState : public QObject
{
  Q_OBJECT
  Q_PROPERTY(NLPSentenceModel* sentences READ sentences NOTIFY sentencesChanged CONSTANT)
  Q_PROPERTY(QString corpus READ corpus WRITE setCorpus NOTIFY corpusChanged)
public:
  AppState();
  ~AppState() override;
  Q_INVOKABLE void loadFile(const QString&);

  NLPSentenceModel* sentences() const;

  QString corpus() const;
  void setCorpus(const QString&);

Q_SIGNALS:
  void sentencesChanged();
  void corpusChanged();

protected:
  NLPParser *m_parser;
  NLPSentenceModel* m_sentences = nullptr;
  QString m_corpus;
};

#endif // APPSTATE_H
