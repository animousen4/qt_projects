QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += static

QT += multimedia multimediawidgets
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
OTHER_FILES +=

RESOURCES += resources.qrc

SOURCES += main.cpp mainwindow.cpp circularlayout.cpp participantwidget.cpp participantinfo.cpp gameinfo.cpp menudialog.cpp settingmanager.cpp settingsdialog.cpp addparticipantdialog.cpp addcountingdialog.cpp winnerdialog.cpp \
    addfiledialog.cpp

HEADERS += mainwindow.h circularlayout.h participantwidget.h participantinfo.h gameinfo.h menudialog.h settingmanager.h settingsdialog.h addparticipantdialog.h addcountingdialog.h CountingManager.h winnerdialog.h \
    addfiledialog.h \
    imagehelper.h \
    preset.h

FORMS += mainwindow.ui menudialog.ui settingsdialog.ui addparticipantdialog.ui addcountingdialog.ui winnerdialog.ui \
    addfiledialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
