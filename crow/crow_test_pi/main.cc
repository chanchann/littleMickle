#include "crow_all.h"
#include <string>

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")
    .methods("GET"_method)
    ([](const crow::request& req){
        std::cout << req.url_params << std::endl;
        std::string cmd = req.url_params.get("cmd");
        std::cout << cmd << std::endl;
        // if(req.url_params.get("cmd") == "S") {
        //     std::cout << "stop" << std::endl;
        // }
        return crow::response{"yes"};
    });

    app.port(9001).multithreaded().run();
}
