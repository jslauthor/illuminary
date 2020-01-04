#ifndef NLPSENTENCES_H
#define NLPSENTENCES_H

#include <QObject>
#include <QAbstractListModel>
#include <QVector>
#include "nlpword.h"
#include "nlpsentence.h"

class NLPSentencesModel : public QAbstractListModel
{
  Q_OBJECT
public:
  enum Roles {
    SentenceRole = Qt::UserRole + 1,
  };

  explicit NLPSentencesModel(QObject *parent = nullptr);

  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role) const;
  void addSentence(NLPSentenceModel* const &sentence);

Q_SIGNALS:
protected:
  QVector<NLPSentenceModel*> m_sentences;
  QHash<int, QByteArray> roleNames() const;
};

#endif // NLPSENTENCES_H
