#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QWidget>
#include "clientcommunication.h"
#include <memory>

namespace Ui {
class ClientWindow;
}

class ClientWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow();
    void showMessageChatArea(const QString& msg);

private slots:
    void on_Conenct_pushButton_clicked();
    void connectedToServer();
    void disconnectedFromServer();
    void enableConnection();

    void on_Send_pushButton_clicked();

private:
    Ui::ClientWindow *ui;
    std::unique_ptr<ClientCommunication> _client;
};

#endif // CLIENTWINDOW_H
