#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <iostream>

typedef websocketpp::client<websocketpp::config::asio_client> client;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

void on_open(client *c, websocketpp::connection_hdl hdl)
{
    std::string msg = "hello";
    c->send(hdl, msg, websocketpp::frame::opcode::text);
    c->get_alog().write(websocketpp::log::alevel::app, "Tx: " + msg);
}

void on_message(client *c, websocketpp::connection_hdl hdl, message_ptr msg)
{
    std::cout << "on_message called with hdl: " << hdl.lock().get()
              << " and message: " << msg->get_payload()
              << std::endl;
    websocketpp::lib::error_code ec;
    //c->send(hdl,msg->get_payload(),msg->get_opcode(),ec);
    if(ec)
    {
        std::cout << "Echo failed because " << ec.message() << std::endl;
    }
}

//定时器回调函数
void Timeout(client *c, websocketpp::connection_hdl &hdl, boost::asio::deadline_timer *pt, const boost::system::error_code &ec)
{
    if(ec)
    {
        std::cout << "timer is cancel " << std::endl;
        return;
    }
    static int count = 0;
    c->send(hdl, "hello", websocketpp::frame::opcode::text);
    count++;
    if(count > 5)//定时器触发五次后关闭连接
    {
        c->close(hdl, websocketpp::close::status::normal, "");
        return;
    }
    pt->expires_at(pt->expires_at() + boost::posix_time::seconds(5));
    pt->async_wait(bind(Timeout, c, hdl, pt, ::_1));

}

int main(int argc, char *argv[])
{
    client c;

    std::string uri = "ws://xx.xx.xx.xx:xxx";

    c.set_access_channels(websocketpp::log::alevel::all);
    c.clear_access_channels(websocketpp::log::alevel::frame_payload);
    c.clear_access_channels(websocketpp::log::alevel::frame_header);

    // 初始化 ASIO
    c.init_asio();

    // 注册消息回调

    c.set_message_handler(bind(&on_message, &c, ::_1, ::_2));
    c.set_open_handler(bind(&on_open, &c, _1));

    websocketpp::lib::error_code ec;
    client::connection_ptr con = c.get_connection(uri, ec);
    con->add_subprotocol("janus-protocol");
    if(ec)
    {
        std::cout << "could not create connection because: " << ec.message() << std::endl;
        return 0;
    }

    auto hdl = con->get_handle();
    c.connect(con);
    
    boost::asio::deadline_timer t(c.get_io_service(), boost::posix_time::seconds(5)); //设置一个5s超时的定时器
    t.async_wait(bind(&Timeout, &c, hdl, &t, ::_1));

    std::thread th([&c] { c.run(); });
   
    //休眠13s后取消定时器并关闭连接
    sleep(13);
    t.cancel();
    c.close(hdl, websocketpp::close::status::normal, "");
    
    th.join();
}
