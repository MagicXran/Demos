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
        stmt.Execute("select sysdate ss from dual");
        auto res = stmt.GetResultset();
        res.Next();

        cout << res.Get<ocilib::Date>("ss"). << endl;


    } catch (std::exception &e) {

        cout << e.what() << endl;
    }

    ocilib::Environment::Cleanup();

    return 0;
}