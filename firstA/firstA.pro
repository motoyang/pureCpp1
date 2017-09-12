TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    check_type.cpp \
    has_member_test.cpp

HEADERS += \
    check_type.hpp \
    firstA.h \
    factorial.hpp \
    has_member.h \
    timer.hpp \
    cache.hpp \
    router.hpp \
    function_traits.hpp
