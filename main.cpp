/**
 * @file main.cpp
 * @brief main source file
 *
 * Start the application and show
 * the Mode window.
 *
 * @author Fedi Salhi
 * @date December 22 2022
 *
 */

#include "modewindow.h"
#include "serverwindow.h"
#include "clientwindow.h"

#include <QApplication>
#include <thread>
#include <memory>

int main(int argc, char *argv[])
{
    QApplication SpeakAPP(argc, argv);
    std::shared_ptr<ModeWindow> modeWindow = std::make_shared<ModeWindow>();
    modeWindow->show();
    return SpeakAPP.exec();
}
