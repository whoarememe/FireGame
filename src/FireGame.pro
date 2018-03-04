QT       += core gui
QT       += network
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += \
    bomb.h \
    circlebomb.h \
    squarebomb.h \
    trianglebomb.h \
    gun.h \
    tower.h \
    circletower.h \
    squaretower.h \
    triangletower.h \
    myview.h \
    towergroup.h \
    enemytowergroup.h \
    explode.h \
    skillgroup.h \
    firebutton.h \
    skillofaddbomb.h \
    skilloftowerspeed.h \
    skillofgunspeed.h \
    gunturntoleft.h \
    gunturntoright.h \
    skill.h \
    skillofwall.h \
    skillofbox.h \
    everyone.h \
    skillofreverse.h

SOURCES += \
    bomb.cpp \
    circlebomb.cpp \
    squarebomb.cpp \
    trianglebomb.cpp \
    main.cpp \
    gun.cpp \
    tower.cpp \
    circletower.cpp \
    squaretower.cpp \
    triangletower.cpp \
    myview.cpp \
    towergroup.cpp \
    enemytowergroup.cpp \
    explode.cpp \
    skillgroup.cpp \
    firebutton.cpp \
    skillofaddbomb.cpp \
    skilloftowerspeed.cpp \
    skillofgunspeed.cpp \
    gunturntoleft.cpp \
    gunturntoright.cpp \
    skill.cpp \
    skillofwall.cpp \
    skillofbox.cpp \
    everyone.cpp \
    skillofreverse.cpp

RESOURCES += \
    pic.qrc
