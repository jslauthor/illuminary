#ifndef NLPWORD_H
#define NLPWORD_H

#include <QObject>
#include "freeling.h"

class PartOfSpeechMapping;

/*
 * The analyzed word. The main primitive for our data visualization.
 **/

class NLPPartOfSpeech : public QObject {
  Q_OBJECT
public:
  NLPPartOfSpeech(QObject *parent = nullptr) : QObject(parent) {

  }
  enum POS {
    Noun,
    Pronoun,
    Verb,
    Adverb,
    Adjective,
    Adposition,
    Preposition,
    Conjunction,
    Determiner,
    Interjection,
    Article,
    Punctuation,
    Number,
    Date,
    Unknown
  };
  Q_ENUM(POS)
};

class NLPWord
{
public:
  NLPWord();
  ~NLPWord() {

  }
  NLPWord(const NLPWord &other) {
    m_pos = other.m_pos;
    m_word = other.m_word;
    m_form = other.m_form;
  }

  NLPPartOfSpeech::POS pos() const;
  QString word() const;

  void parseWord(const freeling::word word); // create copy parse and store it

Q_SIGNALS:

protected:
  NLPPartOfSpeech::POS m_pos;
  QString m_form;
  freeling::word m_word;
  static PartOfSpeechMapping m_posMap;
};


/*
 * Mapping class for all parts of speech found in Freeling
 * Taken from: https://freeling-user-manual.readthedocs.io/en/v4.1/tagsets/tagset-en/
 **/

class PartOfSpeechMapping
{
public:
  PartOfSpeechMapping() {
    // Adjectives
    m_mapStringValues[L"JJ"] = NLPPartOfSpeech::POS::Adjective;
    m_mapStringValues[L"JJR"] = NLPPartOfSpeech::POS::Adjective;
    m_mapStringValues[L"JJS"] = NLPPartOfSpeech::POS::Adjective;
    // Adposition
    m_mapStringValues[L"POS"] = NLPPartOfSpeech::POS::Adposition;
    // Adverb
    m_mapStringValues[L"RB"] = NLPPartOfSpeech::POS::Adverb;
    m_mapStringValues[L"RBR"] = NLPPartOfSpeech::POS::Adverb;
    m_mapStringValues[L"RBS"] = NLPPartOfSpeech::POS::Adverb;
    m_mapStringValues[L"WRB"] = NLPPartOfSpeech::POS::Adverb;
    // Conjunction
    m_mapStringValues[L"CC"] = NLPPartOfSpeech::POS::Conjunction;
    // Determiner
    m_mapStringValues[L"DT"] = NLPPartOfSpeech::POS::Determiner;
    m_mapStringValues[L"WDT"] = NLPPartOfSpeech::POS::Determiner; // type:interrogative
    m_mapStringValues[L"PDT"] = NLPPartOfSpeech::POS::Determiner; // type:predeterminer
    // Interjection
    m_mapStringValues[L"UH"] = NLPPartOfSpeech::POS::Interjection;
    // Noun
    m_mapStringValues[L"NNS"] = NLPPartOfSpeech::POS::Noun; // plural
    m_mapStringValues[L"NN"] = NLPPartOfSpeech::POS::Noun; // singular
    m_mapStringValues[L"NNP"] = NLPPartOfSpeech::POS::Noun; // proper
    m_mapStringValues[L"NP00000"] = NLPPartOfSpeech::POS::Noun; // proper
    m_mapStringValues[L"NP"] = NLPPartOfSpeech::POS::Noun; // proper
    m_mapStringValues[L"NP00G00"] = NLPPartOfSpeech::POS::Noun; // proper
    m_mapStringValues[L"NP00O00"] = NLPPartOfSpeech::POS::Noun; // proper
    m_mapStringValues[L"NP00V00"] = NLPPartOfSpeech::POS::Noun; // proper
    m_mapStringValues[L"NP00SP0"] = NLPPartOfSpeech::POS::Noun; // proper
    m_mapStringValues[L"NNPS"] = NLPPartOfSpeech::POS::Noun; // proper
    // Article
    m_mapStringValues[L"RP"] = NLPPartOfSpeech::POS::Article;
    m_mapStringValues[L"TO"] = NLPPartOfSpeech::POS::Article;
    // Proposition
    m_mapStringValues[L"IN"] = NLPPartOfSpeech::POS::Preposition;
    // Pronoun
    m_mapStringValues[L"EX"] = NLPPartOfSpeech::POS::Pronoun;
    m_mapStringValues[L"WP"] = NLPPartOfSpeech::POS::Pronoun; // type:interrogative
    m_mapStringValues[L"PRP"] = NLPPartOfSpeech::POS::Pronoun; // type:personal
    m_mapStringValues[L"PRP$"] = NLPPartOfSpeech::POS::Pronoun; // type:possessive
    m_mapStringValues[L"WP$"] = NLPPartOfSpeech::POS::Pronoun; // type:possessive
    // Verb
    m_mapStringValues[L"MD"] = NLPPartOfSpeech::POS::Verb; // modal
    m_mapStringValues[L"VBG"] = NLPPartOfSpeech::POS::Verb; // gerund
    m_mapStringValues[L"VB"] = NLPPartOfSpeech::POS::Verb; // infinitive
    m_mapStringValues[L"VBN"] = NLPPartOfSpeech::POS::Verb; // participle
    m_mapStringValues[L"VBD"] = NLPPartOfSpeech::POS::Verb; // past
    m_mapStringValues[L"VBP"] = NLPPartOfSpeech::POS::Verb; // personal
    m_mapStringValues[L"VBZ"] = NLPPartOfSpeech::POS::Verb; // personal person
  }

  NLPPartOfSpeech::POS getMapping(const std::wstring &pos) {
    if (m_mapStringValues.count(pos)) {
      return m_mapStringValues[pos];
    } else if (std::wcscmp(&pos.at(0), L"F") == 0) {
      return NLPPartOfSpeech::POS::Punctuation;
    }
    return NLPPartOfSpeech::POS::Unknown;
  }
private:
  std::map<std::wstring, NLPPartOfSpeech::POS> m_mapStringValues;
};

#endif // NLPWORD_H
