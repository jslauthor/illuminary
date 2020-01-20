#include "visualizationproperties.h"

VisualizationProperties::VisualizationProperties(QObject *parent) : QObject(parent)
{

}

int VisualizationProperties::wordWidth() const
{
  return m_wordWidth;
}

void VisualizationProperties::setWordWidth(int wordWidth)
{
  m_wordWidth = wordWidth;
  Q_EMIT wordWidthChanged();
}

int VisualizationProperties::wordHeight() const
{
  return m_wordHeight;
}

void VisualizationProperties::setWordHeight(int wordHeight)
{
  m_wordHeight = wordHeight;
  Q_EMIT wordHeightChanged();
}

int VisualizationProperties::wordPadding() const
{
  return m_wordPadding;
}

void VisualizationProperties::setWordPadding(int wordPadding)
{
  m_wordPadding = wordPadding;
  Q_EMIT wordPaddingChanged();
}

int VisualizationProperties::sentencePadding() const
{
  return m_sentencePadding;
}

void VisualizationProperties::setSentencePadding(int sentencePadding)
{
  m_sentencePadding = sentencePadding;
  Q_EMIT sentencePaddingChanged();
}

int VisualizationProperties::paragraphPadding() const
{
  return m_paragraphPadding;
}

void VisualizationProperties::setParagraphPadding(int paragraphPadding)
{
  m_paragraphPadding = paragraphPadding;
  Q_EMIT paragraphPaddingChanged();
}
