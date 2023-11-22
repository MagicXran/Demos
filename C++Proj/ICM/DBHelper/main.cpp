//
// Created by zdxia on 2023/7/21.
//

#include <iostream>
#include "ocilib.hpp"

using namespace std;

int main() {

    try {

        ocilib::Environment::Initialize(ocilib::Environment::Threaded);
        ocilib::Connection conn("nercar", "scc", "scc");
        ocilib::Statement stmt(conn);
        stmt.Execute("select ID, coil_id from tb_pdi where COIL_ID = 'D500009300'");
        auto res = stmt.GetResultset();
        res.Next();

        cout << res.Get<int>("ID") << endl;
        cout << res.Get<std::string>("coil_id") << endl;


    } catch (std::exception &e) {

        cout << e.what() << endl;
    }

    ocilib::Environment::Cleanup();

    return 0;
}