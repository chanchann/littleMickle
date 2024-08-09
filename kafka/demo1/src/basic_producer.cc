#include <iostream>
#include <string>
#include <memory>
#include <librdkafka/rdkafkacpp.h>
#include "message.pb.h"

class KafkaProducer {
private:
    std::unique_ptr<RdKafka::Producer> producer;
    std::string topic;

public:
    KafkaProducer(const std::string& brokers, const std::string& topic) : topic(topic) {
        std::string errstr;
        RdKafka::Conf* conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
        
        conf->set("bootstrap.servers", brokers, errstr);
        producer.reset(RdKafka::Producer::create(conf, errstr));
        delete conf;
    }

    bool send(const message::PeriodMessage& msg) {
        std::string serialized_msg;
        if (!msg.SerializeToString(&serialized_msg)) {
            std::cerr << "Failed to serialize message" << std::endl;
            return false;
        }

        RdKafka::ErrorCode err = producer->produce(
            topic,
            RdKafka::Topic::PARTITION_UA,
            RdKafka::Producer::RK_MSG_COPY,
            const_cast<char*>(serialized_msg.c_str()),
            serialized_msg.size(),
            nullptr, 0, 0, nullptr, nullptr
        );

        if (err != RdKafka::ERR_NO_ERROR) {
            std::cerr << "Failed to produce message: " << RdKafka::err2str(err) << std::endl;
            return false;
        }

        producer->poll(0);
        return true;
    }

    ~KafkaProducer() {
        producer->flush(10000);
    }
};

int main() {
    std::string brokers = "localhost:9092";
    std::string topic = "test_topic";

    KafkaProducer producer(brokers, topic);

    message::PeriodMessage msg;
    msg.set_period(123);
    msg.set_ts(456);
    msg.set_post_ts(789);
    msg.set_poster_id("test_poster");

    message::SymbolInfo* symbol_info = msg.add_symbol_infos();
    symbol_info->set_symbol("BTCUSDT");

    message::TradeInfo* trade = symbol_info->add_trades();
    trade->set_timestamp(1234567890);
    trade->set_side("B");
    trade->set_price(50000.0);
    trade->set_amount(1.5);

    message::IncrementOrderBookInfo* inc = symbol_info->add_incs();
    inc->set_timestamp(1234567891);
    inc->set_is_snapshot(false);
    inc->set_side("A");
    inc->set_price(50001.0);
    inc->set_amount(2.0);

    if (producer.send(msg)) {
        std::cout << "Message sent successfully" << std::endl;
    } else {
        std::cout << "Failed to send message" << std::endl;
    }

    return 0;
}