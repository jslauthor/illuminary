#include "colormodel.h"

ColorModel::ColorModel(QObject *parent) : QAbstractListModel(parent)
{
  m_pos_colors[NLPPartOfSpeech::POS::Noun] = QColor("#C94059");
  m_pos.push_back(NLPPartOfSpeech::POS::Noun);
  m_pos_colors[NLPPartOfSpeech::POS::Verb] = QColor("#2D728F");
  m_pos.push_back(NLPPartOfSpeech::POS::Verb);
  m_pos_colors[NLPPartOfSpeech::POS::Adjective] = QColor("#3B8EA5");
  m_pos.push_back(NLPPartOfSpeech::POS::Adjective);
  m_pos_colors[NLPPartOfSpeech::POS::Adposition] = QColor("#2D3047");
  m_pos.push_back(NLPPartOfSpeech::POS::Adposition);
  m_pos_colors[NLPPartOfSpeech::POS::Adverb] = QColor("#419D78");
  m_pos.push_back(NLPPartOfSpeech::POS::Adverb);
  m_pos_colors[NLPPartOfSpeech::POS::Conjunction] = QColor("#17BEBB");
  m_pos.push_back(NLPPartOfSpeech::POS::Conjunction);
  m_pos_colors[NLPPartOfSpeech::POS::Determiner] = QColor("#2E282A");
  m_pos.push_back(NLPPartOfSpeech::POS::Determiner);
  m_pos_colors[NLPPartOfSpeech::POS::Interjection] = QColor("#EDB88B");
  m_pos.push_back(NLPPartOfSpeech::POS::Interjection);
  m_pos_colors[NLPPartOfSpeech::POS::Article] = QColor("#FAD8D6");
  m_pos.push_back(NLPPartOfSpeech::POS::Article);
  m_pos_colors[NLPPartOfSpeech::POS::Preposition] = QColor("#C94059");
  m_pos.push_back(NLPPartOfSpeech::POS::Preposition);
  m_pos_colors[NLPPartOfSpeech::POS::Pronoun] = QColor("#A1EF8B");
  m_pos.push_back(NLPPartOfSpeech::POS::Pronoun);
  m_pos_colors[NLPPartOfSpeech::POS::Unknown] = QColor("#000000");
  m_pos.push_back(NLPPartOfSpeech::POS::Unknown);
}

ColorModel::~ColorModel() {

}

QColor ColorModel::getColor(int pos) {
  if (m_pos_colors.count(static_cast<NLPPartOfSpeech::POS>(pos)) > 0) {
      return m_pos_colors.at(static_cast<NLPPartOfSpeech::POS>(pos));
  }
  return m_pos_colors[NLPPartOfSpeech::POS::Unknown];
}

void ColorModel::setColor(int pos, QColor color) {
  m_pos_colors[static_cast<NLPPartOfSpeech::POS>(pos)] = color;
  Q_EMIT dataChanged(index(pos), index(pos), QVector<int>{ColorRole});
}

int ColorModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  return m_pos.count();
}

QVariant ColorModel::data(const QModelIndex &index, int role) const {
  if (index.row() < 0 || index.row() >= m_pos.count())
      return QVariant();

  const NLPPartOfSpeech::POS &pos = m_pos[index.row()];
  if (role == ColorRole) {
    QColor c = m_pos_colors.at(pos);
    return c;
  } else if (role == POSRole) {
    return pos;
  } else if (role == LabelRole) {
    return NLPWord::pos_map.getLabel(pos);
  }

  return QVariant();
}

QHash<int, QByteArray> ColorModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[ColorRole] = "color";
  roles[POSRole] = "pos";
  roles[LabelRole] = "label";
  return roles;
}
