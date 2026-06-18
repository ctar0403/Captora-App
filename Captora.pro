QT += core

!console {
    QT += gui network texttospeech
    greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
}

# QHotkey dependency (vendored).
# Fetch with: git clone https://github.com/Skycoder42/QHotkey.git vendor/QHotkey
include(vendor/QHotkey/qhotkey.pri)

TARGET = Captora

console {
    TARGET = Captora_CLI
}

TEMPLATE = app

# Emit warnings when deprecated Qt APIs are used.
DEFINES += QT_DEPRECATED_WARNINGS

console {
    DEFINES += CLI_BUILD
}

# ---------------------------------------------------------------------------
# Core sources (shared by the GUI and CLI builds)
# ---------------------------------------------------------------------------
SOURCES += \
    src/main.cpp \
    src/Furigana.cpp \
    src/BoundingTextRect.cpp \
    src/QHotkeyHook.cpp \
    src/CommandLine.cpp \
    src/UtilsLang.cpp \
    src/UtilsImg.cpp \
    src/PostProcess.cpp \
    src/PreProcess.cpp \
    src/OcrEngine.cpp \
    src/UtilsCommon.cpp

HEADERS += \
    src/Furigana.h \
    src/BoundingTextRect.h \
    src/CommandLine.h \
    src/QHotkeyHook.h \
    src/UtilsLang.h \
    src/UtilsImg.h \
    src/PostProcess.h \
    src/PreProcess.h \
    src/PreProcessCommon.h \
    src/OcrEngine.h \
    src/UtilsCommon.h

# ---------------------------------------------------------------------------
# GUI-only sources (excluded from the CLI build)
# ---------------------------------------------------------------------------
!console {
    macx {
        OBJECTIVE_SOURCES += src/MacMouseMonitor.mm
        OBJECTIVE_HEADERS += src/MacMouseMonitor.h
        LIBS += -framework AppKit
    }

    SOURCES += \
        src/MainWindow.cpp \
        src/SettingsDialog.cpp \
        src/Settings.cpp \
        src/PopupDialog.cpp \
        src/Preview.cpp \
        src/SampleBox.cpp \
        src/Translate.cpp \
        src/HotkeyWidget.cpp \
        src/CaptureBox.cpp \
        src/AboutDialog.cpp \
        src/WelcomeDialog.cpp \
        src/MouseHook.cpp \
        src/Speech.cpp

    HEADERS += \
        src/MainWindow.h \
        src/SettingsDialog.h \
        src/Preview.h \
        src/Settings.h \
        src/PopupDialog.h \
        src/SampleBox.h \
        src/Translate.h \
        src/HotkeyWidget.h \
        src/CaptureBox.h \
        src/AboutDialog.h \
        src/ReplyTimeout.h \
        src/WelcomeDialog.h \
        src/MouseHook.h \
        src/Speech.h

    FORMS += \
        ui/SettingsDialog.ui \
        ui/PopupDialog.ui \
        ui/AboutDialog.ui \
        ui/HotkeyWidget.ui \
        ui/WelcomeDialog.ui
}

# Headers live next to their sources in src/.
INCLUDEPATH += src

macx: {
    PKG_CONFIG = /usr/local/bin/pkg-config
}

# Tesseract / Leptonica / OpenCV (resolved via pkg-config).
CONFIG += link_pkgconfig
PKGCONFIG += tesseract opencv4 lept

!console {
    RESOURCES += resources/resource.qrc
}

# Application icon (Windows). RC_INCLUDEPATH lets windres find Captora.ico,
# which the .rc references by name.
RC_FILE = resources/Captora.rc
RC_INCLUDEPATH += $$PWD/resources
