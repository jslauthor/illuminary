#ifndef NLPPARSER_H
#define NLPPARSER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QUrl>
#include <QQmlListProperty>

#include "freeling.h"
using namespace freeling;

/*
 * The Freeling parser
 **/
class NLPParser : public QObject
{

  Q_OBJECT

public:

  explicit NLPParser(QObject *parent = nullptr);
  ~NLPParser() override;

  Q_INVOKABLE void loadFile(const QString&);

  // For debugging purposes
  void PrintMorfo(list<sentence> &ls) const;

Q_SIGNALS:



protected:

  QString freeling_path = "/usr/local/share/freeling/en/";
  tokenizer *tk;
  splitter *sp;
  splitter::session_id sid;
  maco_options *opt;
  maco *morfo;
  np *np;

  // create a hmm tagger for english (with retokenization ability, and forced
  // to choose only one tag per word)
  hmm_tagger *tagger;
  // create chunker
  chart_parser *parser;
  // create dependency parser
  dep_txala *dep;
};

#endif // NLPPARSER_H
