#include "modewindow.h"
#include "serverwindow.h"
#include "clientwindow.h"

#include <QApplication>
#include <thread>
#include <mutex>
#include <condition_variable>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ModeWindow* w = new ModeWindow();
    w->show();
    a.exec();

    /*std::unique_lock<std::mutex> modeLock(w->modeMutex);
    w->modeCV.wait(modeLock);

    if (w->Mode() == SpeakAPPMode::kModeServer) {
        ServerWindow* sr = new ServerWindow();
        sr->show();
    } else if (w->Mode() == SpeakAPPMode::kModeUser) {
        ClientWindow* cl = new ClientWindow();
        cl->show();
    }*/

    return a.exec();
}
