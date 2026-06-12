QT += core
QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

# --- ВСТАВ СВОЇ ШЛЯХИ ТУТ ---
# УВАГА: змініть "C:/SFML-2.6.1" на той шлях, де реально лежить папка!
# Використовуй тільки ПРЯМІ слеші (/)
INCLUDEPATH += "D:/SFML-2.6.2/include"
LIBS += -L"D:/SFML-2.6.2/lib"

# Підключення модулів
LIBS += -lsfml-graphics -lsfml-window -lsfml-system
# --------------------------

SOURCES += main.cpp \
    animation.cpp \
    apteczka.cpp \
    arena.cpp \
    buttons.cpp \
    characterSelect.cpp \
    engine.cpp \
    mainMenu.cpp \
    player.cpp \
    settings.cpp

HEADERS += \
    gameobject.h \
    animation.h \
    apteczka.h \
    arena.h \
    buttons.h \
    characterSelect.h \
    engine.h \
    gameobject.h \
    mainMenu.h \
    player.h \
    settings.h

RESOURCES +=