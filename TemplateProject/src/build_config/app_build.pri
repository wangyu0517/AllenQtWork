CONFIG(debug, debug|release) {#debug与release生成在不同的目录
    DESTDIR = $$PWD/../bin_debug#pwd 是pri所在目录

    OBJECTS_DIR = $$_PRO_FILE_PWD_/build/build_debug#_PRO_FILE_PWD_是调用该pri文件的pro所在的路径
    MOC_DIR = $$_PRO_FILE_PWD_/build/build_debug
    RCC_DIR = $$_PRO_FILE_PWD_/build/build_debug
    UI_DIR = $$_PRO_FILE_PWD_/build/build_debug

    DEFINES += ODEBUG
#    DEFINES += QT_NO_GESTURES
}
CONFIG(release, debug|release) {
    DESTDIR = $$PWD/../bin_release

    OBJECTS_DIR = $$_PRO_FILE_PWD_/build/build_release
    MOC_DIR = $$_PRO_FILE_PWD_/build/build_release
    RCC_DIR = $$_PRO_FILE_PWD_/build/build_release
    UI_DIR = $$_PRO_FILE_PWD_/build/build_release
}

LIBS += -L$$DESTDIR