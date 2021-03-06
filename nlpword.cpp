#include "nlpword.h"

PartOfSpeechMapping NLPWord::pos_map;

NLPWord::NLPWord()
{
  m_pos = NLPPartOfSpeech::POS::Unknown;
}

NLPPartOfSpeech::POS NLPWord::pos() const {
  return m_pos;
}

QString NLPWord::word() const {
  return m_form;
}

void NLPWord::parseWord(const freeling::word word) {
  m_word = word;
  m_form = QString::fromStdWString(word.get_form());
  m_pos = NLPWord::pos_map.getMapping(word.get_tag());
}

freeling::sentence NLPWord::getSentence() const
{
  return m_sentence;
}

void NLPWord::setSentence(const freeling::sentence &sentence)
{
  m_sentence = sentence;
}

bool NLPWord::getEndOfSentence() const
{
  return m_endOfSentence;
}

void NLPWord::setEndOfSentence(bool endOfSentence)
{
  m_endOfSentence = endOfSentence;
}

bool NLPWord::getEndOfParagraph() const
{
  return m_endOfParagraph;
}

void NLPWord::setEndOfParagraph(bool endOfParagraph)
{
  m_endOfParagraph = endOfParagraph;
}
