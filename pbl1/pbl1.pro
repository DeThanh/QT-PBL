QT       += core gui sql \
            multimedia \

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    login.cpp \
    show.cpp \
    studentinfo.cpp\

HEADERS += \
    libs.h \
    login.h \
    show.h \
    studentinfo.h \

FORMS += \
    login.ui \
    show.ui \
    studentinfo.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
RESOURCES += \
    asset.qrc \
    asset.qrc \
    asset.qrc \
    sounds.qrc

RC_ICONS=1.ico

DISTFILES +=
