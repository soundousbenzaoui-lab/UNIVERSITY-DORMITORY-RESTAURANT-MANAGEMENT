QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET   = UDRMS
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    Student.cpp \
    Room.cpp \
    Restaurant.cpp \
    Dormitory.cpp \
    University.cpp

HEADERS += \
    mainwindow.h \
    Student.h \
    Room.h \
    Restaurant.h \
    Dormitory.h \
    University.h

FORMS += \
    mainwindow.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
