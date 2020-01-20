#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include "appstate.h"
#include "nlpanalysismodel.h"
#include "nlpword.h"
#include "nlpanalysisthread.h"
#include "visualizationproperties.h"

int main(int argc, char *argv[])
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication app(argc, argv);

  qRegisterMetaType<CompletedAnalysis>();
  qmlRegisterUncreatableType<NLPPartOfSpeech>("NLP", 1,0, "PartOfSpeech", "Not creatable - for enums only");

  AppState appState;
  VisualizationProperties visualizationProperties;

  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:/main.qml"));

  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                   &app, [url](QObject *obj, const QUrl &objUrl) {
    if (!obj && url == objUrl)
      QCoreApplication::exit(-1);
  }, Qt::QueuedConnection);

  engine.rootContext()->setContextProperty("AppState", &appState);
  engine.rootContext()->setContextProperty("VisualizationProperties", &visualizationProperties);
  engine.load(url);

  return app.exec();
}
