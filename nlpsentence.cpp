#include "nlpsentence.h"

NLPSentence::NLPSentence(QObject *parent) : QObject(parent)
{

}

QQmlListProperty<NLPWord> NLPSentence::words()
{
    return {this, this,
             &NLPSentence::appendWord,
             &NLPSentence::wordCount,
             &NLPSentence::word,
             &NLPSentence::clearWords};
}

void NLPSentence::appendWord(NLPWord *word) {
  m_words.append(word);
}

int NLPSentence::wordCount() const {
  return m_words.count();
}

NLPWord *NLPSentence::word(int index) const {
  return m_words.at(index);
}

void NLPSentence::clearWords() {
  m_words.clear();
}

void NLPSentence::appendWord(QQmlListProperty<NLPWord>* list, NLPWord* word) {
  reinterpret_cast<NLPSentence*>(list->data)->appendWord(word);
}

int NLPSentence::wordCount(QQmlListProperty<NLPWord>* list) {
  return reinterpret_cast<NLPSentence*>(list->data)->wordCount();
}

NLPWord* NLPSentence::word(QQmlListProperty<NLPWord>* list, int index) {
  return reinterpret_cast<NLPSentence*>(list->data)->word(index);
}

void NLPSentence::clearWords(QQmlListProperty<NLPWord>* list) {
  reinterpret_cast<NLPSentence*>(list->data)->clearWords();
}
