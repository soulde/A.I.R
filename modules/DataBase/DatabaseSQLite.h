//
// Created by lyjly on 2021/11/19.
//

#ifndef ACPS_DATABASESQLITE_H
#define ACPS_DATABASESQLITE_H

#include <utility>

#include "Database.h"
#include "sqlite3/sqlite3.h"
#include "Tools.hpp"
#include <cassert>


class DatabaseSQLite : public Database {
public:
    friend class Query;

    friend class Table;

    DatabaseSQLite() = default;

    explicit DatabaseSQLite(std::string url) : Database(std::move(url)) {};

    int addTable(std::string tableName, std::string primaryKey, std::vector<std::string> columnNames) override;

    int removeTable(std::string tableName) override;

    int insertRow(std::string tableName, void *data) override;

    int deleteRow(std::string tableName, unsigned int rowIndex) override;

    int deleteRow(std::string tableName, std::string primaryKey) override;

    int modifyValue(std::string tableName, std::string primaryKey, std::string columnName) override;

    std::string executeCmd(std::string cmd) override;

private:
    int inline open() override;

    int inline close() override;


    sqlite3 *impl{};

};

class Query {
public:
    Query() = default;

    ~Query();

    std::string prepareCmd(const std::string &cmd, DatabaseSQLite &db);

    bool read();

    int resetBind();

    void finish();

    template<typename T>
    void bind(T value, int index) {
        if constexpr (std::is_same<T, int>()) {
            sqlite3_bind_int(pStmt, index, value);
        }
        if constexpr (std::is_same<T, std::string>()) {
            sqlite3_bind_text(pStmt, index, value.c_str(), value.size(), nullptr);
        }
        if constexpr (std::is_same<T, double>()) {
            sqlite3_bind_double(pStmt, index, value);
        }
    }

    template<typename T>
    T getData(int index) {
        if constexpr (std::is_same<T, std::string>()) {
            try {
                return std::string((char *) sqlite3_column_text(pStmt, index));
            } catch (const std::logic_error &e) {
                return std::string("");
            }
        }
        if constexpr (std::is_same<T, int>()) {
            return sqlite3_column_int(pStmt, index);
        }
        if constexpr (std::is_same<T, double>()) {
            return sqlite3_column_double(pStmt, index);
        }
    }


private:
    sqlite3_stmt *pStmt{};

};

class Table {
public:
    Table() = default;

    ~Table();

    int getTable(const std::string &cmd, DatabaseSQLite &db);

    std::string getData(int row, int col);

    void getSrc(char **&pT, int &nCols, int &nRows);

private:
    char **pTable;

    int cols;

    int rows;
};


#endif //ACPS_DATABASESQLITE_H
