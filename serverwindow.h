/**
 * @file serverwindow.h
 * @brief ServerWindow class header file
 *
 * This class is responsible for the creation
 * of the server window. It owns a ServerCommunication
 * object that is resposbile for TCP server connection.
 *
 * @author Fedi Salhi
 * @date December 22 2022
 */

#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QWidget>
#include <memory>
#include "servercommunication.h"

namespace Ui {
class ServerWindow;
}

class ServerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWindow(QWidget *parent = nullptr);
    virtual ~ServerWindow();
    ServerWindow(const ServerWindow& src) = delete; // No copying policy
    ServerWindow& operator=(const ServerWindow& src) = delete; // No copying policy
    ServerWindow(ServerWindow&& src) = delete; // No moving policy
    ServerWindow& operator=(ServerWindow&& src) = delete; // No moving policy
    void showNumberClients(); // update the number of clients every 500 ms

private slots:
    void on_Connect_pushButton_clicked();
    void on_Quit_pushButton_clicked();

private:
    Ui::ServerWindow *ui;
    std::unique_ptr<ServerCommunication> _server;
    std::vector<std::thread> _threads;
};

#endif // SERVERWINDOW_H
