//
// Created by ZDxia on 2023/9/27.
//

#ifndef OPCHELPER_OPCUAHELPER_H
#define OPCHELPER_OPCUAHELPER_H

#ifdef _WIN32
#ifdef EXPORTS_UA_LIB
#define UA_API __declspec(dllexport)
#else
#define UA_API __declspec(dllimport)
#endif
#else
#define UA_API
#endif


#include <memory>
#include <functional>

#include "open62541.h"


namespace opc::ua {

    class UA_API OPCUAHelper {

    private:
        UA_Client *m_client{};


        bool init();

    public:

        OPCUAHelper();
    };

} // opc
// ua

#endif //OPCHELPER_OPCUAHELPER_H
