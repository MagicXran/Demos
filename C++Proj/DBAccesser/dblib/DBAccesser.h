//
// Created by Renaissance on 12/2/2023.
//

#ifndef DBACCESSER_DBACCESSER_H
#define DBACCESSER_DBACCESSER_H

#include "ocilib/include/ocilib.hpp"


class EnvironmentSingleton {
public:
    static EnvironmentSingleton &getInstance() {
        static EnvironmentSingleton instance;
        return instance;
    }

    EnvironmentSingleton(const EnvironmentSingleton &) = delete;

    EnvironmentSingleton &operator=(const EnvironmentSingleton &) = delete;

private:
    EnvironmentSingleton() {
        ocilib::Environment::Initialize(ocilib::Environment::Threaded);
        ocilib::Environment::EnableWarnings(true);
    }

    ~EnvironmentSingleton() {
        ocilib::Environment::Cleanup();
    }
};


class DBAccesser {

public:
    enum class DBAccesserFlagsValues {
        /** Default mode */
        Default = 0, /** Enable support for multi-threading */
        Threaded = 1, /** Enable support for events related to subscriptions, HA and AQ notifications */
        Events = 4
    };

    DBAccesser();

};


#endif //DBACCESSER_DBACCESSER_H
