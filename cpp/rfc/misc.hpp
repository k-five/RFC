/*
    +-------------------------------------+
    |Regex Function Collection ( or: RFC )|
    |-------------------------------------|
    |Written by Shakiba (=k-five) in 2017,|
    |shared on Git-Hub .../k-five/RFC,    |
    |All things that is used, is from std,|
    |there is no nonstandard library, but,|
    |you can use boost in place of std.   |
    +-------------------------------------+
    |Any bug, suggestion, critic, opinion,|
    |would be appreciated. Feel free if y-|
    |ou need a special function that you c|
    |ould not find it here.               |
    +-------------------------------------+
    | contact me: vhsu30@yahoo.com        |
    | github: k-five                      |
    | stackoverflow: k-five               |
    | twitter: k__five                    |
    +-------------------------------------+

    =======================================

    miscellaneous family
        fold
        auto-zero-leading
*/

#ifndef RFC_MICS_HPP
#define RFC_MICS_HPP

#include <regex>
#include <string>
#include <utility>

namespace k5{


/***********************************************************************/
/*                                                                     */
/*                           miscellaneous                             */
/*                                                                     */
/***********************************************************************/

std::pair< std::string, std::string > fold
( const std::string& user_string, const std::string& user_pattern, const std::string& flags = "o" ){

    const bool flags_has_i = flags.find( "i" ) < flags.size();
//    const bool flags_has_g = flags.find( "g" ) < flags.size();

    std::regex::flag_type regex_flag                  = flags_has_i ? std::regex_constants::icase         : std::regex_constants::ECMAScript;
//    std::regex_constants::match_flag_type search_flag = flags_has_g ? std::regex_constants::match_default : std::regex_constants::format_first_only;
    std::regex rx( user_pattern, regex_flag );
    std::match_results< std::string::const_iterator > mr;

//    std::regex_search( user_string, mr, rx, search_flag );  // search_flag has no effect
    std::regex_search( user_string, mr, rx );

    return { mr.prefix().str(), mr.suffix().str() };
}


class auto_zero_leading {
private:
    static unsigned int count__;
    static unsigned int base__;
           const char*  glue__;
    static const char*  zero__;

public:
    auto_zero_leading() = delete;
    auto_zero_leading( const auto_zero_leading& ) = delete;
    auto_zero_leading( auto_zero_leading&& )      = delete;
    auto_zero_leading operator=( const auto_zero_leading& ) = delete;
    auto_zero_leading operator=( auto_zero_leading&& )      = delete;

    explicit auto_zero_leading( const unsigned int count, const char* glue  )
    : glue__( glue )
    {
        zero__ +=( 50 - count );
        if( !*zero__ ){
            base__ = 0;
            glue__ = "";
        }
    }

    friend std::ostream& operator<<( std::ostream& output, const auto_zero_leading& azl ){
        if( count__ == base__ ){
            ++zero__;
            base__ *= 10;
        }
        return output << zero__ << count__++ << azl.glue__;
    }

};
unsigned int auto_zero_leading::count__ = 1;
unsigned int auto_zero_leading::base__  = 10;
const char*  auto_zero_leading::zero__  = "00000000000000000000000000000000000000000000000000";


} // end of namespace k5

#endif // RFC_MICS_HPP
