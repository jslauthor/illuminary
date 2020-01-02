#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QDebug>
#include "nlpparser.h"
#include "nlpsentence.h"
#include "nlpword.h"

int main(int argc, char *argv[])
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication app(argc, argv);


  qmlRegisterType<NLPWord>("NLP", 1,0, "Word");
  qmlRegisterType<NLPSentence>("NLP", 1,0, "Sentence");
  NLPParser parser;

  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:/main.qml"));

  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                   &app, [url](QObject *obj, const QUrl &objUrl) {
    if (!obj && url == objUrl)
      QCoreApplication::exit(-1);
  }, Qt::QueuedConnection);

  engine.rootContext()->setContextProperty("NLPParser", &parser);
  engine.load(url);

  return app.exec();
}
