#include "convert_command_line_arguments.h"

#include <docopt/docopt.h>
#include <string>


/**
 * converts the command line arguments into \see InputParameter.
 * If the conversion is not possible an \see Unexpected Message is returned
 **/
Expected<InputParameter, std::string>
convertCommandLineArguments(int argc, char const* argv[])
{
    static constexpr auto commandlineUsage =
      R"(podmate 0.1
        Usage:
              podmate <input-file> <output-header-file> <output-source-file> <output-header-preamble> <output-source-preamble>
              podmate (-h | --help)
              podmate --version
        Options:
              -h --help     Show this screen.
              --version     Show version.
    )";
    try {
        //Use docopt_parse to trigger exceptions instead of programm termination
        std::map<std::string, docopt::value> args = docopt::docopt_parse(commandlineUsage, { std::next(argv), std::next(argv, argc) });

        std::string const inputFileName="<input-file>";
        std::string const outputHeaderFile="<output-header-file>";
        std::string const outputSourceFile="<output-source-file>";
        std::string const outputHeaderPreamble = "<output-header-preamble>";
        std::string const outputSourcePreamble = "<output-source-preamble>";
        
        return InputParameter{
            args[inputFileName].asString(),
            OutputFileParameters{
                args[outputHeaderFile].asString(),
                args[outputSourceFile].asString(),
                args[outputHeaderPreamble].asString(),
                args[outputSourcePreamble].asString()
            }
        };
    } catch (docopt::DocoptLanguageError const& exception) {
        return Unexpected(std::string("sorry, this shouldn't have happend. Please consider to report this bug"));
    } catch (docopt::DocoptArgumentError const& exception) {
        return Unexpected(std::string(exception.what()) + "\n" + commandlineUsage);
    } catch (docopt::DocoptExitHelp const& exception) {
        return Unexpected(std::string(commandlineUsage));
    } catch (docopt::DocoptExitVersion const& exception) {
        return Unexpected(std::string("podmate 0.1"));
    }
}
