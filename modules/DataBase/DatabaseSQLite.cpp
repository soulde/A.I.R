//
// Created by lyjly on 2021/11/19.
//

#include "DatabaseSQLite.h"

#include <utility>


int DatabaseSQLite::open() {
    if (impl == nullptr) {
        return sqlite3_open(url.c_str(), &impl);
    } else {
        return -1;
    }
}

int DatabaseSQLite::close() {
    int ret = sqlite3_close(impl);
    impl = nullptr;
    return ret;
}

int DatabaseSQLite::addTable(std::string tableName, std::string primaryKey, std::vector<std::string> columnNames) {
    return 0;
}

int DatabaseSQLite::removeTable(std::string tableName) {
    return 0;
}

int DatabaseSQLite::insertRow(std::string tableName, void *data) {
    return 0;
}

int DatabaseSQLite::deleteRow(std::string tableName, unsigned int rowIndex) {
    return 0;
}

int DatabaseSQLite::deleteRow(std::string tableName, std::string primaryKey) {
    return 0;
}

int DatabaseSQLite::modifyValue(std::string tableName, std::string primaryKey, std::string columnName) {
    return 0;
}

std::string DatabaseSQLite::executeCmd(std::string cmd) {
    int rc = open();
    char* err;
    if (rc != SQLITE_OK) {
       std::string errMsg(sqlite3_errmsg(impl));
        return errMsg;
    } else {
        rc = sqlite3_exec(impl, cmd.c_str(), nullptr, nullptr, &err);
    }
    if(rc != SQLITE_OK){
        std::string errMsg(err);
        sqlite3_free(err);
        return errMsg;
    }

    close();

    return "";
}

bool Query::read() {
    return SQLITE_ROW == sqlite3_step(pStmt);

}

int Query::resetBind() {
    return sqlite3_reset(pStmt);
}


std::string Query::prepareCmd(const std::string &cmd, DatabaseSQLite &db) {
    int rc = db.open();
    const char* err;
    if (rc != SQLITE_OK) {
        std::string errMsg(sqlite3_errmsg(db.impl));
        return errMsg;
    }
    if (pStmt != nullptr) {
        rc = sqlite3_finalize(pStmt);
        if (rc != SQLITE_OK) {
            return "";
        }

    }
    rc = sqlite3_prepare_v2(db.impl, cmd.c_str(), -1, &pStmt, &err);
    if (rc != SQLITE_OK) {
        std::string errMsg(err);
        return errMsg;
    }
    db.close();
    return "";
}

Query::~Query() {
    sqlite3_finalize(pStmt);
}

void Query::finish() {
    sqlite3_finalize(pStmt);

}


std::string Table::getData(int row, int col) {
    assert(row < rows);
    assert(col < cols);
    return std::string(pTable[row * cols + col]);
}

int Table::getTable(const std::string &cmd, DatabaseSQLite &db) {
    int rc = db.open();
    if (rc != SQLITE_OK) {
        LOG << "err:" << sqlite3_errmsg(db.impl) << std::endl;
        return rc;
    }
    char* err;
    rc = sqlite3_get_table(db.impl, cmd.c_str(), &pTable,&rows,&cols, &err);
    if (rc != SQLITE_OK) {
        return rc;
    }
    db.close();
    return rc;
}

void Table::getSrc(char **&pT, int &nCols, int &nRows) {
    pT = pTable;
    nCols = cols;
    nRows = rows;
}

Table::~Table() {
    sqlite3_free_table(pTable);
}
