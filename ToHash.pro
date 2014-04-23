QT       += core gui

TARGET = ToHash
TEMPLATE = app

TRANSLATIONS += translations/ToHash_Ru.ts

DESTDIR = ../bin

SOURCES += main.cpp\
        mainwindow.cpp \
        crc32.cpp \
    about.cpp

HEADERS  += mainwindow.h \
        crc32.h \
    about.h

FORMS    += mainwindow.ui \
    about.ui

RESOURCES += \
    ToHash.qrc
