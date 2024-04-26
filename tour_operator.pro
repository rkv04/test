QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addcitywindow.cpp \
    addemployeewindow.cpp \
    addhotelwindow.cpp \
    addticketwindow.cpp \
    adminmainwindow.cpp \
    app.cpp \
    apperror.cpp \
    authorizationwindow.cpp \
    city.cpp \
    citylistwindow.cpp \
    citymodel.cpp \
    cityservice.cpp \
    clientmainwindow.cpp \
    clientmodel.cpp \
    clientslistwindow.cpp \
    context.cpp \
    criticaldb.cpp \
    db.cpp \
    editcitywindow.cpp \
    edithotelwindow.cpp \
    editticketwindow.cpp \
    employeedeletewindow.cpp \
    employeemainwindow.cpp \
    hotelslistwindow.cpp \
    main.cpp \
    account.cpp \
    myticketswindow.cpp \
    registrationwindow.cpp \
    ticketpurchasewindow.cpp \
    ticketslistwindow.cpp \
    user.cpp \
    userservice.cpp \
    userslistwindow.cpp

HEADERS += \
    account.h \
    addcitywindow.h \
    addemployeewindow.h \
    addhotelwindow.h \
    addticketwindow.h \
    adminmainwindow.h \
    app.h \
    apperror.h \
    authorizationwindow.h \
    city.h \
    citylistwindow.h \
    citymodel.h \
    cityservice.h \
    clientmainwindow.h \
    clientmodel.h \
    clientslistwindow.h \
    context.h \
    criticaldb.h \
    db.h \
    editcitywindow.h \
    edithotelwindow.h \
    editticketwindow.h \
    employeedeletewindow.h \
    employeemainwindow.h \
    hotelslistwindow.h \
    myticketswindow.h \
    registrationwindow.h \
    ticketpurchasewindow.h \
    ticketslistwindow.h \
    user.h \
    userservice.h \
    userslistwindow.h

FORMS += \
    account.ui \
    addcitywindow.ui \
    addemployeewindow.ui \
    addhotelwindow.ui \
    addticketwindow.ui \
    adminmainwindow.ui \
    authorizationwindow.ui \
    citylistwindow.ui \
    clientmainwindow.ui \
    clientslistwindow.ui \
    editcitywindow.ui \
    edithotelwindow.ui \
    editticketwindow.ui \
    employeedeletewindow.ui \
    employeemainwindow.ui \
    hotelslistwindow.ui \
    myticketswindow.ui \
    registrationwindow.ui \
    ticketpurchasewindow.ui \
    ticketslistwindow.ui \
    userslistwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
