#ifndef _DB_INTERFACE_H
#define _DB_INTERFACE_H

#include <string>
namespace DB
{
	class ConnectionPool
	{
	public:
		ConnectionPool() = default;
		virtual ~ConnectionPool() = default;

	public:
		virtual void shutDown() = 0;

		virtual int  execute(const std::string& sql) = 0;
		virtual void executeQuery(const std::string& sql, void* callback) = 0;
		virtual void beginTransaction() = 0;
		virtual void commitTransaction() = 0;
		virtual void rollbackTransaction() = 0;
	private:

	};

}
#endif
