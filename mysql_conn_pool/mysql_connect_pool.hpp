#ifndef _MYSQL_CONNECTION_POOL_H_
#define _MYSQL_CONNECTION_POOL_H_

#include <iostream>
#include <string>
#include <list>
#include <mutex>

#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/exception.h>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/statement.h>

#include <singleton.hpp>

class MySQLConnPool : public Singleton<MySQLConnPool>{
public:
	/* Initial connection pool to connect given MySQL database. */
	void init_pool(
		const std::string& str_host_ip, const std::string& str_user_name, 
		const std::string& str_passwd,  std::size_t n_max_size);

	/* Innitial connection object for the pool */
	void init_connections(std::size_t n_size);

	/* Create single connection object. */
	sql::Connection* create_connection();

	/* Allocate avalible connection instance from pool. */
	sql::Connection* get_connection();

	/* Free connection instance to the pool after using. */
	void release_connection(sql::Connection* mysql_conn);

	~MySQLConnPool();

	MySQLConnPool();

	void destroy_connection(sql::Connection* mysql_conn);

	void destroy_pool();

	std::string str_host_ip;
	std::string str_user_name;
	std::string str_passwd;

	std::size_t n_max_size;
	std::size_t n_current_size;

	sql::Driver*                p_driver;          // MySQL driver object pointer
	std::list<sql::Connection*> lst_connection;    // MySQL connection pool container

	std::mutex mtx_lock;
};

#endif