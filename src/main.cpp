#include "CommandLine.h"

//#include <SingleApplication>
#ifndef CLI_BUILD
    #include <QApplication>
    #include <QStyleFactory>
    #include <QFile>
//    #include <RunGuard.h>
    #include "MainWindow.h"
#else
    #include <QCoreApplication>
#endif

int main(int argc, char *argv[])
{
    /* From http://www.qtcentre.org/threads/60203-QApplication-QGuiApplication-and-QCoreApplication:
       "QCoreApplication is the base class, QGuiApplication extends the base class with functionality
       related to handling windows and GUI stuff (non-widget related, e.g. OpenGL or QtQuick),
       QApplication extends QGuiApplication with functionality related to handling widgets." */
#ifndef CLI_BUILD
    QApplication app(argc, argv);
    bool portable = false;
#else
    QCoreApplication  app(argc, argv);
#endif
    QCoreApplication::setOrganizationName("Captora");
    QCoreApplication::setOrganizationDomain("Captora.com");
    QCoreApplication::setApplicationName("Captora");
    QCoreApplication::setApplicationVersion("4.6.2");

#ifndef CLI_BUILD
    if(argc > 1)
#endif
    {
        CommandLine cmdLine;
        bool success = cmdLine.process(app);
#ifndef CLI_BUILD
        if(success && cmdLine.getPortable())
        {
            portable = true;
        }
        else
        {
            return (int)(!success);
        }
#else
        return (int)(!success);
#endif
    }

#ifndef CLI_BUILD
    // Force single instance
//    RunGuard guard("Captora-42e81c93-4f7c-4d68-9688-0b7f75a427cc");
//    if(!guard.tryToRun())
//    {
//        return 0;
//    }

    // Apply the modern light theme (Fusion base + global stylesheet)
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QFile styleFile(":/style/modern.qss");
    if(styleFile.open(QFile::ReadOnly | QFile::Text))
    {
        app.setStyleSheet(QString::fromUtf8(styleFile.readAll()));
        styleFile.close();
    }

    // Ensure that closing a message box does not exit the program
    app.setQuitOnLastWindowClosed(false);
    MainWindow w(portable); // The constructor will setup everything

    return app.exec();
#endif
}
