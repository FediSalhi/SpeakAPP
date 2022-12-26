/**
 * @file modewindow.h
 * @brief ModeWindow class header file
 *
 * This class is responsible for the creation
 * of the mode window. It owns a client window
 * and a server window. It creates client/server
 * window depending on the user choice.
 *
 * @author Fedi Salhi
 * @date December 22 2022
 *
 */

#ifndef MODEWINDOW_H
#define MODEWINDOW_H

#include <QWidget>
#include <memory>
#include "clientwindow.h"
#include "serverwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ModeWindow; }
QT_END_NAMESPACE

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
    ModeWindow(const ModeWindow& src) = delete; // No copying policy
    ModeWindow& operator=(const ModeWindow& src) = delete; // No copying policy
    ModeWindow(ModeWindow&& src) = delete; // No moving policy
    ModeWindow& operator=(ModeWindow&& src) = delete; // No moving policy

    void Mode(SpeakAPPMode mode) {  this->_mode = mode;  } // set the App mode
    SpeakAPPMode Mode() { return this->_mode; } // get the App mode
    void startMode(); // starts client/server modes

private slots:
    void on_userMode_pushButton_clicked();
    void on_serverMode_pushButton_clicked();
    void on_aboutMode_pushButton_clicked();

private:
    Ui::ModeWindow *ui;
    SpeakAPPMode _mode{SpeakAPPMode::kModeNotDefined};
    std::unique_ptr<ClientWindow> _clientWindow;
    std::unique_ptr<ServerWindow> _serverWindow;

};
#endif // MODEWINDOW_H
