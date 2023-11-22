//
// Created by zdxia on 2023/7/17.
//

#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"

int main() {

    try {
        using json = nlohmann::json;

        std::ifstream jfile(R"(C:\Projects\ICM\JsonParser\test.json)");
        json j = json ::parse(jfile);
//        jfile >> j;

        // 打印output对象【也可以用j["output"].at("width")】

        double  aa = j["output"]["width"];
        std::cout << "ddd: " <<aa << std::endl;
//        std::cout << j.at("output").at("width") << std::endl;
//        std::cout << j.at("output").at("height") << std::endl;
//        std::cout << j.at("output").at("frameRate") << std::endl;
//        std::cout << j.at("output").at("crf") << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "error: 000" << e.what() << std::endl;
    }

    return 0;
}