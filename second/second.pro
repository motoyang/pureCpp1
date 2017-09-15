TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    luapp.cpp \
    luaobject.cpp \
    auto.cpp \
    luaauto.cpp

DISTFILES += \
    auto1.lua

HEADERS += \
    luapp.h \
    ../include/purecpp1.h \
    luaobject.h \
    auto.h \
    luaauto.h \
    precompiled.h

# Use Precompiled headers (PCH)
PRECOMPILED_HEADER = precompiled.h

INCLUDEPATH += /usr/local/include ../include
LIBS += -L/usr/local/lib -llua
