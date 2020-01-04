#include "nlpsentence.h"

NLPSentenceModel::NLPSentenceModel(QObject *parent) : QAbstractListModel(parent)
{

}

NLPSentenceModel::~NLPSentenceModel() {

}

int NLPSentenceModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  return m_words.count();
}

QVariant NLPSentenceModel::data(const QModelIndex &index, int role) const {
  if (index.row() < 0 || index.row() >= m_words.count())
      return QVariant();

  const NLPWord &word = m_words[index.row()];
  if (role == WordRole)
      return word.word();
  else if (role == POSRole)
      return word.pos();

  return QVariant();
}

void NLPSentenceModel::addWord(NLPWord const &word) {
  beginInsertRows(QModelIndex(), rowCount(), rowCount());
  m_words.push_back(word);
  endInsertRows();
}

QHash<int, QByteArray> NLPSentenceModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[WordRole] = "word";
  roles[POSRole] = "pos";
  return roles;
}

