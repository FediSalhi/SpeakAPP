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
    ~ServerWindow();
    void showNumberClients();

private slots:
    void on_Connect_pushButton_clicked();

private:
    Ui::ServerWindow *ui;
    std::unique_ptr<ServerCommunication> _server;
    std::vector<std::thread> _threads;

};

#endif // SERVERWINDOW_H
