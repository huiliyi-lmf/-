QT       += core gui
QT += charts
QT += network

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
    Create_Peo.cpp \
    Find_password.cpp \
    check.cpp \
    io_baseB.cpp \
    main.cpp \
    mainwindow.cpp \
    qurry.cpp \
    send_email.cpp \
    sort.cpp \
    vote.cpp

HEADERS += \
    Create_Peo.h \
    Find_password.h \
    check.h \
    class_base.h \
    io_baseB.h \
    mainwindow.h \
    qurry.h \
    send_email.h \
    sort.h \
    vote.h

FORMS += \
    create_peo.ui \
    find_password.ui \
    mainwindow.ui \
    vote.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
