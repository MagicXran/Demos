//
// Created by ZDxia on 2023/9/27.
//

#include "inc/OPCUAHelper.h"
#include <iostream>

namespace opc::ua {


    OPCUAHelper::OPCUAHelper() {
        init();
    }

    bool OPCUAHelper::init() {

        try {
            m_client = UA_Client_new();


            return true;
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
        return false;
    }
} // opc
// ua