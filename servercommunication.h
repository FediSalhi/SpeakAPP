/**
 * @file servercommunication.h
 * @brief ServerCommunication class header file
 *
 * This class is responsible for sending/receiving
 * messages from/to clients. It owns the
 * tcp server object and the clients sockets.
 *
 * @author Fedi Salhi
 * @date December 22 2022
 *
 */

#ifndef SERVERCOMMUNICATION_H
#define SERVERCOMMUNICATION_H


#include <QList>
#include <iostream>
#include <QtWidgets>
#include <QtNetwork>
#include <thread>
#include <vector>
#include <chrono>

enum ServerStatus {
    kServerListenFailure,
    kServerListenSuccess,
};

class ServerCommunication : public QWidget
{
    Q_OBJECT
public:
    ServerCommunication(const QHostAddress& address, quint16 port);
    virtual ~ServerCommunication();
    ServerCommunication(const ServerCommunication& src) = delete; // no copy constructor
    ServerCommunication& operator=(const ServerCommunication& src) = delete; // no copy assignment
    ServerCommunication(ServerCommunication&& src) = delete; // no move constructor
    ServerCommunication& operator=(ServerCommunication&& src) = delete; // no move assignment
    void sendToAll(const QString& message); // send message to all clients
    ServerStatus ServerListenStatus();
    quint8 getNumberClients();

public slots:
    void newConnectionEstablished(); // called when a new connection happens
    void newDataReceived(); // called for each received tco sub-package
    void clientDisconnected(); // called when a client disconnect

private:
    QTcpServer* _server;
    QList<QTcpSocket*> _clients;
    quint16 messageSize;
    ServerStatus _listenStatus;

};

#endif // SERVERCOMMUNICATION_H
