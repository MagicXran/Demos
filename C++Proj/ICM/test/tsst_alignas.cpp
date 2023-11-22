//
// Created by zdxia on 2023/9/16.
//

#include <iostream>

using namespace std;


struct ts {
    int a;
    char b;
    int c;
};

#pragma pack(1)

struct ts_ali {
    int a;
    char b;
    int c;
};

#pragma  pack()


int main(int argc, char *argv[]) {

    char buffer[1024];
//    auto new_place = new(buffer) ts_ali{1,'c'};
    thread_local auto new_place = new(buffer) ts_ali();

    new_place->a *= 122;
//     auto new_place = new ts_ali();
    cout << new_place->a << endl;
    cout << new_place->b << endl;
    cout << new_place->c << endl;

    return 0;
}
