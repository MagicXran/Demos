#include <iostream>
#include "ocilib.hpp"
using namespace std;
using namespace ocilib;

int main() {

    try {
        ocilib::Environment::Initialize(ocilib::Environment::Default);
        ocilib::Environment::EnableWarnings(true);

        // 链接数据库
        ocilib::Connection conn("datacentre", "scc", "scc");
        ocilib::Statement stmt(conn);

        //查询所有曲线记录, 可以自己按照时间筛选
        stmt.Execute("SELECT sysdate ss from dual");

        auto rs = stmt.GetResultset();

        while (rs.Next()) {
            cout << "fm blob size:" << rs.Get<ocilib::Date>("ss").ToString() << endl;

        }
    } catch (const std::exception &e) {
        cerr << "err: " << e.what() << endl;
    }
    ocilib::Environment::Cleanup();
    return 0;
}
