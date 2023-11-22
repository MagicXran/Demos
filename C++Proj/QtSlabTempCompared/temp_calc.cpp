//
// Created by ZDxia on 2023/11/9.
//

#include <iostream>
#include <cstring>


#include "temp_calc.h"


//若该函数返回 -1，则不进行后续计算。
int GetMatCode(const char *MatClass) {
    try {

        for (int i = 0; i < CEQ_CLASS_NUM; i++) {
            if (!strcmp(MatClass, CEQClassTbl[i])) return i;
        }
        return -1;
    } catch (const std::exception &e) {

        std::cerr << "GetMatCode.获取钢种分档失败,错误=" << e.what() << std::endl;
        return -1;
    }
}


