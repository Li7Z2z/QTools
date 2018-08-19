#-------------------------------------------------
#
# Project created by QtCreator 2018-06-10T18:14:51
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTools
TEMPLATE = app

RC_ICONS = Icon/QTools.ico

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        QTools.cpp \
    FontIcons.cpp \
    TitleBar.cpp \
    Utils.cpp \
    ConfigFile.cpp \
    DbUtils.cpp \
    ToolBox.cpp \
    pugixml.cpp \
    ListWidget.cpp \
    XmlData.cpp

HEADERS += \
        QTools.h \
    FontIcons.h \
    TitleBar.h \
    Utils.h \
    ConfigFile.h \
    DbUtils.h \
    ToolBox.h \
    pugiconfig.hpp \
    pugixml.hpp \
    ListWidget.h \
    XmlData.h

FORMS += \
        QTools.ui

RESOURCES += \
    font.qrc \
    icon.qrc \
    qss.qrc

DISTFILES += \
    Image/Alibaba/add (1).png \
    Image/Alibaba/add (2).png \
    Image/Alibaba/box (1).png \
    Image/Alibaba/box (2).png \
    Image/Alibaba/close (1).png \
    Image/Alibaba/close (2).png \
    Image/Alibaba/color (1).png \
    Image/Alibaba/color (2).png \
    Image/Alibaba/delete (1).png \
    Image/Alibaba/delete (2).png \
    Image/Alibaba/download (1).png \
    Image/Alibaba/download (2).png \
    Image/Alibaba/edit (1).png \
    Image/Alibaba/edit (2).png \
    Image/Alibaba/iconfont-fuzhuangneiyi (1).png \
    Image/Alibaba/iconfont-fuzhuangneiyi (2).png \
    Image/Alibaba/minus (1).png \
    Image/Alibaba/minus (2).png \
    Image/Alibaba/process (1).png \
    Image/Alibaba/process (2).png \
    Image/Alibaba/search (1).png \
    Image/Alibaba/search (2).png \
    Image/Alibaba/search (3).png \
    Image/Alibaba/search (4).png \
    Image/Alibaba/search (5).png \
    Image/Alibaba/set (1).png \
    Image/Alibaba/set (2).png \
    Image/Alibaba/关闭 (1).png
