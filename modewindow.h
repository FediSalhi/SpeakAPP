#ifndef MODEWINDOW_H
#define MODEWINDOW_H

#include <QWidget>
#include <mutex>
#include <condition_variable>
#include "clientwindow.h"
#include "serverwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ModeWindow; }
QT_END_NAMESPACE

/* this class is used to set the mode of the program
 * the program has 3 main modes:
 *      - server mode
 *      - client mode
 *      - info mode
 * get the program mode from user using buttons then
 * switch to the specific mode window
 * this is the firt window that appears
 */

enum SpeakAPPMode {
    kModeNotDefined,
    kModeServer,
    kModeUser,
    KModeAbout
};

class ModeWindow : public QWidget
{

    Q_OBJECT

public:
    ModeWindow(QWidget *parent = nullptr);
    ~ModeWindow();
    void Mode(SpeakAPPMode mode) {  this->_mode = mode;  } // set the App mode
    SpeakAPPMode Mode() { return this->_mode; } // get the App mode
    void startMode();


private slots:
    //void on_pushButton_2_clicked();

    void on_userMode_pushButton_clicked();

    void on_serverMode_pushButton_clicked();

    void on_aboutMode_pushButton_clicked();

private:
    Ui::ModeWindow *ui;
    SpeakAPPMode _mode{SpeakAPPMode::kModeNotDefined};
    ClientWindow* _clientWindow;
    ServerWindow* _serverWindow;

};
#endif // MODEWINDOW_H
