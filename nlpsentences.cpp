#include "nlpsentences.h"

NLPSentencesModel::NLPSentencesModel(QObject *parent) : QAbstractListModel(parent)
{

}

int NLPSentencesModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  return m_sentences.count();
}

QVariant NLPSentencesModel::data(const QModelIndex &index, int role) const {
  if (index.row() < 0 || index.row() >= m_sentences.count())
      return QVariant();

  const NLPSentenceModel &sentence = *m_sentences.at(index.row());
  if (role == SentenceRole) {
    QVariant s = QVariant::fromValue(sentence);
    return s;
  }

  return QVariant();
}

void NLPSentencesModel::addSentence(NLPSentenceModel* const &sentence) {
  beginInsertRows(QModelIndex(), rowCount(), rowCount());
  m_sentences.push_back(sentence);
  endInsertRows();
}

QHash<int, QByteArray> NLPSentencesModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[SentenceRole] = "sentence";
  return roles;
}

