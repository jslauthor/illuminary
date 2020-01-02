#include "nlpword.h"

PartOfSpeechMapping NLPWord::m_posMap;

NLPWord::NLPWord(QObject *parent) : QObject(parent)
{
  m_pos = PartOfSpeech::Unknown;
}

NLPWord::PartOfSpeech NLPWord::pos() {
  return m_pos;
}

void NLPWord::parseWord(const freeling::word word) {
  m_word = word;
  m_pos = NLPWord::m_posMap.getMapping(word.get_tag());
}
