TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    luapp.cpp \
    printf.cpp

DISTFILES +=

HEADERS += \
    luapp.h \
    ../include/purecpp1.h \
    precompiled.h \
    printf.h \
    lprefix.h

# Use Precompiled headers (PCH)
PRECOMPILED_HEADER = precompiled.h

INCLUDEPATH += /usr/local/include ../include
LIBS += -L/usr/local/lib -llua
