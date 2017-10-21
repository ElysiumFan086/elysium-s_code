#ifdef WIN32
#include "stdafx.h"
#endif

#include <db_interface/mysql_connect_pool.hpp>

/* Initial connection pool to connect given MySQL database. */
void MySQLConnPool::init_pool(
	const std::string& str_host_ip, const std::string& str_user_name, 
	const std::string& str_passwd,  std::size_t n_max_size)
{
	this->str_host_ip = str_host_ip;
	this->str_user_name = str_user_name;
	this->str_passwd = str_passwd;

	this->n_max_size = n_max_size;
	this->n_current_size = 0;
	try{
		this->p_driver = sql::mysql::get_driver_instance();
	}
	catch (sql::SQLException& ex){
		std::cout << "Get MySQL driver error: " << ex.getErrorCode() << std::endl;
		std::cout << "More message: " << std::endl << ex.getSQLState() << std::endl;
	}
	catch (std::runtime_error& ex_rt){
		std::cout << "Runtime error: " << ex_rt.what() << std::endl;
	}

	this->init_connections(n_max_size);
}

void MySQLConnPool::init_connections(std::size_t n_size)
{
	sql::Connection* p_conn = NULL;
	std::lock_guard<std::mutex> lock(this->mtx_lock);
	for (std::size_t i = 0; i < n_size; ++i){
		p_conn = this->create_connection();
		if (p_conn != NULL){
			this->lst_connection.push_back(p_conn);
			this->n_current_size++;
		}
	}
}

sql::Connection* MySQLConnPool::create_connection()
{
	sql::Connection* p_conn = NULL;
	try{
		sql::ConnectOptionsMap connection_properties;

		connection_properties["hostName"] = str_host_ip;
		connection_properties["userName"] = str_user_name;
		connection_properties["password"] = str_passwd;
		p_conn = this->p_driver->connect(connection_properties);
		//p_conn = this->p_driver->connect(this->str_host_ip, this->str_user_name, this->str_passwd);

		return p_conn;
	}
	catch (sql::SQLException& ex){
		std::cout << "Link MySQL database error: " << ex.getErrorCode() << std::endl;
		std::cout << "More message: " << std::endl << ex.getSQLState() << std::endl;
		return NULL;
	}
	catch (std::runtime_error& ex_rt){
		std::cout << "Runtime error: " << ex_rt.what() << std::endl;
		return NULL;
	}
}

/* Allocate avalible connection instance from pool. */
sql::Connection* MySQLConnPool::get_connection()
{
	sql::Connection* p_conn = NULL;
	std::lock_guard<std::mutex> lock(this->mtx_lock);
	if (this->lst_connection.size() > 0){
		p_conn = this->lst_connection.front();
		this->lst_connection.pop_front();
		if (p_conn->isClosed()){
			delete p_conn;
			p_conn = this->create_connection();
		}
		this->n_current_size--;
	}
	return p_conn;
}

/* Free connection instance to the pool after using. */
void MySQLConnPool::release_connection(sql::Connection* mysql_conn)
{
	if (mysql_conn != NULL){
		std::lock_guard<std::mutex> lock(this->mtx_lock);
		this->lst_connection.push_back(mysql_conn);
	}
}

MySQLConnPool::~MySQLConnPool()
{
	this->destroy_pool();
}

MySQLConnPool::MySQLConnPool() {}

void MySQLConnPool::destroy_connection(sql::Connection* mysql_conn)
{
	if (mysql_conn != NULL){
		try{
			mysql_conn->close();
		}
		catch (sql::SQLException& ex){
			std::cout << "Close MySQL connection error: " << ex.getErrorCode() << std::endl;
			std::cout << "More message: " << std::endl << ex.getSQLState() << std::endl;
		}
		catch (std::exception& std_ex){
			std::cout << "Catch excetion: " << std_ex.what() << std::endl;
		}
	}
}

void MySQLConnPool::destroy_pool()
{
	std::lock_guard<std::mutex> lock(this->mtx_lock);
	for (auto itr = lst_connection.begin(); itr != lst_connection.end(); ++itr){
		this->destroy_connection(*itr);
	}
	this->n_current_size = 0;
	this->lst_connection.clear();
}
