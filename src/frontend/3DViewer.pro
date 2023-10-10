QT       += core gui openglwidgets opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../backend/matrix/add_func.c \
    ../backend/matrix/output.c \
    ../backend/matrix/s21_calc_complements.c \
    ../backend/matrix/s21_create_matrix.c \
    ../backend/matrix/s21_determinant.c \
    ../backend/matrix/s21_eq_matrix.c \
    ../backend/matrix/s21_inverse_matrix.c \
    ../backend/matrix/s21_mult_matrix.c \
    ../backend/matrix/s21_mult_number.c \
    ../backend/matrix/s21_remove_matrix.c \
    ../backend/matrix/s21_sub_matrix.c \
    ../backend/matrix/s21_sum_matrix.c \
    ../backend/matrix/s21_transpose.c \
    ../backend/parcer.c \
    glwidget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../backend/matrix/add_func.h \
    ../backend/matrix/s21_matrix.h \
    ../backend/parcer.h \
    glwidget.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include(QtGifImage/src/gifimage/qtgifimage.pri)
