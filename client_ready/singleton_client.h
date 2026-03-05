#ifndef SINGLETON_CLIENT_H
#define SINGLETON_CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QtNetwork>
#include <QByteArray>
#include <QDebug>

class SingletonClient;

class SingletonDestroyer 
{
    private:
        SingletonClient * p_instance;
    public:
        ~SingletonDestroyer() 
        {
            delete p_instance;
        }
        void initialize(SingletonClient * p) 
        {
            p_instance = p;
        }
};

class SingletonClient : public QObject 
{
    Q_OBJECT
    private:
        static SingletonClient * p_instance;
        static SingletonDestroyer destroyer;
        QTcpSocket * mTcpSocket;
    protected:
        SingletonClient() {}
        SingletonClient(const SingletonClient&) = delete;
        SingletonClient& operator = (SingletonClient &) = delete;
        ~SingletonClient() {}
        friend class SingletonDestroyer;
    public:
        static SingletonClient* getInstance() 
        {
            if (!p_instance) 
            {
                p_instance = new Singleton();
                destroyer.initialize(p_instance);
            }
            return p_instance;
        }

        void send_msg_to_server(QString query);

        /*
    signals:
        void message_from_server(QString msq);
    private slots:
        void slotServerRead();
        */
        // Запрос на подключение - в конструкторе
        // Отправка сообщения на сервер - функция 
        // 
};

// Выделение памяти под статичные переменные
Singleton::SingletonClient * p_instance;
Singleton::SingletonDestroyer destroyer;
