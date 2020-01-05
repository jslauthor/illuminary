#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include "appstate.h"
#include "nlpsentence.h"
#include "nlpword.h"

int main(int argc, char *argv[])
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication app(argc, argv);

  qmlRegisterUncreatableType<NLPPartOfSpeech>("NLP", 1,0, "PartOfSpeech", "Not creatable - for enums only");
//  qmlRegisterType<NLPSentenceModel>("NLP", 1,0, "Sentence");
//  qmlRegisterType<NLPSentencesModel>("NLP", 1,0, "Sentences");
  AppState appState;

  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:/main.qml"));

  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                   &app, [url](QObject *obj, const QUrl &objUrl) {
    if (!obj && url == objUrl)
      QCoreApplication::exit(-1);
  }, Qt::QueuedConnection);

  engine.rootContext()->setContextProperty("AppState", &appState);
  engine.load(url);

  return app.exec();
}
