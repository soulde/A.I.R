//
// Created by lyjly on 2021/11/19.
//

#ifndef ACPS_DATABASE_H
#define ACPS_DATABASE_H

#include <utility>
#include <vector>
#include <string>


class Database {
protected:
    std::string url;

    Database() = default;

    Database(std::string database) {
        url = std::move(database);
    }

    virtual int open() = 0;

    virtual int close() = 0;

    virtual int addTable(std::string tableName, std::string primaryKey, std::vector<std::string> columnNames) = 0;

    virtual int removeTable(std::string tableName) = 0;

    virtual int insertRow(std::string tableName, void *data) = 0;

    virtual int deleteRow(std::string tableName, unsigned int rowIndex) = 0;

    virtual int deleteRow(std::string tableName, std::string primaryKey) = 0;

    virtual int modifyValue(std::string tableName, std::string primaryKey, std::string columnName) = 0;

    virtual std::string executeCmd(std::string cmd) = 0;
};


#endif //ACPS_DATABASE_H
