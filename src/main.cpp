#include <dpp/dpp.h>
#include "include/private.hpp"
#include "include/base64Maps.hpp"
#include "decode.cpp"
#include "encode.cpp"

const std::string BOT_TOKEN = token;

std::string encode(std::string text)
{
    Encode encode;

    return encode.encode(text);
};

int main()
{
    dpp::cluster bot(BOT_TOKEN);

    bot.on_log(dpp::utility::cout_logger());

    bot.on_slashcommand([](const dpp::slashcommand_t &event)
                        {
        if (event.command.get_command_name() == "encode") {
            std::string text = std::get<std::string>(event.get_parameter("input"));
            
            // event.reply(std::string(encode(text)));
            event.reply(text + " in base64 is: " + encode(text));
        } else {
            event.reply("Not right here");          
        } });

    bot.on_ready([&bot](const dpp::ready_t &event)
                 {
                     if (dpp::run_once<struct register_bot_commands>())
                     {
                         //     bot.global_command_create(dpp::slashcommand("encode", "Input a string to encode", bot.me.id)
                         //     .add_option(dpp::command_option(dpp::co_string, "text", "What you want to encode")));
                         dpp::slashcommand encode("encode", "Enter text to encode", bot.me.id);

                         encode.add_option(
                             dpp::command_option(dpp::co_string, "input", "The text to encode", true));

                        bot.global_command_create(encode);
                     }
                 });

    bot.start(dpp::st_wait);

    return 0;
}