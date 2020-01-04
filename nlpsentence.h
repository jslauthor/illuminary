#ifndef NLPSENTENCE_H
#define NLPSENTENCE_H

#include <QObject>
#include <QAbstractListModel>
#include <QVector>
#include "nlpword.h"

class NLPSentenceModel : public QAbstractListModel
{
  Q_OBJECT
public:
  enum NLPWordRoles {
    WordRole = Qt::UserRole + 1,
    POSRole
  };

  explicit NLPSentenceModel(QObject *parent = nullptr);
  ~NLPSentenceModel();
  NLPSentenceModel(const NLPSentenceModel &other) {
    m_words = other.m_words;
  }

  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role) const;
  void addWord(NLPWord const &word);
Q_SIGNALS:
protected:
  QList<NLPWord> m_words;
  QHash<int, QByteArray> roleNames() const;
};

Q_DECLARE_METATYPE(NLPSentenceModel)

#endif // NLPSENTENCE_H
