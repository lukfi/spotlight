TEMPLATE = lib
CONFIG += dll
QT -= core gui

INCLUDEPATH += ../../Common/System

# Set the target name of the library
TARGET = wip

# Define your source files
SOURCES += wip.cpp

# Optional: specify output directory for the DLL
DESTDIR = $$OUT_PWD/../
