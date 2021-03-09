#include "crow_all.h"

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/hello")([](){
        return "skyu MIT";
    });

    CROW_ROUTE(app, "/demo2")
    .methods("GET"_method)
    ([](const crow::request& req){
        auto x = crow::json::load(req.body);
        // if (!x)
        //     return crow::response(400);
        // int sum = x["a"].i()+x["b"].i();
        // std::ostringstream os;
        // os << sum;
        std::cout << "body " << x["age"] << std::endl;
        // return crow::response{os.str()};
        return crow::response{"yes"};
        
    });

    app.port(8888).multithreaded().run();
}
