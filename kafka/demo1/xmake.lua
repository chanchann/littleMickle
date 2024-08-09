add_rules("mode.debug", "mode.release")

add_requires("librdkafka")

add_packages("librdkafka")

target("basic_producer")
    set_kind("binary")
    add_files("src/basic_producer.cc")
