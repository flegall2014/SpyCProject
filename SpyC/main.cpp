// Qt
#include <QApplication>

// Application
#include "spyc.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Build SpyC instance
    SpyC *pSpyC = SpyC::instance();

    // Startup
    pSpyC->startup();

    // Event loop
    int res = app.exec();

    // Shutdown
    pSpyC->shutdown();

    // Release
    delete pSpyC;

    return res;
}
