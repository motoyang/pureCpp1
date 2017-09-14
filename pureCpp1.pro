TEMPLATE = subdirs

SUBDIRS += \
    firstA \
    second \
    third

macx:QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.12
macx:QMAKE_MAC_SDK=macosx10.12
