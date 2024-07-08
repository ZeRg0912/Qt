#include "database.h"

DataBase::DataBase(QObject *parent)
    : QObject{parent}
{
    dataBase = new QSqlDatabase();
    simpleQuery = new QSqlQuery();
}

DataBase::~DataBase()
{
    delete dataBase;
}

/*!
 * \brief Метод добавляет БД к экземпляру класса QSqlDataBase
 * \param driver драйвер БД
 * \param nameDB имя БД (Если отсутствует Qt задает имя по умолчанию)
 */
void DataBase::AddDataBase(QString driver, QString nameDB)
{
    *dataBase = QSqlDatabase::addDatabase(driver, nameDB);
}

/*!
 * \brief Метод подключается к БД
 * \param для удобства передаем контейнер с данными необходимыми для подключения
 * \return возвращает тип ошибки
 */
void DataBase::ConnectToDataBase(QVector<QString> data)
{
    dataBase->setHostName(data[hostName]);
    dataBase->setDatabaseName(data[dbName]);
    dataBase->setUserName(data[login]);
    dataBase->setPassword(data[pass]);
    dataBase->setPort(data[port].toInt());

    ///Тут должен быть код ДЗ

    bool status;
    status = dataBase->open( );
    if (status) {
        tableModel = new QSqlTableModel(this, *dataBase);
        queryModel = new QSqlQueryModel(this);
    }
    emit sig_SendStatusConnection(status);
}

/*!
 * \brief Метод производит отключение от БД
 * \param Имя БД
 */
void DataBase::DisconnectFromDataBase(QString nameDb)
{
    *dataBase = QSqlDatabase::database(nameDb);
    dataBase->close();
}

/*!
 * \brief Метод формирует запрос к БД.
 * \param request - SQL запрос
 */
void DataBase::RequestToDB(const requestType& type, QTableView* tv_result)
{
    QSqlError err;
    *simpleQuery = QSqlQuery(*dataBase);

    QString request = "SELECT title, description FROM film f "
                      "JOIN film_category fc on f.film_id = fc.film_id "
                      "JOIN category c on c.category_id = fc.category_id ";
    ///Тут должен быть код ДЗ
    if (type == requestAllFilms) {

        tableModel->setTable("film");
        tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
        tableModel->setHeaderData(1, Qt::Horizontal, tr("Название"));
        tableModel->setHeaderData(2, Qt::Horizontal, tr("Описание"));
        tableModel->select();
        tv_result->setModel(tableModel);

        for (int column = 0; column < tableModel->columnCount(); column++) {
            if (column != 1 && column != 2) {
                tv_result->setColumnHidden(column, true);
            }
        }

    } else {

        if (type == requestComedy) {
            request = request + " WHERE c.name = 'Comedy'";
        } else if (type == requestHorrors) {
            request = request + " WHERE c.name = 'Horror'";
        }

        queryModel->setQuery(request, *dataBase);
        queryModel->setHeaderData(0, Qt::Horizontal, tr("Название"));
        queryModel->setHeaderData(1, Qt::Horizontal, tr("Описание"));
        tv_result->setModel(queryModel);

        for (int col = 0; col < queryModel->columnCount(); ++col) {
            if (col != 0 && col != 1) {
                tv_result->setColumnHidden(col, true);
            }
        }
    }
    if(simpleQuery->exec(request) == false){
        err = simpleQuery->lastError();
        emit sig_SendStatusRequest(err);
    }
    tv_result->resizeColumnsToContents();
}

/*!
 * @brief Метод возвращает последнюю ошибку БД
 */
QSqlError DataBase::GetLastError()
{
    return dataBase->lastError();
}
