set_languages("cxx20")

add_rules("mode.debug", "mode.release")

add_requires("boost")
add_requires("nlohmann_json")
add_requires("openssl")

add_packages("boost")
add_packages("nlohmann_json")
add_packages("openssl")

target("binance_future_demo")
    set_kind("binary")
    add_files("src/*.cc")
