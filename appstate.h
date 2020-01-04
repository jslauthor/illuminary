#ifndef APPSTATE_H
#define APPSTATE_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QUrl>
#include <QAbstractListModel>
#include "nlpparser.h"
#include "nlpsentences.h"
#include "nlpsentence.h"

#include "freeling.h"
using namespace freeling;

class AppState : public QObject
{
  Q_OBJECT
  Q_PROPERTY(NLPSentenceModel* sentence READ sentences NOTIFY sentencesChanged CONSTANT)
public:
  AppState();
  ~AppState() override;
  Q_INVOKABLE void loadFile(const QString&);

  NLPSentenceModel* sentences() const;

Q_SIGNALS:
  void sentencesChanged();

protected:
  NLPParser *m_parser;
  NLPSentenceModel* m_sentences = nullptr;
};

#endif // APPSTATE_H
