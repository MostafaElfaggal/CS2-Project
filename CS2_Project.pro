QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Button.cpp \
    block.cpp \
    bullet.cpp \
    character.cpp \
    door.cpp \
    enemy.cpp \
    enemy1.cpp \
    enemy2.cpp \
    game.cpp \
    gameobject.cpp \
    main.cpp \
    mainmenu.cpp \
    mainwindow.cpp \
    player.cpp \
    wall.cpp \
    winlose_status.cpp

HEADERS += \
    Button.h \
    block.h \
    bullet.h \
    character.h \
    door.h \
    enemy.h \
    enemy1.h \
    enemy2.h \
    game.h \
    gameobject.h \
    mainmenu.h \
    mainwindow.h \
    player.h \
    wall.h \
    winlose_status.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

FORMS += \
    mainwindow.ui
