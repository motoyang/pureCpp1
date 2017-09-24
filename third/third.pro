TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

HEADERS += \
    precompiled.h

# Use Precompiled headers (PCH)
PRECOMPILED_HEADER = precompiled.h

INCLUDEPATH += /usr/local/include ../include
LIBS += -L/usr/local/lib -llua
