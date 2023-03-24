#include "database.h"
//
//#include <utility>
//
//Database::Database(std::string database_filepath) : m_file_location(std::move(database_filepath)){
//    int32_t exit = sqlite3_open("example.db", &m_DB);
//    ASSERT(!exit, INFO("LOADED DATABASE \"%s\"", "example.db"), ERROR("FAILED TO LOAD DATABASE \"%s\"\n         ERROR LOG: %s", "example.db", sqlite3_errmsg(m_DB)))
//}
//
//Database::~Database() {
//    INFO("CLOSED DATABASE \"%s\"", m_file_location.c_str());
//}
//
//Database *Database::table(const std::string &name, const std::vector<TableColumn> &columns) {
//    std::string command = "CREATE TABLE IF NOT EXISTS " + name + "(";
//
//    for (int i = 0; i < columns.size()-1; i++)
//        command += columns[i].m_name + " " + columns[i].m_type + " " + columns[i].m_nullable + ", ";
//    command += columns.back().m_name + " " + columns.back().m_type + " " + columns.back().m_nullable + " );";
//
//    char* messaggeError;
//    int exit = sqlite3_exec(m_DB, command.c_str(), nullptr, nullptr, &messaggeError);
//
//    ASSERT(exit == SQLITE_OK, INFO("EXECUTED SQL\n         \"%s\"", command.c_str()), ERROR("FAILED TO EXECUTE SQL\n         \"%s\"", command.c_str()););
//
//    return this;
//}
//
//Database *Database::insert(const std::string &table_name, const std::string &value) {
//    char* messaggeError;
//
//    std::string command = "INSERT INTO " + table_name + " VALUES(" + value +");";
//
//    int exit = sqlite3_exec(m_DB, command.c_str(), nullptr, nullptr, &messaggeError);
//
//    ASSERT(exit == SQLITE_OK, INFO("EXECUTED SQL\n         \"%s\"", command.c_str()), ERROR("FAILED TO EXECUTE SQL\n         \"%s\"", command.c_str()););
//    return this;
//}