#-------------------------------------------------
#
# Project created by QtCreator 2012-04-07T02:33:03
#
#-------------------------------------------------

QT       += core gui
LIBS+= -lX11 -lXmu -lXrender -lXcomposite -lXdamage
TARGET = ScaleWine
TEMPLATE = app


SOURCES += main.cpp\
    xutil.cpp \
    scalewine.cpp \
    scaledcontainer.cpp

HEADERS  += \
    xutil.h \
    scalewine.h \
    scaledcontainer.h

FORMS    += mainwindow.ui
