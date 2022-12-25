#include "clientcommunication.h"

ClientCommunication::ClientCommunication()
{
    this->_socket = new QTcpSocket;
    connect(_socket, SIGNAL(readyRead()), this, SLOT(dataReceived()));
    connect(_socket, SIGNAL(connected()), this, SLOT(connectedToServer()));
    connect(_socket, SIGNAL(disconnected()), this, SLOT(disconnectedFromServer()));
    connect(_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));

    // associate the model with the string list
    this->_shownMessagesModel = new QStringListModel(this->_shownMessages);

    this->messageSize = 0;
}

void ClientCommunication::sendMessageToServer(const QString& message) {
    QByteArray package;
    QDataStream out(&package, QIODevice::WriteOnly);
    out << (quint16)0;
    out << message;
    out.device()->seek(0);
    out << (quint16) (package.size()-sizeof(quint16));
    this->_socket->write(package);
}

void ClientCommunication::connectedToServer() {
    showMessageChatArea("Connected to server successfully !");
    emit(sigConnectedToServer());
}

void ClientCommunication::disconnectedFromServer() {
    showMessageChatArea("Disconnected from server");
    emit(sigDisconnected());
}

void ClientCommunication::dataReceived() {
    QDataStream in(this->_socket);
    if(this->_socket->bytesAvailable() < (int)sizeof(quint16)) {
        // still didn't get the size completely, just return
        return;
    } else {
        in >> this->messageSize;
    }
    if (this->_socket->bytesAvailable() < this->messageSize) {
        // still didn't get the message completely, return
        return;
    } else {
        QString receivedMessage;
        in >> receivedMessage;
        // TODO: show the message to the GUI
        showMessageChatArea(receivedMessage);
        this->messageSize = 0;
    }
}

void ClientCommunication::socketError(QAbstractSocket::SocketError error) {
    switch(error) {
    case QAbstractSocket::HostNotFoundError:
        // TODO print to the GUI: server couldn't be found, verify IP and port
        showMessageChatArea("ERROR: Server not found, verify server IP and Port");
        emit(sigDisconnected());
        break;
    case QAbstractSocket::ConnectionRefusedError:
        showMessageChatArea("ERROR: Connection refuse from server. Make sure sure that the server program is working! Verify IP and Port as well.");
        emit(sigDisconnected());
        break;
    case QAbstractSocket::RemoteHostClosedError:
        showMessageChatArea("ERROR: Connection stopped from the server!");
        emit(sigDisconnected());
        break;
    default:
        showMessageChatArea("ERROR " + _socket->errorString());
        emit(sigDisconnected());
        break;
    }
}

void ClientCommunication::appendShownMessages(const QString& item) {
    this->_shownMessages.append(item);
}

QStringListModel* ClientCommunication::shownMessagesModel() {
    return this->_shownMessagesModel;
}

QStringList ClientCommunication::getShownMessages() {
    return this->_shownMessages;
}

void ClientCommunication::showMessageChatArea(const QString& msg) {
    appendShownMessages(msg);
    shownMessagesModel()->setStringList(getShownMessages());
}

QTcpSocket* ClientCommunication::getSocket() {
    return _socket;
}

