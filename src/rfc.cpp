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

    content:

    valid family:
        regex_is_valid (1)
        regex_is_valid (2)

*/

namespace k5 {

/***********************************************************************/
/*                                                                     */
/*                            valid family                             */
/*                                                                     */
/***********************************************************************/

bool regex_is_valid( const std::string& user_pattern ){
    bool result = false;

    try{
        std::regex regex( user_pattern );
        result = true;
    } catch( const std::regex_error& ){
        result = false;
    }

    return result;
}

const char* regex_is_valid( const char* user_pattern ){
    const char* result = nullptr;
    try{
        std::regex regex( user_pattern );
    } catch( const std::regex_error& re ){
        result = re.what();
    }

    return result;
}

/***********************************************************************/
/*                                                                     */
/*                            parse family                             */
/*                                                                     */
/***********************************************************************/

std::string parse( const char** argv, const char* glue = " " ){

    std::string result;
    while( *argv ){
        result += *argv;
        result += glue;
        argv++;
    }

    return result;
}

void parse_to( const char** argv, std::string& user_string, const char* glue = " " ){

    while( *argv ){
        user_string += *argv;
        user_string += glue;
        argv++;
    }
}

} // end of namespace k5
