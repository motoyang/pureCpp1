TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    student.cpp \
    luapp.cpp \
    luaobject.cpp

INCLUDEPATH += /usr/local/include ../include
LIBS += -L/usr/local/lib -llua

DISTFILES += \
    hello.lua

HEADERS += \
    student.h \
    luapp.h \
    ../include/purecpp1.h \
    luaobject.h
