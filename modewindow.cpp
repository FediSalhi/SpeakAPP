/**
 * @file modewindow.cpp
 * @brief ModeWindow class source file
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

#include "modewindow.h"
#include "ui_modewindow.h"

ModeWindow::ModeWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ModeWindow)
{
    ui->setupUi(this);
}

ModeWindow::~ModeWindow()
{
    delete ui;
}

void ModeWindow::on_userMode_pushButton_clicked()
{
    this->_mode = SpeakAPPMode::kModeUser;
    startMode();
}

void ModeWindow::on_serverMode_pushButton_clicked()
{
    this->_mode = SpeakAPPMode::kModeServer;
    startMode();
}

void ModeWindow::on_aboutMode_pushButton_clicked()
{
    this->_mode = SpeakAPPMode::KModeAbout;
    startMode();
}

void ModeWindow::startMode() {
    if (_mode == SpeakAPPMode::kModeServer) {
        // start server
        this->_serverWindow = std::make_unique<ServerWindow>();
        this->_serverWindow->show();
        this->close();
    }
    if (_mode == SpeakAPPMode::kModeUser) {
        // start client
        this->_clientWindow = std::make_unique<ClientWindow>();
        this->_clientWindow->show();
        this->close();
    }
    if (_mode == SpeakAPPMode::KModeAbout) {
        QMessageBox::information(this, "About Me", "Hi, I'm <strong>Fedi Salhi</strong>\n \
                                 This is a chat application built for Udacity C++ Nano Degre.\n \
                                 Reach out on <strong>fedisalhi.com</strong>");
    }
}
