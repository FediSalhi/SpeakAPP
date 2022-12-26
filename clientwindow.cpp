/**
 * @file clientwindow.cpp
 * @brief ClientWindow class source file
 *
 * This class is responsible for the creation
 * of the client window. It owns a ClientCommunication
 * object that is resposbile for TCP client connection.
 *
 * @author Fedi Salhi
 * @date December 22 2022
 *
 */

#include "clientwindow.h"
#include "ui_clientwindow.h"

ClientWindow::ClientWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWindow)
{
    ui->setupUi(this);

    // set Port range and default value
    ui->ServerPort_spinBox->setRange(1024,65536);
    ui->ServerPort_spinBox->setValue(50888);

    // create the communication class
    this->_client = std::make_unique<ClientCommunication>();

    // set the listvew model
    ui->ChatArea_listView->setModel(this->_client->shownMessagesModel());
    ui->ChatArea_listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // setup signals/slots connections
    connect(this->_client.get(), SIGNAL(sigConnectedToServer()), this, SLOT(enableConnection()));
    connect(this->_client.get(), SIGNAL(sigDisconnected()), this, SLOT(enableConnection()));

    setAttribute(Qt::WA_DeleteOnClose, true);

   // exit only usign button
   setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
}

ClientWindow::~ClientWindow()
{
    delete ui;
}


void ClientWindow::showMessageChatArea(const QString& msg) {
    this->_client->appendShownMessages(msg);
    this->_client->shownMessagesModel()->setStringList(this->_client->getShownMessages());
}

void ClientWindow::on_Conenct_pushButton_clicked()
{
    showMessageChatArea("Trying to connect...");
    ui->Conenct_pushButton->setEnabled(false);
    this->_client->getSocket()->abort();
    this->_client->getSocket()->connectToHost(ui->ServerIP_lineEdit->text(), ui->ServerPort_spinBox->value());
}

void ClientWindow::enableConnection() {
    ui->Conenct_pushButton->setEnabled(true);
}

void ClientWindow::on_Send_pushButton_clicked()
{
    this->_client->sendMessageToServer(ui->Pseudo_lineEdit->text() + " : " + ui->Message_lineEdit->text());
}

void ClientWindow::on_Exit_pushButton_clicked()
{
    qApp->quit();
}
