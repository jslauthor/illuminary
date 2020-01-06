#ifndef COLORMODEL_H
#define COLORMODEL_H

#include <QObject>
#include <QColor>
#include <QAbstractListModel>
#include <QVariantMap>
#include "nlpword.h"

class ColorModel : public QAbstractListModel
{
  Q_OBJECT
public:
  explicit ColorModel(QObject *parent = nullptr);
  ~ColorModel() override;
  ColorModel(const ColorModel &other) {
    m_pos = other.m_pos;
  }

  enum Roles {
    ColorRole = Qt::UserRole + 1,
    POSRole
  };

  Q_INVOKABLE QColor getColor(int);
  Q_INVOKABLE void setColor(NLPPartOfSpeech::POS, QColor&);

  int rowCount(const QModelIndex &parent = QModelIndex()) const  override;
  QVariant data(const QModelIndex &index, int role) const override;

Q_SIGNALS:
  void colorChanged();
protected:
  QList<NLPPartOfSpeech::POS> m_pos;
  std::map<NLPPartOfSpeech::POS, QColor> m_pos_colors;
  QHash<int, QByteArray> roleNames() const override;
};

Q_DECLARE_METATYPE(ColorModel)

#endif // COLORMODEL_H
