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

    // Punctuation
    Colon,
    Comma,
    CurlyOpen,
    CurlyClose,
    Etc,
    ExclamationMarkOpen,
    ExclamationMarkClosed,
    Hyphen,
    Other,
    ParenthesisOpen,
    ParenthesisClosed,
    Percentage,
    Period,
    QuestionMarkOpen,
    QuestionMarkClosed,
    Quotation,
    QuotationOpen,
    QuotationClosed,
    Semicolon,
    Slash,
    SquareOpen,
    SquareClosed,

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
    averageWordLengthInSentence = other.averageWordLengthInSentence;
  }

  NLPPartOfSpeech::POS pos() const;
  QString word() const;

  void parseWord(const freeling::word word); // create copy parse and store it

  freeling::sentence getSentence() const;
  void setSentence(const freeling::sentence &sentence);

  qreal averageWordLengthInSentence = 0.0;

Q_SIGNALS:

protected:
  NLPPartOfSpeech::POS m_pos;
  QString m_form;
  freeling::word m_word;
  freeling::sentence m_sentence;

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
    // Punctuation
    m_mapStringValues[L"Fd"] = NLPPartOfSpeech::POS::Colon;
    m_mapStringValues[L"Fc"] = NLPPartOfSpeech::POS::Comma;
    m_mapStringValues[L"Flt"] = NLPPartOfSpeech::POS::CurlyClose;
    m_mapStringValues[L"Fla"] = NLPPartOfSpeech::POS::CurlyOpen;
    m_mapStringValues[L"Fs"] = NLPPartOfSpeech::POS::Etc;
    m_mapStringValues[L"Fat"] = NLPPartOfSpeech::POS::ExclamationMarkClosed;
    m_mapStringValues[L"Faa"] = NLPPartOfSpeech::POS::ExclamationMarkOpen;
    m_mapStringValues[L"Fg"] = NLPPartOfSpeech::POS::Hyphen;
    m_mapStringValues[L"Fz"] = NLPPartOfSpeech::POS::Other;
    m_mapStringValues[L"Fpt"] = NLPPartOfSpeech::POS::ParenthesisClosed;
    m_mapStringValues[L"Fpa"] = NLPPartOfSpeech::POS::ParenthesisOpen;
    m_mapStringValues[L"Ft"] = NLPPartOfSpeech::POS::Percentage;
    m_mapStringValues[L"Fp"] = NLPPartOfSpeech::POS::Period;
    m_mapStringValues[L"Fit"] = NLPPartOfSpeech::POS::QuestionMarkClosed;
    m_mapStringValues[L"Fia"] = NLPPartOfSpeech::POS::QuestionMarkOpen;
    m_mapStringValues[L"Fe"] = NLPPartOfSpeech::POS::Quotation;
    m_mapStringValues[L"Frc"] = NLPPartOfSpeech::POS::QuotationClosed;
    m_mapStringValues[L"Fra"] = NLPPartOfSpeech::POS::QuotationOpen;
    m_mapStringValues[L"Fx"] = NLPPartOfSpeech::POS::Semicolon;
    m_mapStringValues[L"Fh"] = NLPPartOfSpeech::POS::Slash;
    m_mapStringValues[L"Fct"] = NLPPartOfSpeech::POS::SquareClosed;
    m_mapStringValues[L"Fca"] = NLPPartOfSpeech::POS::SquareOpen;
  }

  NLPPartOfSpeech::POS getMapping(const std::wstring &pos) {
    if (m_mapStringValues.count(pos) > 0) {
      return m_mapStringValues.at(pos);
    }
    return NLPPartOfSpeech::POS::Unknown;
  }
private:
  std::map<std::wstring, NLPPartOfSpeech::POS> m_mapStringValues;
};

#endif // NLPWORD_H
