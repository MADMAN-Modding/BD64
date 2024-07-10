#include <dpp/dpp.h>
#include "include/private.hpp"
#include "include/base64Maps.hpp"
#include "decode.cpp"
#include "encode.cpp"
    
const std::string BOT_TOKEN = token;

std::string encode(std::string text) {
    Encode encode;

    return encode.encode(text);
};


int main() {
    dpp::cluster bot(BOT_TOKEN, dpp::i_default_intents  | dpp::i_message_content);

    bot.on_log(dpp::utility::cout_logger());

    dpp::commandhandler command_handler(&bot);

    command_handler.add_prefix(".").add_prefix("/");
    // bot.on_slashcommand([](const dpp::slashcommand_t& event) {
    //     if (event.command.get_command_name() == "encode") {
    //         std::string text = std::get<std::string>(event.get_parameter("input"));
            
    //         event.reply(std::string(encode(text)));
    //     }
    // }); 

    bot.on_ready([&command_handler](const dpp::ready_t &event) {
        // if (dpp::run_once<struct register_bot_commands>()) {
        //     bot.global_bulk_command_delete();

        //     bot.global_command_create(dpp::slashcommand("encode", "Input a string to encode", bot.me.id)
        //     .add_option(dpp::command_option(dpp::co_string, "text", "What you want to encode")));
        // }

        command_handler.add_command(
            // Command Name
            "encode",

            {
                {"input", dpp::param_info(dpp::pt_string, true, "Text to encode")}
            },

            /* Command handler */
            [&command_handler](const std::string& command, const dpp::parameter_list_t& parameters, dpp::command_source src) {
                std::string got_param;
                if (!parameters.empty()) {
                    got_param = std::get<std::string>(parameters[0].second);
                }
                command_handler.reply(dpp::message(encode(got_param)), src);
            },

            // Description
            "Encodes the user input to base64"
        );

    });


    bot.start(dpp::st_wait);

    return 0;
}