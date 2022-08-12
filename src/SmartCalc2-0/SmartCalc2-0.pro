QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../SmartCalc2-0/main.cpp \
    ../SmartCalc2-0/view.cpp \
    ../SmartCalc2-0/s21_model.cpp \
    ../SmartCalc2-0/s21_controller.cpp \
    ../SmartCalc2-0/s21_creditModel.cpp \
    ../SmartCalc2-0/s21_depositModel.cpp \
    ../SmartCalc2-0/s21_polishModel.cpp \
    ../SmartCalc2-0/s21_tableModel.cpp


HEADERS += \
    ../SmartCalc2-0/view.h \
    ../SmartCalc2-0/s21_controller.h \
    ../SmartCalc2-0/s21_model.h \
    ../SmartCalc2-0/s21_creditModel.h \
    ../SmartCalc2-0/s21_depositModel.h \
    ../SmartCalc2-0/s21_polishModel.h \
    ../SmartCalc2-0/s21_tableModel.h

FORMS += \
    ../SmartCalc2-0/view.ui



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../SmartCalc2-0/resource.qrc

ICON = ../SmartCalc2-0/smartcalc.icns
