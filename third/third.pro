TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt core

SOURCES += main.cpp \
    luaspdloger.cpp \
    spdloger.cpp \
    ../luapp/luapp.cpp

HEADERS += \
    precompiled.h \
    luaspdloger.h \
    spdloger.h \
    ../luapp/luapp.h

# Use Precompiled headers (PCH)
PRECOMPILED_HEADER = precompiled.h

INCLUDEPATH += /usr/local/include ../include
LIBS += -L/usr/local/lib -llua

QMAKE_CXXFLAGS -= -mmacosx-version-min=10.9
QMAKE_CXXFLAGS += -fvisibility=hidden
QMAKE_LFLAGS -= -mmacosx-version-min=10.9
#QMAKE_LFLAGS += -mmacosx-version-min=10.12
#QMAKE_LFLAGS += -shared -fPIC
