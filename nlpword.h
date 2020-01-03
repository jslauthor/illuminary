#ifndef NLPWORD_H
#define NLPWORD_H

#include <QObject>
#include "freeling.h"

class PartOfSpeechMapping;

/*
 * The analyzed word. The main primitive for our data visualization.
 **/

class NLPWord : public QObject
{
  Q_OBJECT
  Q_PROPERTY(PartOfSpeech pos READ pos)
  Q_PROPERTY(QString word READ word)
public:
  explicit NLPWord(QObject *parent = nullptr);

  enum PartOfSpeech {
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
  Q_ENUM(PartOfSpeech)

  PartOfSpeech pos();
  QString word();

  void parseWord(const freeling::word word); // create copy parse and store it

Q_SIGNALS:

protected:
  PartOfSpeech m_pos;
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
    m_mapStringValues[L"JJ"] = NLPWord::PartOfSpeech::Adjective;
    m_mapStringValues[L"JJR"] = NLPWord::PartOfSpeech::Adjective;
    m_mapStringValues[L"JJS"] = NLPWord::PartOfSpeech::Adjective;
    // Adposition
    m_mapStringValues[L"POS"] = NLPWord::PartOfSpeech::Adposition;
    // Adverb
    m_mapStringValues[L"RB"] = NLPWord::PartOfSpeech::Adverb;
    m_mapStringValues[L"RBR"] = NLPWord::PartOfSpeech::Adverb;
    m_mapStringValues[L"RBS"] = NLPWord::PartOfSpeech::Adverb;
    m_mapStringValues[L"WRB"] = NLPWord::PartOfSpeech::Adverb;
    // Conjunction
    m_mapStringValues[L"CC"] = NLPWord::PartOfSpeech::Conjunction;
    // Determiner
    m_mapStringValues[L"DT"] = NLPWord::PartOfSpeech::Determiner;
    m_mapStringValues[L"WDT"] = NLPWord::PartOfSpeech::Determiner; // type:interrogative
    m_mapStringValues[L"PDT"] = NLPWord::PartOfSpeech::Determiner; // type:predeterminer
    // Interjection
    m_mapStringValues[L"UH"] = NLPWord::PartOfSpeech::Interjection;
    // Noun
    m_mapStringValues[L"NNS"] = NLPWord::PartOfSpeech::Noun; // plural
    m_mapStringValues[L"NN"] = NLPWord::PartOfSpeech::Noun; // singular
    m_mapStringValues[L"NNP"] = NLPWord::PartOfSpeech::Noun; // proper
    m_mapStringValues[L"NP00000"] = NLPWord::PartOfSpeech::Noun; // proper
    m_mapStringValues[L"NP"] = NLPWord::PartOfSpeech::Noun; // proper
    m_mapStringValues[L"NP00G00"] = NLPWord::PartOfSpeech::Noun; // proper
    m_mapStringValues[L"NP00O00"] = NLPWord::PartOfSpeech::Noun; // proper
    m_mapStringValues[L"NP00V00"] = NLPWord::PartOfSpeech::Noun; // proper
    m_mapStringValues[L"NP00SP0"] = NLPWord::PartOfSpeech::Noun; // proper
    m_mapStringValues[L"NNPS"] = NLPWord::PartOfSpeech::Noun; // proper
    // Article
    m_mapStringValues[L"RP"] = NLPWord::PartOfSpeech::Article;
    m_mapStringValues[L"TO"] = NLPWord::PartOfSpeech::Article;
    // Proposition
    m_mapStringValues[L"IN"] = NLPWord::PartOfSpeech::Preposition;
    // Pronoun
    m_mapStringValues[L"EX"] = NLPWord::PartOfSpeech::Pronoun;
    m_mapStringValues[L"WP"] = NLPWord::PartOfSpeech::Pronoun; // type:interrogative
    m_mapStringValues[L"PRP"] = NLPWord::PartOfSpeech::Pronoun; // type:personal
    m_mapStringValues[L"PRP$"] = NLPWord::PartOfSpeech::Pronoun; // type:possessive
    m_mapStringValues[L"WP$"] = NLPWord::PartOfSpeech::Pronoun; // type:possessive
    // Verb
    m_mapStringValues[L"MD"] = NLPWord::PartOfSpeech::Verb; // modal
    m_mapStringValues[L"VBG"] = NLPWord::PartOfSpeech::Verb; // gerund
    m_mapStringValues[L"VB"] = NLPWord::PartOfSpeech::Verb; // infinitive
    m_mapStringValues[L"VBN"] = NLPWord::PartOfSpeech::Verb; // participle
    m_mapStringValues[L"VBD"] = NLPWord::PartOfSpeech::Verb; // past
    m_mapStringValues[L"VBP"] = NLPWord::PartOfSpeech::Verb; // personal
    m_mapStringValues[L"VBZ"] = NLPWord::PartOfSpeech::Verb; // personal person
  }

  NLPWord::PartOfSpeech getMapping(const std::wstring &pos) {
    if (m_mapStringValues.count(pos)) {
      return m_mapStringValues[pos];
    } else if (std::wcscmp(&pos.at(0), L"F") == 0) {
      return NLPWord::PartOfSpeech::Punctuation;
    }
    return NLPWord::PartOfSpeech::Unknown;
  }
private:
  std::map<std::wstring, NLPWord::PartOfSpeech> m_mapStringValues;
};

#endif // NLPWORD_H
