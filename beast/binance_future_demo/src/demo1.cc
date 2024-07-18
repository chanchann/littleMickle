#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/strand.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace ssl = boost::asio::ssl;
using tcp = boost::asio::ip::tcp;

class BinanceSession : public std::enable_shared_from_this<BinanceSession>
{
private:
    tcp::resolver resolver_;
    ssl::stream<beast::tcp_stream> stream_;
    beast::flat_buffer buffer_;
    http::request<http::empty_body> req_;
    http::response<http::string_body> res_;

public:
    explicit BinanceSession(net::any_io_executor ex, ssl::context& ctx)
        : resolver_(ex), stream_(ex, ctx) {}

    void run(const char* host, const char* port, const char* target) {
        if (!SSL_set_tlsext_host_name(stream_.native_handle(), host)) {
            beast::error_code ec{static_cast<int>(::ERR_get_error()), net::error::get_ssl_category()};
            std::cerr << ec.message() << "\n";
            return;
        }

        req_.method(http::verb::get);
        req_.target(target);
        req_.set(http::field::host, host);
        req_.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        resolver_.async_resolve(
            host, port,
            beast::bind_front_handler(&BinanceSession::on_resolve, shared_from_this()));
    }

    void on_resolve(beast::error_code ec, tcp::resolver::results_type results) {
        if (ec) return fail(ec, "resolve");

        beast::get_lowest_layer(stream_).expires_after(std::chrono::seconds(30));

        auto proxy_results = resolver_.resolve("172.16.30.97", "59124");
        beast::get_lowest_layer(stream_).async_connect(
            proxy_results,
            beast::bind_front_handler(&BinanceSession::on_connect, shared_from_this()));
    }

    void on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type) {
        if (ec) return fail(ec, "connect");

        http::request<http::empty_body> connect_req{http::verb::connect, "fapi.binance.com:443", 11};
        connect_req.set(http::field::host, "fapi.binance.com");

        http::async_write(beast::get_lowest_layer(stream_), connect_req,
            beast::bind_front_handler(&BinanceSession::on_connect_write, shared_from_this()));
    }

    void on_connect_write(beast::error_code ec, std::size_t bytes_transferred) {
        boost::ignore_unused(bytes_transferred);

        if (ec) return fail(ec, "connect write");

        http::async_read(beast::get_lowest_layer(stream_), buffer_, res_,
            beast::bind_front_handler(&BinanceSession::on_connect_read, shared_from_this()));
    }

    void on_connect_read(beast::error_code ec, std::size_t bytes_transferred) {
        boost::ignore_unused(bytes_transferred);

        if (ec) return fail(ec, "connect read");

        stream_.async_handshake(
            ssl::stream_base::client,
            beast::bind_front_handler(&BinanceSession::on_handshake, shared_from_this()));
    }

    void on_handshake(beast::error_code ec) {
        if (ec) return fail(ec, "handshake");

        beast::get_lowest_layer(stream_).expires_after(std::chrono::seconds(30));

        http::async_write(stream_, req_,
            beast::bind_front_handler(&BinanceSession::on_write, shared_from_this()));
    }

    void on_write(beast::error_code ec, std::size_t bytes_transferred) {
        boost::ignore_unused(bytes_transferred);

        if (ec) return fail(ec, "write");

        http::async_read(stream_, buffer_, res_,
            beast::bind_front_handler(&BinanceSession::on_read, shared_from_this()));
    }

    void on_read(beast::error_code ec, std::size_t bytes_transferred) {
        boost::ignore_unused(bytes_transferred);

        if (ec) return fail(ec, "read");

        std::cout << res_ << std::endl;

        beast::get_lowest_layer(stream_).expires_after(std::chrono::seconds(30));

        stream_.async_shutdown(
            beast::bind_front_handler(&BinanceSession::on_shutdown, shared_from_this()));
    }

    void on_shutdown(beast::error_code ec) {
        if (ec != net::ssl::error::stream_truncated)
            return fail(ec, "shutdown");
    }

    void fail(beast::error_code ec, char const* what) {
        std::cerr << what << ": " << ec.message() << "\n";
    }
};

int main() {
    constexpr static const char* host = "fapi.binance.com";
    constexpr static const char* port = "443";
    constexpr static const char* target = "/fapi/v1/exchangeInfo";
    net::io_context ioc;
    ssl::context ctx{ssl::context::tlsv12_client};

    ctx.set_verify_mode(ssl::verify_none);
    ctx.set_default_verify_paths();

    std::make_shared<BinanceSession>(net::make_strand(ioc), ctx)->run(host, port, target);

    ioc.run();

    return 0;
}