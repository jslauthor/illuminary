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
