#pragma once
//#include "logger.h"
//#include <string>
//#include "sqlite3.h"
//#include <vector>
//
//struct TableColumn{
//    std::string m_name;
//    std::string m_type;
//    std::string m_nullable{"NOT NULL"};
//};
//
//
//enum class eCommand{
//    eInsert,
//    eDelete,
//    eUpdate
//};
//
//struct Command{
//    eCommand m_type;
//};
//
//struct Database{
//    explicit Database(std::string database_filepath);
//    ~Database();
//
//    Database* table(const std::string &name, const std::vector<TableColumn> &columns);
//    Database* insert(const std::string &table_name, const std::string &value);
//
//    const std::string m_file_location;
//    sqlite3* m_DB{};
//};