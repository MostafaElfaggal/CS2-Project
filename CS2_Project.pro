QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bullet.cpp \
    character.cpp \
    enemy.cpp \
    enemy1.cpp \
    enemy2.cpp \
    game.cpp \
    gameobject.cpp \
    grass.cpp \
    main.cpp \
    player.cpp \
    wall.cpp

HEADERS += \
    bullet.h \
    character.h \
    enemy.h \
    enemy1.h \
    enemy2.h \
    game.h \
    gameobject.h \
    grass.h \
    player.h \
    wall.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
