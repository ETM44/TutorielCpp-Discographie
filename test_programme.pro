CONFIG += c++17
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    discographie.cpp \
    donnees_disco.cpp \
    donnees_disco_tests.cpp \
    main.cpp \
    systeme_commandes.cpp \
    utils.cpp

HEADERS += \
    discographie.hpp \
    donnees_disco.hpp \
    donnees_disco_tests.hpp \
    systeme_commandes.hpp \
    utils.hpp
