#ifndef NLPPARSER_H
#define NLPPARSER_H

#include "freeling.h"
#include <QString>

using namespace freeling;

/*
 * The Freeling parser
 **/
class NLPParser
{
public:

  NLPParser();
  ~NLPParser();

  list<sentence> parse(wstring const &text);

  // For debugging purposes
  void PrintMorfo(list<sentence> &ls) const;

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
