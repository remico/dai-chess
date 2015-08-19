TEMPLATE = app

QT += qml quick widgets
CONFIG += c++11

# disable debugging output to console in release mode
CONFIG(release, debug|release): DEFINES += QT_NO_DEBUG_OUTPUT

SOURCES += src/main.cpp \
    src/chessgame.cpp

HEADERS += \
    src/chessgame.h \
    src/historymodel.h \
    src/gamefield.h \
    src/validator/ivalidator.h \
    src/validator/pawnvalidator.h \
    src/validator/rookvalidator.h \
    src/validator/knightvalidator.h \
    src/validator/bishopvalidator.h \
    src/validator/queenvalidator.h \
    src/validator/kingvalidator.h

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES += \
    qml/*.qml \
