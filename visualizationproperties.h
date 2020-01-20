#ifndef VISUALIZATIONPROPERTIES_H
#define VISUALIZATIONPROPERTIES_H

#include <QObject>

class VisualizationProperties : public QObject
{
  Q_OBJECT
public:
  explicit VisualizationProperties(QObject *parent = nullptr);
  Q_PROPERTY(int wordWidth READ wordWidth WRITE setWordWidth NOTIFY wordWidthChanged)
  Q_PROPERTY(int wordHeight READ wordHeight WRITE setWordHeight NOTIFY wordHeightChanged)

  int wordWidth() const;
  void setWordWidth(int wordWidth);

  int wordHeight() const;
  void setWordHeight(int wordHeight);

Q_SIGNALS:
  void wordWidthChanged();
  void wordHeightChanged();
protected:
  int m_wordWidth = 12;
  int m_wordHeight = 10;

};

#endif // VISUALIZATIONPROPERTIES_H
