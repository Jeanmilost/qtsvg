HEADERS       = mainwindow.h \
                svgview.h
RESOURCES     = svgviewer.qrc
SOURCES       = main.cpp \
                mainwindow.cpp \
                svgview.cpp
QT           += widgets svg xml

contains(QT_CONFIG, opengl): QT += opengl

CONFIG += console

# install
target.path = $$[QT_INSTALL_EXAMPLES]/svg/svgviewer
INSTALLS += target

wince*: {
     addFiles.files = files\\*.svg
     addFiles.path = "\\My Documents"
     DEPLOYMENT += addFiles
}