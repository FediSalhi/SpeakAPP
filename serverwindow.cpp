/**
 * @file serverwindow.cpp
 * @brief ServerWindow class source file
 *
 * This class is responsible for the creation
 * of the server window. It owns a ServerCommunication
 * object that is resposbile for TCP server connection.
 *
 * @author Fedi Salhi
 * @date December 22 2022
 */

#include "serverwindow.h"
#include "ui_serverwindow.h"

ServerWindow::ServerWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWindow)
{
    ui->setupUi(this);
    ui->ServerPort_spinBox->setRange(1024,65536);

    //set 50888 as default port
    ui->ServerPort_spinBox->setValue(50888);

    // update the comboBox list with IP options
    QStringList Iplist=(QStringList()<<"Null"<<"Broadcast"<<"LocalHost"<<"LocalHostIPv6"<<"Any"<<"AnyIPv6"<<"AnyIPv4");
    ui->ServerIP_comboBox->addItems(Iplist);

    // set "Any" as default ip
    ui->ServerIP_comboBox->setCurrentIndex(4);

    ui->InfoZone_textEdit->setReadOnly(true);
    ui->ConnectedClients_lineEdit->setReadOnly(true);

    // exit only usign button
    setAttribute(Qt::WA_DeleteOnClose, true);
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
}


ServerWindow::~ServerWindow()
{
    delete ui;
}

void ServerWindow::on_Connect_pushButton_clicked()
{
    // get chosen ip
    QHostAddress ip;
    switch(ui->ServerIP_comboBox->currentIndex()) {
    case 0:
        ip = QHostAddress::Null;
        break;
    case 1:
        ip = QHostAddress::Broadcast;
        break;
    case 2:
        ip = QHostAddress::LocalHost;
        break;
    case 3:
        ip = QHostAddress::LocalHostIPv6;
        break;
    case 4:
        ip = QHostAddress::Any;
        break;
    case 5:
        ip = QHostAddress::AnyIPv6;
        break;
    case 6:
        ip = QHostAddress::AnyIPv6;
        break;
    default:
        break;
    }

    // connect using chosen IP and port
    this->_server = std::make_unique<ServerCommunication>(ip, ui->ServerPort_spinBox->value());

    // updating textEdit when server starts
    //connect(this->_server.get(), SIGNAL(connectedToServer()), this, SLOT(connectedToServer()));
    if (this->_server->ServerListenStatus() == ServerStatus::kServerListenSuccess) {
        ui->InfoZone_textEdit->setText("Server is listening...\nIP: "+ui->ServerIP_comboBox->currentText()+"\n"+"Port: " + QString::number(ui->ServerPort_spinBox->value()));
        ui->Connection_groupBox->setEnabled(false);

        // start thread to update number of clients
        this->_threads.emplace_back(std::thread(&ServerWindow::showNumberClients, this));
        this->_threads.at(0).detach();
    }
    if (this->_server->ServerListenStatus() == ServerStatus::kServerListenFailure) {
        ui->InfoZone_textEdit->setText("Error: Please verfiy IP and Port");
    }
}

void ServerWindow::showNumberClients() {
    while (true) {
        ui->ConnectedClients_lineEdit->setText(QString::number(this->_server->getNumberClients()) + " client(s) connected");
        std::this_thread::sleep_for(std::chrono::microseconds(500));
    }
}


void ServerWindow::on_Quit_pushButton_clicked()
{
    qApp->quit();
}
