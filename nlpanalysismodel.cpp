#include "nlpanalysismodel.h"

NLPAnalysisModel::NLPAnalysisModel(QObject *parent) : QAbstractListModel(parent)
{

}

NLPAnalysisModel::~NLPAnalysisModel() {

}

int NLPAnalysisModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  return m_words.count();
}

QVariant NLPAnalysisModel::data(const QModelIndex &index, int role) const {
  if (index.row() < 0 || index.row() >= m_words.count())
      return QVariant();

  const NLPWord &word = m_words[index.row()];

  if (role == WordRole)
      return word.word();
  else if (role == POSRole)
      return word.pos();
  else if (role == WordLengthInSentenceRole)
      return word.averageWordLengthInSentence;
  else if (role == EndOfSentenceRole)
      return word.getEndOfSentence();
  else if (role == EndOfParagraphRole)
      return word.getEndOfParagraph();

  return QVariant();
}

void NLPAnalysisModel::addWord(NLPWord const &word) {
  beginInsertRows(QModelIndex(), rowCount(), rowCount());
  m_words.push_back(word);
  endInsertRows();
}

QHash<int, QByteArray> NLPAnalysisModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[WordRole] = "word";
  roles[POSRole] = "pos";
  roles[WordLengthInSentenceRole] = "averageLengthInSentence";
  roles[EndOfSentenceRole] = "isEndOfSentence";
  roles[EndOfParagraphRole] = "isEndOfParagraph";
  return roles;
}

