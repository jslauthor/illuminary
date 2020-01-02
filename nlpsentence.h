#ifndef NLPSENTENCE_H
#define NLPSENTENCE_H

#include <QObject>
#include <QQmlListProperty>
#include <QVector>
#include "nlpword.h"


class NLPSentence : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QQmlListProperty<NLPWord> words READ words)
public:
  explicit NLPSentence(QObject *parent = nullptr);

  void appendWord(NLPWord *word);
  int wordCount() const;
  NLPWord *word(int) const;
  void clearWords();

  QQmlListProperty<NLPWord> words();
Q_SIGNALS:
protected:
  static void appendWord(QQmlListProperty<NLPWord>*, NLPWord*);
  static int wordCount(QQmlListProperty<NLPWord>*);
  static NLPWord* word(QQmlListProperty<NLPWord>*, int);
  static void clearWords(QQmlListProperty<NLPWord>*);

  QVector<NLPWord*> m_words;
};

#endif // NLPSENTENCE_H
