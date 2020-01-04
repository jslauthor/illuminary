QT += quick widgets
CONFIG += c++17 no_keywords

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
  appstate.cpp \
  nlpparser.cpp \
  nlpsentence.cpp \
  nlpsentences.cpp \
  nlpword.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
  appstate.h \
  nlpparser.h \
  nlpsentence.h \
  nlpsentences.h \
  nlpword.h

INCLUDEPATH += /usr/local/include/boost_1_71_0/include/ \
  /usr/local/opt/icu4c/include \
  /usr/local/include

#INCLUDEPATH += /usr/local/opt/Frameworks/Python.framework/Versions/2.7/include/python2.7
QMAKE_LFLAGS += -L/usr/local/lib -lfreeling

#LIBS =+
