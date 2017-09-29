QT       -= core gui

TARGET = lualogger
TEMPLATE = lib
CONFIG += c++14 shared

SOURCES += main.cpp \
    luaspdloger.cpp \
    spdloger.cpp \
    ../luapp/luapp.cpp \
    fun.cpp \
    export.cpp

HEADERS += \
    precompiled.h \
    luaspdloger.h \
    spdloger.h \
    ../luapp/luapp.h \
    fun.h \
    export.h


unix {
    target.path = /usr/lib
    INSTALLS += target
}

# Use Precompiled headers (PCH)
PRECOMPILED_HEADER = precompiled.h

INCLUDEPATH += /usr/local/include ../include
LIBS += -L/usr/local/lib -llua

QMAKE_CXXFLAGS -= -mmacosx-version-min=10.9
QMAKE_CXXFLAGS += -fvisibility=hidden
QMAKE_LFLAGS -= -mmacosx-version-min=10.9
#QMAKE_LFLAGS += -mmacosx-version-min=10.12
#QMAKE_LFLAGS += -shared -fPIC
