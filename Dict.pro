QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++23

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AVLTree.cpp \
    BSTree.cpp \
    Treap.cpp \
    Trie.cpp \
    home.cpp \
    main.cpp \
    wNode.cpp

HEADERS += \
    AVLTree.h \
    BSTree.h \
    RBTree.h \
    Treap.h \
    Trie.h \
    home.h \
    wNode.h

FORMS += \
    home.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
