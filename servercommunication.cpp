/**
 * @file servercommunication.cpp
 * @brief ServerCommunication class source file
 *
 * This class is responsible for sending/receiving
 * messages from/to clients. It owns the
 * tcp server object and the clients sockets.
 *
 * @author Fedi Salhi
 * @date December 22 2022
 *
 */

#include "servercommunication.h"

ServerCommunication::ServerCommunication(const QHostAddress& address, quint16 port)
{
    this->_server = new QTcpServer();

    if(!(this->_server->listen(address, port))) {
        this->_listenStatus = ServerStatus::kServerListenFailure;
    } else {
        this->_listenStatus = ServerStatus::kServerListenSuccess;
    }

    connect(this->_server, SIGNAL(newConnection()), this, SLOT(newConnectionEstablished()));
    this->messageSize = 0;
}

void ServerCommunication::newConnectionEstablished() {
    sendToAll("New client connected!");
    QTcpSocket* newClient = this->_server->nextPendingConnection();
    this->_clients.append(newClient);
    connect(newClient, SIGNAL(readyRead()), this, SLOT(newDataReceived()));
    connect(newClient, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
}

void ServerCommunication::newDataReceived() {
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) {
        // sender not known, just return
        return;
    }
    QDataStream in(socket);
    if (this->messageSize == 0) {
        // if we still don't know the size of the message, try to capture it
        if (socket->bytesAvailable() < (int)sizeof(quint16)) {
            // we still didn't get the size, just return
            return;
        }
        in >> this->messageSize;

        // we captured the size of the message, let's capture the message now
        if (socket->bytesAvailable() < messageSize) {
        // we didn't yet received all tcp sub-packages, just return
            return;
         }
         // the message is entirely received
         QString message;
         in >> message;
         sendToAll(message);
         this->messageSize = 0; // reset the message size for the new message
    }
}

void ServerCommunication::clientDisconnected() {
    sendToAll("A client just disconnected");
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) {
        return;
    } else {
        this->_clients.removeOne(socket);
        socket->deleteLater(); // don't use delet client, deleting the source of the signal may cause a problem later
    }
}

void ServerCommunication::sendToAll(const QString& message) {

    QByteArray package;
    QDataStream out(&package, QIODevice::WriteOnly);
    out << (quint16)0;
    out << message;
    out.device()->seek(0);
    out << (quint16)(package.size()-sizeof(quint16));
    for(auto* item : _clients) {
        item->write(package);
    }
}

ServerCommunication::~ServerCommunication() {
    delete this->_server;
    for(auto* item : this->_clients) {
        delete item;
    }
}

ServerStatus ServerCommunication::ServerListenStatus() {
    return this->_listenStatus;
}

quint8 ServerCommunication::getNumberClients() {
    return _clients.size();
}




