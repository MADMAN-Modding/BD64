#include <dpp/dpp.h>
#include "include/private.hpp"
#include "include/base64Maps.hpp"
#include "decode.cpp"
#include "encode.cpp"
    
const std::string BOT_TOKEN = token;

std::string encode(std::string text) {
    Encode encode;

    return encode.encode(text, Base64Maps::base64CharMapRev);
};


int main() {

    dpp::cluster bot(BOT_TOKEN);

    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "encode") {
            std::string text = std::get<std::string>(event.get_parameter("input"));
            
            event.reply(std::string(encode(text)));
        }
    });

    bot.on_ready([&bot](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            dpp::slashcommand encodeCommand("encode", "Input a string to encode", bot.me.id);

            encodeCommand.add_option(
                dpp::command_option(dpp::co_string, "input", "Text to encode", true)
                    .add_choice(dpp::command_option_choice("Wahoo", std::string("wahoo")))
            );
        }
    });

    bot.start(dpp::st_wait);

    return 0;
}