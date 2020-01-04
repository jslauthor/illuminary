#include "nlpword.h"

PartOfSpeechMapping NLPWord::m_posMap;

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
  m_word = std::move(word);
  m_form = QString::fromStdWString(word.get_form());
  m_pos = NLPWord::m_posMap.getMapping(word.get_tag());
}