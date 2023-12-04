#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QLibrary>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);


    QLibrary *hello_lib = NULL;
    //写清楚库的路径，如果放在当前工程的目录下，路径为./Oracle.so
    hello_lib = new QLibrary("X:/app/Renaissance/product/11.2.0/client_1/oci.dll");

    //加载动态库
    hello_lib->load();
    if (!hello_lib->isLoaded()) {
        printf("load Oracle failed!/n");
        return -1;
    }

    // 创建数据库对象
    QSqlDatabase db = QSqlDatabase::addDatabase("QOCI");

    qDebug() << QSqlDatabase::drivers();


    // 设置数据库连接信息
    db.setHostName("192.168.5.5"); // 主机名
    db.setDatabaseName("datacentre"); // 数据库名称
    db.setUserName("scc"); // 用户名
    db.setPassword("scc"); // 密码
    // 打开数据库连接
    if (!db.open()) {
        qWarning() << "Failed to connect to database." << db.lastError().text();
        return -1;
    }
    // 创建查询对象
    QSqlQuery query(db);
    // 执行SQL语句，查询v$session视图
    if (!query.exec("select SID, SERIAL#, USERNAME, STATUS, CPU_TIME from v$session")) {
        qWarning() << "Failed to execute query." << query.lastError().text();
        return -1;
    }
    // 循环读取查询结果
    while (query.next()) {
        // 获取每一行的数据
        int sid = query.value(0).toInt(); // SID
        int serial = query.value(1).toInt(); // SERIAL#
        QString username = query.value(2).toString(); // USERNAME
        QString status = query.value(3).toString(); // STATUS
        int cpu_time = query.value(4).toInt(); // CPU_TIME
        // 打印输出
        qDebug() << "SID:" << sid << "SERIAL#:" << serial << "USERNAME:" << username << "STATUS:" << status
                 << "CPU_TIME:" << cpu_time;
    }
    // 关闭数据库连接
    db.close();
    return a.exec();
//    return 0;
}
