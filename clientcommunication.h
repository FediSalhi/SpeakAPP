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
    void sendMessageToServer(const QString& message);
    void appendShownMessages(const QString& item);
    QStringListModel* shownMessagesModel();
    QStringList getShownMessages();
    QTcpSocket* getSocket();
    void showMessageChatArea(const QString& msg);
private slots:
    void connectedToServer();
    void disconnectedFromServer();
    void dataReceived();
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
