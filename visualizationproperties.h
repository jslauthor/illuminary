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
  Q_PROPERTY(int wordPadding READ wordPadding WRITE setWordPadding NOTIFY wordPaddingChanged)
  Q_PROPERTY(int sentencePadding READ sentencePadding WRITE setSentencePadding NOTIFY sentencePaddingChanged)
  Q_PROPERTY(int paragraphPadding READ paragraphPadding WRITE setParagraphPadding NOTIFY paragraphPaddingChanged)

  int wordWidth() const;
  void setWordWidth(int wordWidth);

  int wordHeight() const;
  void setWordHeight(int wordHeight);

  int wordPadding() const;
  void setWordPadding(int wordPadding);

  int sentencePadding() const;
  void setSentencePadding(int sentencePadding);

  int paragraphPadding() const;
  void setParagraphPadding(int paragraphPadding);

Q_SIGNALS:
  void wordWidthChanged();
  void wordHeightChanged();
  void wordPaddingChanged();
  void sentencePaddingChanged();
  void paragraphPaddingChanged();

protected:
  int m_wordWidth = 12;
  int m_wordHeight = 10;
  int m_wordPadding = 1;
  int m_sentencePadding = 5;
  int m_paragraphPadding = 0;
};

#endif // VISUALIZATIONPROPERTIES_H
