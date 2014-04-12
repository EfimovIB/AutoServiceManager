#ifndef ASM_CONNECTION_H
#define ASM_CONNECTION_H

#include <QString>
#include <QObject>

namespace asmt
{
class Connection : public QObject
{
    Q_OBJECT
public:

    Connection();

    const QString& host() const;
    unsigned int port() const;
    const QString& database() const;
    const QString& user() const;
    const QString& password() const;

    bool opened() const;

public slots:

    void setHost(const QString& _host);
    void setPort(unsigned int _port);
    void setDatabase(const QString& _database);
    void setUser(const QString& _user);
    void setPassword(const QString& _password);

    void connect();

signals:

    void open();
    void stateChanged(bool _opened);

private:

    void downloadSettings();
    void uploadSettings();

private:

    QString m_host;
    QString m_database;
    QString m_user;
    QString m_password;
    unsigned int m_port;
};
}

#endif //ASM_CONNECTION_H
