add_rules("mode.debug", "mode.release")

add_requires("websocketpp")

add_packages("websocketpp")

target("client")
    set_kind("binary")
    add_files("examples/client.cc")

target("server")
    set_kind("binary")
    add_files("examples/server.cc")