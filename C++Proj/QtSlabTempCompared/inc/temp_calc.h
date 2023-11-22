//
// Created by ZDxia on 2023/11/9.
//

#ifndef QTSLABTEMPCOMPARED_TEMP_CALC_H
#define QTSLABTEMPCOMPARED_TEMP_CALC_H

#include "rapidcsv.h"


#define     CEQ_CLASS_NUM    15    //钢种分类数
constexpr char CEQClassTbl[CEQ_CLASS_NUM][7] =
        /*----------------------------------------------------------------*/
        /* 0  |   1   |   2   |   3   |   4   |   5   |   6   |   7   |	  */
        /*低碳|  中高碳 | 硅钢| 低合金| 高合金|自定义1|自定义2|自定义3|	  */
        /*----------------------------------------------------------------*/
        {"L1", "L2", "L3", "L4", "L5", "L6", "L7", "D1",

                /*----------------------------------------------------------------*/
                /* 8  |   9   |  10   |  11   |  12   |  13   |  14   |  15   |	  */
                /*----------------------------------------------------------------*/
         "D2", "D3", "D4", "D5", "D6", "D7", "D8"};


int GetMatCode(const char *MatClass);


class temp_calc {

public:


};

#endif //QTSLABTEMPCOMPARED_TEMP_CALC_H
