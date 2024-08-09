add_rules("mode.debug", "mode.release")

add_requires("websocketpp")

target("server")
    set_kind("binary")
    add_files("src/server.cc")
