/**
 * @file clientwindow.h
 * @brief ClientWindow class header file
 *
 * This class is responsible for the creation
 * of the client window. It owns a ClientCommunication
 * object that is resposbile for TCP client connection.
 *
 * @author Fedi Salhi
 * @date December 22 2022
 *
 */

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
    ClientWindow(const ClientWindow& src) = delete; // No copying
    ClientWindow& operator=(const ClientWindow& src) = delete; // No copying
    ClientWindow(ClientWindow&& src) = delete; // No moving
    ClientWindow& operator=(ClientWindow&& src) = delete; // No moving
    void showMessageChatArea(const QString& msg); // prints messages to the GUI

private slots:
    void on_Conenct_pushButton_clicked();
    void enableConnection();
    void on_Send_pushButton_clicked();
    void on_Exit_pushButton_clicked();

private:
    Ui::ClientWindow *ui;
    std::unique_ptr<ClientCommunication> _client;
};

#endif // CLIENTWINDOW_H
