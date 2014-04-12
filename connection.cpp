#include <QDebug>
#include <QSettings>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "connection.h"

namespace asmt
{

Connection::Connection()
{
    downloadSettings();
}

const QString& Connection::host() const
{
    return m_host;
}

unsigned int Connection::port() const
{
    return m_port;
}

const QString& Connection::database() const
{
    return m_database;
}

const QString& Connection::user() const
{
    return m_user;
}

const QString& Connection::password() const
{
    return m_password;
}

bool Connection::opened() const
{
    QSqlDatabase db;
    return db.isOpen();
}

void Connection::setHost(const QString& _host)
{
    m_host = _host;
    uploadSettings();
    connect();
}

void Connection::setPort(unsigned int _port)
{
    m_port = _port;
    uploadSettings();
    connect();
}

void Connection::setDatabase(const QString& _database)
{
    m_database = _database;
    uploadSettings();
    connect();
}

void Connection::setUser(const QString& _user)
{
    m_user = _user;
    uploadSettings();
    connect();
}

void Connection::setPassword(const QString& _password)
{
    m_password = _password;
    uploadSettings();
    connect();
}

void Connection::connect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(m_host);
    db.setUserName(m_user);
    db.setPassword(m_password);
    db.setPort(m_port);

    if (db.open())
    {
        QSqlQuery query("create database if not exists " + m_database, db);

        if (query.lastError().text().isEmpty())
        {
            db.setDatabaseName(m_database);

            if (db.open())
            {
                emit open();
            }
        }
    }
    else
    {
        qDebug() << "Database error: " << db.lastError().databaseText();

    }

    emit stateChanged(db.isOpen());
}

void Connection::downloadSettings()
{
    QSettings s(QSettings::IniFormat, QSettings::UserScope, "Auto Server Manager");
    s.beginGroup("Database");
    m_host     = s.value("Host").toString();
    m_database = s.value("Database").toString();
    m_user     = s.value("User").toString();
    m_password = s.value("Password").toString();
    m_port     = s.value("Port", "5432").toUInt();
    s.endGroup();
}

void Connection::uploadSettings()
{
    QSettings s(QSettings::IniFormat, QSettings::UserScope, "Auto Server Manager");
    s.beginGroup("Database");
    s.setValue("Host", m_host);
    s.setValue("Database", m_database);
    s.setValue("User", m_user);
    s.setValue("Password", m_password);
    s.setValue("Port", m_port);
    s.endGroup();
}



}
