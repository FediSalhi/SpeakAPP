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
    delete _clientWindow;
    delete _serverWindow;
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
        this->_serverWindow = new ServerWindow();
        this->_serverWindow->show();
        this->close();
    }
    if (_mode == SpeakAPPMode::kModeUser) {
        // start client
        this->_clientWindow = new ClientWindow();
        this->_clientWindow->show();
        this->close();
    }
    if (_mode == SpeakAPPMode::KModeAbout) {
        //this->_aboutWindow = new About();
        //this->_aboutWindow->show();
        //this->close();
        QMessageBox::information(this, "About Me", "Hi, I'm <strong>Fedi Salhi</strong>\n \
                                 This is a chat application built for Udacity C++ Nano Degre.\n \
                                 Reach out on <strong>fedisalhi.com</strong>");
    }
}
