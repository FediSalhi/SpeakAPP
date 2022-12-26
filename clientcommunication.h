/**
 * @file clientcommunication.h
 * @brief ClientCommunication class header file
 *
 * This class is responsible for sending/receiving
 * messages from/to the server. It owns the
 * communication socket and the messages model
 *
 * @author Fedi Salhi
 * @date December 22 2022
 *
 */

#ifndef CLIENTCOMMUNICATION_H
#define CLIENTCOMMUNICATION_H

#include <QWidget>
#include <QtNetwork>
#include <iostream>
#include <QStringList>

class ClientCommunication : public QWidget
{
    Q_OBJECT

public:
    ClientCommunication();
    virtual ~ClientCommunication();
    ClientCommunication(const ClientCommunication& src) = delete; // No copying policy
    ClientCommunication& operator=(const ClientCommunication& src) = delete; // No copying policy
    ClientCommunication(ClientCommunication&& src) = delete; // No moving policy
    ClientCommunication& operator=(ClientCommunication&& src) = delete; // No moving policy
    void sendMessageToServer(const QString& message); // serialize a message and send it through the socket
    void appendShownMessages(const QString& item); // add a message to the list
    QStringListModel* shownMessagesModel(); // get model
    QStringList getShownMessages();
    QTcpSocket* getSocket();
    void showMessageChatArea(const QString& msg); // prints a message the chat zone in the GUI

private slots:
    void connectedToServer();
    void disconnectedFromServer();
    void dataReceived(); // This slot parses the received message and print it
    void socketError(QAbstractSocket::SocketError error);

signals:
    void sigConnectedToServer();
    void sigDisconnected();

private:
    QTcpSocket* _socket;
    quint16 messageSize;
    QStringList _shownMessages;
    QStringListModel* _shownMessagesModel;
};

#endif // CLIENTCOMMUNICATION_H
