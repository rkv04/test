QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

INCLUDEPATH += \
    ./app \
    ./entities \
    ./windows \
    ./models \
    ./services \
    ./gui \

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    app/log.cpp \
    models/citylistmodel.cpp \
    models/citytablemodel.cpp \
    models/clienttablemodel.cpp \
    models/hoteltablemodel.cpp \
    services/hotelservice.cpp \
    windows/addcitywindow.cpp \
    windows/addemployeewindow.cpp \
    windows/addhotelwindow.cpp \
    windows/addticketwindow.cpp \
    windows/adminmainwindow.cpp \
    app/app.cpp \
    app/apperror.cpp \
    windows/authorizationwindow.cpp \
    entities/city.cpp \
    windows/citylistwindow.cpp \
    services/cityservice.cpp \
    windows/clientmainwindow.cpp \
    windows/clientslistwindow.cpp \
    app/context.cpp \
    app/criticaldb.cpp \
    app/db.cpp \
    windows/editcitywindow.cpp \
    windows/edithotelwindow.cpp \
    windows/editticketwindow.cpp \
    windows/employeedeletewindow.cpp \
    windows/employeemainwindow.cpp \
    entities/hotel.cpp \
    windows/hotelslistwindow.cpp \
    app/main.cpp \
    windows/account.cpp \
    windows/myticketswindow.cpp \
    windows/registrationwindow.cpp \
    windows/ticketpurchasewindow.cpp \
    windows/ticketslistwindow.cpp \
    entities/user.cpp \
    services/userservice.cpp \
    windows/userslistwindow.cpp

HEADERS += \
    app/log.h \
    models/citylistmodel.h \
    models/citytablemodel.h \
    models/clienttablemodel.h \
    models/hoteltablemodel.h \
    services/hotelservice.h \
    windows/account.h \
    windows/addcitywindow.h \
    windows/addemployeewindow.h \
    windows/addhotelwindow.h \
    windows/addticketwindow.h \
    windows/adminmainwindow.h \
    app/app.h \
    app/apperror.h \
    windows/authorizationwindow.h \
    entities/city.h \
    windows/citylistwindow.h \
    services/cityservice.h \
    windows/clientmainwindow.h \
    windows/clientslistwindow.h \
    app/context.h \
    app/criticaldb.h \
    app/db.h \
    windows/editcitywindow.h \
    windows/edithotelwindow.h \
    windows/editticketwindow.h \
    windows/employeedeletewindow.h \
    windows/employeemainwindow.h \
    entities/hotel.h \
    windows/hotelslistwindow.h \
    windows/myticketswindow.h \
    windows/registrationwindow.h \
    windows/ticketpurchasewindow.h \
    windows/ticketslistwindow.h \
    entities/user.h \
    services/userservice.h \
    windows/userslistwindow.h

FORMS += \
    gui/account.ui \
    gui/addcitywindow.ui \
    gui/addemployeewindow.ui \
    gui/addhotelwindow.ui \
    gui/addticketwindow.ui \
    gui/adminmainwindow.ui \
    gui/authorizationwindow.ui \
    gui/citylistwindow.ui \
    gui/clientmainwindow.ui \
    gui/clientslistwindow.ui \
    gui/editcitywindow.ui \
    gui/edithotelwindow.ui \
    gui/editticketwindow.ui \
    gui/employeedeletewindow.ui \
    gui/employeemainwindow.ui \
    gui/hotelslistwindow.ui \
    gui/myticketswindow.ui \
    gui/registrationwindow.ui \
    gui/ticketpurchasewindow.ui \
    gui/ticketslistwindow.ui \
    gui/userslistwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
