QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Button.cpp \
    bar.cpp \
    block.cpp \
    boss.cpp \
    bullet.cpp \
    character.cpp \
    clickableimage.cpp \
    door.cpp \
    enemy.cpp \
    enemy1.cpp \
    enemy2.cpp \
    explosion.cpp \
    flame.cpp \
    game.cpp \
    gameitem.cpp \
    gameobject.cpp \
    healthpot.cpp \
    main.cpp \
    mainmenu.cpp \
    mainwindow.cpp \
    menu.cpp \
    pausemenu.cpp \
    player.cpp \
    rectangle.cpp \
    thunder.cpp \
    wall.cpp \
    winlose_status.cpp

HEADERS += \
    Button.h \
    bar.h \
    block.h \
    boss.h \
    bullet.h \
    character.h \
    clickableimage.h \
    door.h \
    enemy.h \
    enemy1.h \
    enemy2.h \
    explosion.h \
    flame.h \
    game.h \
    gameitem.h \
    gameobject.h \
    healthpot.h \
    mainmenu.h \
    mainwindow.h \
    menu.h \
    pausemenu.h \
    player.h \
    rectangle.h \
    thunder.h \
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
