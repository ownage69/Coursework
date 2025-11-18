QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

INCLUDEPATH += $$PWD/includes

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/car.cpp \
    src/client.cpp \
    src/sale.cpp \
    src/dealership_manager.cpp \
    src/safeinput.cpp \
    src/addcardialog.cpp \
    src/addclientdialog.cpp \
    src/makesaledialog.cpp \
    src/searchdialog.cpp \
    src/reservationdialog.cpp \
    src/editcardialog.cpp \
    src/price_delegate.cpp \
    src/carcardwidget.cpp

HEADERS += \
    includes/mainwindow.h \
    includes/car.h \
    includes/client.h \
    includes/sale.h \
    includes/dealership_manager.h \
    includes/safeinput.h \
    includes/addcardialog.h \
    includes/addclientdialog.h \
    includes/makesaledialog.h \
    includes/searchdialog.h \
    includes/reservationdialog.h \
    includes/editcardialog.h \
    includes/price_delegate.h \
    includes/carcardwidget.h

FORMS +=

RESOURCES += resources.qrc