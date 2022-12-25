#include "clientwindow.h"
#include "ui_clientwindow.h"

ClientWindow::ClientWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWindow)
{
    ui->setupUi(this);
    ui->ServerPort_spinBox->setRange(1024,65536);
    ui->ServerPort_spinBox->setValue(5000);
    this->_client = std::make_unique<ClientCommunication>();
    ui->ChatArea_listView->setModel(this->_client->shownMessagesModel());
    ui->ChatArea_listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(this->_client.get(), SIGNAL(sigConnectedToServer()), this, SLOT(enableConnection()));
    connect(this->_client.get(), SIGNAL(sigDisconnected()), this, SLOT(enableConnection()));

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
void ClientWindow::connectedToServer() {

}

void ClientWindow::disconnectedFromServer() {

}

void ClientWindow::enableConnection() {
    ui->Conenct_pushButton->setEnabled(true);
    // TODO: change this slot to enable button
}


void ClientWindow::on_Send_pushButton_clicked()
{
    this->_client->sendMessageToServer(ui->Pseudo_lineEdit->text() + " : " + ui->Message_lineEdit->text());
}
