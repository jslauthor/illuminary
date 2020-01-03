#include "appstate.h"

AppState::AppState()
{
  m_parser = new NLPParser();
}

AppState::~AppState() {
  delete m_parser;
}

void AppState::loadFile(const QString& filename) {
  QFile file(QUrl(filename).toLocalFile());
  if (!file.open(QIODevice::ReadOnly)) {
    qWarning("%s", file.errorString().toStdString().c_str());
  }
  QTextStream in(&file);
  QString text = in.readAll();

  list<freeling::sentence> sentences = m_parser->parse(text.toStdWString());

  clearSentences();

  // Naive copy to NLPSentence/NLPWord
  sentence::const_iterator word;
  for (list<freeling::sentence>::iterator is = sentences.begin(); is != sentences.end(); is++) {
    NLPSentence nlpsentence;
    for (word = is->begin(); word != is->end(); word++) {
      NLPWord nlpword;
      nlpword.parseWord(*word);
      nlpsentence.appendWord(&nlpword);
    }
    appendSentence(&nlpsentence);
  }

  file.close();
  Q_EMIT sentencesChanged();
}

QQmlListProperty<NLPSentence> AppState::sentences()
{
    return {this, this,
//             &AppState::appendSentence,
             &AppState::sentenceCount,
             &AppState::sentence,
//             &AppState::clearSentences
    };
}

void AppState::appendSentence(NLPSentence *sentence) {
  m_sentences.append(std::move(sentence));
}

int AppState::sentenceCount() const {
  return m_sentences.count();
}

NLPSentence *AppState::sentence(int index) const {
  return m_sentences.at(index);
}

void AppState::clearSentences() {
  m_sentences.clear();
}

void AppState::appendSentence(QQmlListProperty<NLPSentence>* list, NLPSentence* sentence) {
  reinterpret_cast<AppState*>(list->data)->appendSentence(sentence);
}

int AppState::sentenceCount(QQmlListProperty<NLPSentence>* list) {
  return reinterpret_cast<AppState*>(list->data)->sentenceCount();
}

NLPSentence* AppState::sentence(QQmlListProperty<NLPSentence>* list, int index) {
  return reinterpret_cast<AppState*>(list->data)->sentence(index);
}

void AppState::clearSentences(QQmlListProperty<NLPSentence>* list) {
  reinterpret_cast<AppState*>(list->data)->clearSentences();
}
