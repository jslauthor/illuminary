#ifndef APPSTATE_H
#define APPSTATE_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QUrl>
#include <QQmlListProperty>
#include "nlpparser.h"
#include "nlpsentence.h"

#include "freeling.h"
using namespace freeling;

class AppState : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QQmlListProperty<NLPSentence> sentences READ sentences NOTIFY sentencesChanged)
public:
  AppState();
  ~AppState() override;
  Q_INVOKABLE void loadFile(const QString&);

  void appendSentence(NLPSentence *sentence);
  int sentenceCount() const;
  NLPSentence *sentence(int) const;
  void clearSentences();

  QQmlListProperty<NLPSentence> sentences();

Q_SIGNALS:
  void sentencesChanged();

protected:
  NLPParser *m_parser;
  QVector<NLPSentence*> m_sentences;

  static void appendSentence(QQmlListProperty<NLPSentence>*, NLPSentence*);
  static int sentenceCount(QQmlListProperty<NLPSentence>*);
  static NLPSentence* sentence(QQmlListProperty<NLPSentence>*, int);
  static void clearSentences(QQmlListProperty<NLPSentence>*);
};

#endif // APPSTATE_H
