#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <functional>

typedef websocketpp::server<websocketpp::config::asio> server;

class utility_server {
public:
    utility_server() {
         // 设置log
        m_endpoint.set_error_channels(websocketpp::log::elevel::all);
        m_endpoint.set_access_channels(websocketpp::log::alevel::all ^ websocketpp::log::alevel::frame_payload);

        // 初始化Asio
        m_endpoint.init_asio();

        // 设置消息回调为echo_handler
        m_endpoint.set_message_handler(std::bind(
            &utility_server::echo_handler, this,
            std::placeholders::_1, std::placeholders::_2
        ));
    }

    void echo_handler(websocketpp::connection_hdl hdl, server::message_ptr msg) {
        // 发送消息
        m_endpoint.send(hdl, msg->get_payload(), msg->get_opcode());
    }

    void run() {
        // 监听端口 9002
        m_endpoint.listen(9002);

       
        m_endpoint.start_accept();

        // 开始Asio事件循环
        m_endpoint.run();
    }
private:
    server m_endpoint;
};

int main() {
    utility_server s;
    s.run();
    return 0;
}
