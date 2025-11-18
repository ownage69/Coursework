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
    src/carcardwidget.cpp \
    src/car_repository.cpp \
    src/car_reservation.cpp \
    src/client_repository.cpp \
    src/inventory_service.cpp \
    src/sale_repository.cpp \
    src/sale_service.cpp \
    src/car_options.cpp \
    src/accessmodedialog.cpp \
    src/adminlogindialog.cpp \
    src/reviewdialog.cpp \
    src/salesreportdialog.cpp \
    src/car_validator.cpp \
    src/car_serializer.cpp

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
    includes/carcardwidget.h \
    includes/car_repository.h \
    includes/car_reservation.h \
    includes/client_repository.h \
    includes/inventory_service.h \
    includes/sale_repository.h \
    includes/sale_service.h \
    includes/car_options.h \
    includes/accessmodedialog.h \
    includes/adminlogindialog.h \
    includes/reviewdialog.h \
    includes/salesreportdialog.h \
    includes/car_validator.h \
    includes/car_serializer.h

FORMS +=

RESOURCES += resources.qrc