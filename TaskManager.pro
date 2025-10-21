QT += core gui widgets
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/CentralDatabaseClass.cpp \
        src/main.cpp \
        src/IMySQLService.cpp \
        src/MySQLConnector.cpp \
        src/TaskManagerService.cpp \
        src/User.cpp \
        src/UserService.cpp

HEADERS += \
    src/headers/CentralDatabaseClass.h \
    src/headers/IMySQLService.h \
    src/headers/MySQLConnector.h \
    src/headers/TaskManagerService.h \
    src/headers/User.h \
    src/headers/UserService.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$quote(C:/Program Files/MySQL/MySQL Connector C++ 9.4/include)
DEPENDPATH += $$quote(C:/Program Files/MySQL/MySQL Connector C++ 9.4/include)
win32:CONFIG(release, debug|release): LIBS += -L$$quote(C:/Program Files/MySQL/MySQL Connector C++ 9.4/lib64/vs14/) -lmysqlcppconn
else:win32:CONFIG(debug, debug|release): LIBS += -L'C:/Program Files/MySQL/MySQL Connector C++ 9.4/lib64/Debug/vs14/' -lmysqlcppconn
else:unix: LIBS += -L'C:/Program Files/MySQL/MySQL Connector C++ 9.4/lib64/' -lmysqlcppconn

INCLUDEPATH += $$PWD/../../../libs/libsodium/src/libsodium/include/
DEPENDPATH += $$PWD/../../../libs/libsodium/src/libsodium/include/
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../libs/libsodium/bin/x64/Release/v141/dynamic/ -llibsodium
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../libs/libsodium/bin/x64/Debug/v141/dynamic/ -llibsodium
else:unix: LIBS += -L$$PWD/../../../libs/libsodium/bin/x64/Release/v141/ -llibsodium
