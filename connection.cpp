#include <QDebug>
#include <QSettings>
#include <QSqlError>
#include <QSqlDatabase>

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
    return m_connectError.isEmpty();
}

const QString& Connection::error() const
{
    return m_connectError;
}

void Connection::setHost(const QString& _host)
{
    m_host = _host;
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
    db.setDatabaseName(m_database);// CREATE DATABASE
    db.setUserName(m_user);
    db.setPassword(m_password);

    m_connectError.clear();
    if (db.open() == false)
        m_connectError = db.lastError().databaseText();
    else
        emit open();

    emit stateChanged(db.open());
}

void Connection::downloadSettings()
{
    QSettings s(QSettings::IniFormat, QSettings::UserScope, "Auto Server Manager");
    s.beginGroup("Database");
    m_host     = s.value("Host").toString();
    m_database = s.value("Database").toString();
    m_user     = s.value("User").toString();
    m_password = s.value("Password").toString();
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
    s.endGroup();
}



}
