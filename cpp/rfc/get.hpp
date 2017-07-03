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

    get family:
        get_prefix
        get_prefix_to
        get_suffix
        get_suffix_to
        get_prefix_of_index
        get_prefix_of_index_to
        get_suffix_of_index
        get_suffix_of_index_to

*/

#ifndef RFC_GET_HPP
#define RFC_GET_HPP

#include <regex>
#include <string>
#include <iterator>
#include <algorithm>

namespace k5{

/***********************************************************************/
/*                                                                     */
/*                            get family                               */
/*                                                                     */
/***********************************************************************/

std::string get_prefix( const std::string& user_string, const std::string& user_pattern, const std::string& flags = "o" ){

    bool flags_has_i = flags.find( "i" ) < flags.size();
//    bool flags_has_g = flags.find( "g" ) < flags.size();

    std::regex::flag_type regex_flag                  = flags_has_i ? std::regex_constants::icase         : std::regex_constants::ECMAScript;
//    std::regex_constants::match_flag_type search_flag = flags_has_g ? std::regex_constants::match_default : std::regex_constants::format_first_only;

    std::regex rx( user_pattern, regex_flag );
    std::match_results< std::string::const_iterator > mr;

//    std::regex_search( user_string, mr, rx, search_flag );
    std::regex_search( user_string, mr, rx );

    return mr.prefix().str();
}

void get_prefix_to( const std::string& user_string, std::string& new_user_string, const std::string& user_pattern, const std::string& flags = "o" ){

    bool flags_has_i = flags.find( "i" ) < flags.size();
//    bool flags_has_g = flags.find( "g" ) < flags.size();

    std::regex::flag_type regex_flag                  = flags_has_i ? std::regex_constants::icase         : std::regex_constants::ECMAScript;
//    std::regex_constants::match_flag_type search_flag = flags_has_g ? std::regex_constants::match_default : std::regex_constants::format_first_only;

    std::regex rx( user_pattern, regex_flag );
    std::match_results< std::string::const_iterator > mr;

//    std::regex_search( user_string, mr, rx, search_flag );
    std::regex_search( user_string, mr, rx );

    new_user_string = mr.prefix().str();
}



std::string get_suffix( const std::string& user_string, const std::string& user_pattern, const std::string& flags = "o" ){

    bool flags_has_i = flags.find( "i" ) < flags.size();
//    bool flags_has_g = flags.find( "g" ) < flags.size();

    std::regex::flag_type regex_flag                  = flags_has_i ? std::regex_constants::icase         : std::regex_constants::ECMAScript;
//    std::regex_constants::match_flag_type search_flag = flags_has_g ? std::regex_constants::match_default : std::regex_constants::format_first_only;

    std::regex rx( user_pattern, regex_flag );
    std::match_results< std::string::const_iterator > mr;

//    std::regex_search( user_string, mr, rx, search_flag );
    std::regex_search( user_string, mr, rx );

    return mr.suffix().str();
}

void get_suffix_to( const std::string& user_string, std::string& new_user_string, const std::string& user_pattern, const std::string& flags = "o" ){

    bool flags_has_i = flags.find( "i" ) < flags.size();
//    bool flags_has_g = flags.find( "g" ) < flags.size();

    std::regex::flag_type regex_flag                  = flags_has_i ? std::regex_constants::icase         : std::regex_constants::ECMAScript;
//    std::regex_constants::match_flag_type search_flag = flags_has_g ? std::regex_constants::match_default : std::regex_constants::format_first_only;

    std::regex rx( user_pattern, regex_flag );
    std::match_results< std::string::const_iterator > mr;

//    std::regex_search( user_string, mr, rx, search_flag );
    std::regex_search( user_string, mr, rx );

    new_user_string = mr.suffix().str();
}

std::string get_prefix_of_index( const std::string& user_string, const std::string& user_pattern, int position ){

    std::regex rx( user_pattern, std::regex_constants::icase );
    std::match_results< std::string::const_iterator > mr;

    if( position < 0 ){
        std::string temp = user_string;
        unsigned int counter = 0;

        while( std::regex_search( temp, mr, rx ) ){
            temp = mr.suffix().str();
            ++counter;
        }
        position = counter + position;
    }

    std::string temp = user_string;
    std::string the_prefix;
    while( std::regex_search( temp, mr, rx ) ){
        if( !position-- ){
            if( mr.str() != "" ){
                return the_prefix;
            }
            break;
        }

        the_prefix += mr.prefix().str() + mr.str();
        temp = mr.suffix().str();
    }

    return user_string;
}

void get_prefix_of_index_to( const std::string& user_string, std::string& new_user_string, const std::string& user_pattern, int position ){

    std::regex rx( user_pattern, std::regex_constants::icase );
    std::match_results< std::string::const_iterator > mr;

    if( position < 0 ){
        std::string temp = user_string;
        unsigned int counter = 0;

        while( std::regex_search( temp, mr, rx ) ){
            temp = mr.suffix().str();
            ++counter;
        }
        position = counter + position;
    }

    std::string temp = user_string;
    std::string the_prefix;
    while( std::regex_search( temp, mr, rx ) ){
        if( !position-- ){
            if( mr.str() != "" ){
                new_user_string = the_prefix;
            }
            break;
        }

        the_prefix += mr.prefix().str() + mr.str();
        temp = mr.suffix().str();
    }
}

std::string get_suffix_of_index( const std::string& user_string, const std::string& user_pattern, int position ){

    std::regex rx( user_pattern, std::regex_constants::icase );
    std::match_results< std::string::const_iterator > mr;

    if( position < 0 ){
        std::string temp = user_string;
        unsigned int counter = 0;

        while( std::regex_search( temp, mr, rx ) ){
            temp = mr.suffix().str();
            ++counter;
        }
        position = counter + position;
    }

    std::string temp = user_string;
    while( std::regex_search( temp, mr, rx ) ){
        if( !position-- ){
            if( mr.str() != "" ){
                return mr.suffix().str();
            }
            break;
        }
        temp = mr.suffix().str();
    }

    return user_string;
}

void get_suffix_of_index_to( const std::string& user_string, std::string& new_user_string, const std::string& user_pattern, int position ){

    std::regex rx( user_pattern, std::regex_constants::icase );
    std::match_results< std::string::const_iterator > mr;

    if( position < 0 ){
        std::string temp = user_string;
        unsigned int counter = 0;

        while( std::regex_search( temp, mr, rx ) ){
            temp = mr.suffix().str();
            ++counter;
        }
        position = counter + position;
    }

    std::string temp = user_string;
    while( std::regex_search( temp, mr, rx ) ){
        if( !position-- ){
            if( mr.str() != "" ){
                new_user_string = mr.suffix().str();
            }
            break;
        }
        temp = mr.suffix().str();
    }

}

} // end of namespace k5


#endif // RFC_GET_HPP

