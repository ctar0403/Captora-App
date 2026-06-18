# Captora

A screen-capture OCR utility for Windows (a port/fork of Capture2Text), built with
Qt 5, Tesseract, Leptonica and OpenCV. Press a hotkey, select a region of the
screen, and the recognized text is copied to the clipboard.

## Project layout

```
Captora/
├─ src/         C++ sources and headers (*.cpp, *.h, *.mm)
├─ ui/          Qt Designer forms (*.ui)
├─ resources/   resource.qrc, images (img/), stylesheet (style/), app icon (*.rc, *.ico)
├─ vendor/      Third-party dependencies (QHotkey) — not committed
├─ dist/        Self-contained runnable app (exe + DLLs + Qt plugins + tessdata) — generated
├─ Captora.pro  qmake project file
└─ README.md
```

## Dependencies

Built with the MSYS2 MinGW-w64 toolchain. Install the required packages:

```sh
pacman -S mingw-w64-x86_64-qt5 \
          mingw-w64-x86_64-tesseract-ocr \
          mingw-w64-x86_64-tesseract-data-eng \
          mingw-w64-x86_64-leptonica \
          mingw-w64-x86_64-opencv
```

Fetch the vendored QHotkey dependency:

```sh
git clone https://github.com/Skycoder42/QHotkey.git vendor/QHotkey
```

## Build

From the MSYS2 MinGW64 shell (or with `C:/msys64/mingw64/bin` on PATH):

```sh
qmake-qt5 -o Makefile Captora.pro
mingw32-make -f Makefile.Release
```

The compiled executable is written to `release/Captora.exe`. To build the
command-line variant, add `CONFIG+=console` to the qmake invocation.

## Run

`release/Captora.exe` needs its runtime DLLs, the Qt platform plugins, and
Tesseract language data (`tessdata/`) alongside it. The ready-to-run, fully
self-contained build lives in `dist/` — run `dist/Captora.exe` directly, or copy
the whole `dist/` folder to another machine.

To OCR additional languages, drop the corresponding `*.traineddata` files into
`dist/tessdata/` (e.g. `jpn.traineddata`, `chi_sim.traineddata`).

## Usage

- Press the OCR hotkey to arm capture (the cursor becomes a crosshair).
- Click once to set the first corner; the selection rectangle follows the mouse.
- Click again — or press-drag and release — to finish and run OCR.
- Press `Esc` to cancel.
