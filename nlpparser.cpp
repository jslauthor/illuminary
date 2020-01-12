#include "nlpparser.h"

NLPParser::NLPParser()
{
  // set freeling locale to an UTF8 compatible locale
  // This is super important to call before instantiating the rest
  util::init_locale(L"default");

  tk = new tokenizer(QString(freeling_path + "tokenizer.dat").toStdWString());
  sp = new splitter(QString(freeling_path + "splitter.dat").toStdWString());

  tagger = new hmm_tagger(QString(freeling_path + "tagger.dat").toStdWString(), true, FORCE_TAGGER);
  parser = new chart_parser(QString(freeling_path + "chunker/grammar-chunk.dat").toStdWString());
  dep = new dep_txala(QString(freeling_path + "dep_txala/dependences.dat").toStdWString(), parser->get_start_symbol());
  np = new class np(QString(freeling_path + "np.dat").toStdWString());

  opt = new maco_options(L"en");
  opt->UserMapFile = L"";
  opt->QuantitiesFile = QString(freeling_path + "quantities.dat").toStdWString();
  opt->CompoundFile = QString(freeling_path + "compounds.dat").toStdWString();
  opt->LocutionsFile = QString(freeling_path + "locucions.dat").toStdWString();
  opt->AffixFile = QString(freeling_path + "afixos.dat").toStdWString();
  opt->ProbabilityFile = QString(freeling_path + "probabilitats.dat").toStdWString();
  opt->DictionaryFile = QString(freeling_path + "dicc.src").toStdWString();
  opt->NPdataFile = QString(freeling_path + "np.dat").toStdWString();
  opt->PunctuationFile = QString(freeling_path + "../common/punct.dat").toStdWString();

  morfo = new maco(*opt);
  morfo->set_active_options (false,// UserMap
                             true, // NumbersDetection,
                             true, //  PunctuationDetection,
                             true, //  DatesDetection,
                             true, //  DictionarySearch,
                             true, //  AffixAnalysis,
                             true, //  CompoundAnalysis,
                             true, //  RetokContractions,
                             true, //  MultiwordsDetection,
                             true, //  NERecognition,
                             true, //  QuantitiesDetection,
                             true);  //  ProbabilityAssignment

}

NLPParser::~NLPParser() {
  delete tk;
  delete sp;
  delete opt;
  delete morfo;
  delete np;
  delete tagger;
  delete parser;
  delete dep;
}

list<sentence> NLPParser::parse(wstring const &text) {
  list<word> lw;
  list<sentence> ls;

  sid = sp->open_session();
  qInfo("tokenize start");
  lw = tk->tokenize(text);
  qInfo("tokenize done, split start");
  ls = sp->split(sid, lw, false);
  qInfo("split done, morfo start");
  morfo->analyze(ls);
  qInfo("morfo done, tagger start");
  tagger->analyze(ls);
  qInfo("tagger done, parser start");
  parser->analyze(ls);
  qInfo("parser done, dep start");
  dep->analyze(ls);
  // Hm, this library seems to struggle with noun analysis (crashes)
//  qInfo("dep done, noun start");
//  np->analyze(ls);
  qInfo("done!");

  sp->close_session(sid);

  return ls;
}

void NLPParser::PrintMorfo(list<sentence> &ls) const {
  word::const_iterator a;
  sentence::const_iterator w;

  wcout<<L"----------- MORPHOLOGICAL INFORMATION -------------"<<endl;

  // print sentence XML tag
  for (list<sentence>::iterator is=ls.begin(); is!=ls.end(); is++) {

    wcout<<L"<SENT>"<<endl;
    // for each word in sentence
    for (w=is->begin(); w!=is->end(); w++) {

      // print word form, with PoS and lemma chosen by the tagger
      wcout<<L"  <WORD form=\""<<w->get_form();
      wcout<<L"\" lemma=\""<<w->get_lemma();
      wcout<<L"\" pos=\""<<w->get_tag();
      wcout<<L"\" position=\""<<w->get_position();
      wcout<<L"\">"<<endl;

      // for each possible analysis in word, output lemma, tag and probability
      for (a=w->analysis_begin(); a!=w->analysis_end(); ++a) {
        // print analysis info
        wcout<<L"    <ANALYSIS lemma=\""<<a->get_lemma();
        wcout<<L"\" pos=\""<<a->get_tag();
        wcout<<L"\" prob=\""<<a->get_prob();
        wcout<<L"\"/>"<<endl;
      }

      // close word XML tag after list of analysis
      wcout<<L"  </WORD>"<<endl;
    }

    // close sentence XML tag
    wcout<<L"</SENT>"<<endl;
  }
}
