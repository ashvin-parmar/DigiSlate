QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    drawing.cpp \
    groupshape.cpp \
    model.cpp \
    main.cpp \
    mainwindow.cpp \
    shapes_src/arcshape.cpp \
    shapes_src/ellipseshape.cpp \
    shapes_src/freehandshape.cpp \
    shapes_src/lineshape.cpp \
    shapes_src/pixmapshape.cpp \
    shapes_src/pointshape.cpp \
    shapes_src/polygonshape.cpp \
    shapes_src/polylineshape.cpp \
    shapes_src/rectangleshape.cpp \
    shapes_src/roundedrectangleshape.cpp \
    shapes_src/textshape.cpp

HEADERS += \
    drawing.h \
    groupshape.h \
    model.h \
    mainwindow.h \
    shapes_header/arcshape.h \
    shapes_header/ellipseshape.h \
    shapes_header/freehandshape.h \
    shapes_header/lineshape.h \
    shapes_header/pixmapshape.h \
    shapes_header/pointshape.h \
    shapes_header/polygonshape.h \
    shapes_header/polylineshape.h \
    shapes_header/rectangleshape.h \
    shapes_header/roundedrectangleshape.h \
    shapes_header/textshape.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
