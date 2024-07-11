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

std::string decode(std::string text)
{
    Decode decode;

    return decode.decode(text);
}

int main()
{
    dpp::cluster bot(BOT_TOKEN);

    bot.on_log(dpp::utility::cout_logger());

    bot.on_slashcommand([](const dpp::slashcommand_t &event)
        {
            std::string command = event.command.get_command_name();
                
            if (command == "encode") {
                // Gets the input
                std::string text = std::get<std::string>(event.get_parameter("input"));

                // If the user doesn't want the original text shown then it will set the extra variable to ""
                std::string extra = std::get<bool>(event.get_parameter("show_original")) ? text + " in base 64 is: " : "";
                
                // Initializes the ephemeral variable to put
                int ephemeral = dpp::m_put;

                // This allows the code to not crash when the variable isn't set
                try
                {                    
                    // If the user wants the text hidden then it will be ephemeral, else put
                    ephemeral = std::get<bool>(event.get_parameter("hidden")) ? dpp::m_ephemeral : ephemeral;
                }
                catch(const std::exception& e) {}
                
                // Sends the message to the user
                event.reply(dpp::message(extra + encode(text)).set_flags(ephemeral));

            } else if (command == "decode") {
                // Gets the input
                std::string text = std::get<std::string>(event.get_parameter("input"));
                
                // If the user doesn't want the original text shown then it will set the extra variable to ""
                std::string extra = std::get<bool>(event.get_parameter("show_original")) ? text + " from base 64 is: " : "";

                // Initializes the ephemeral variable to put
                int ephemeral = dpp::m_put;

                // This allows the code to not crash when the variable isn't set
                try
                {                    
                    // If the user wants the text hidden then it will be ephemeral, else put
                    ephemeral = std::get<bool>(event.get_parameter("hidden")) ? dpp::m_ephemeral : ephemeral;
                }
                catch(const std::exception& e) {}

                // Sends the message to the user
                event.reply(dpp::message(extra + decode(text)).set_flags(ephemeral));          
            } else {
                // If something messes up then send this
                event.reply("Something went wrong");
            }
        });

    bot.on_ready([&bot](const dpp::ready_t &event)
                 {
                     if (dpp::run_once<struct register_bot_commands>())
                     {
                        // Makes the commands
                        dpp::slashcommand encode("encode", "Enter text to encode", bot.me.id);
                        dpp::slashcommand decode("decode", "Enter text to decode", bot.me.id);

                        // Encoding commands
                        encode.add_option(
                            dpp::command_option(dpp::co_string, "input", "The text to encode", true));
                        encode.add_option(dpp::command_option(dpp::co_boolean, "show_original", "Show the original text?", true));

                        encode.add_option(dpp::command_option(dpp::co_boolean, "hidden", "Keep the response hidden to you?", false)); 
                        
                        // Decoding commands
                        decode.add_option(
                            dpp::command_option(dpp::co_string, "input", "The text to decode", true));
                        decode.add_option(
                            dpp::command_option(dpp::co_boolean, "show_original", "Show the original text?", true));

                        decode.add_option(dpp::command_option(dpp::co_boolean, "hidden", "Keep the response hidden to you?", false)); 

                        // Creates the commands 
                        bot.global_command_create(encode);
                        bot.global_command_create(decode);
                     } });

    bot.start(dpp::st_wait);

    return 0;
}