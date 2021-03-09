#include "crow_all.h"
#include <string>

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/hello")([](){
        return "skyu MIT";
    });

    // 通过某个id访问
    // http://localhost:8888/demo/1
    CROW_ROUTE(app, "/demo/<int>")
    .methods("POST"_method)
    ([](int id){
        crow::json::wvalue js;
        js["msg"] = id * 2;
        return js;
    });

    CROW_ROUTE(app, "/demo1/<int>")
    .methods("POST"_method)
    ([](const crow::request& req, int id){
        auto x = crow::json::load(req.body);
        int num = x["num"].i();
        crow::json::wvalue js;
        js["msg"] = id + num;
        return js;
    });

    // 第二种方式， http://localhost:8888/demo2?age=20
    CROW_ROUTE(app, "/demo2")
    .methods("GET"_method)
    ([](const crow::request& req){
        std::cout << req.url_params << std::endl;
        return crow::response{"demo2 yes"};
    });

    app.port(9001).multithreaded().run();
}
