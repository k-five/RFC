## Regex Function Collection

### Cplusplus version

There are more than one header file. You can use them all, one by one
or just `include `rfc/rfc.hpp` if you have the whole directory, or if
not, you just need `rfc.hpp`. If you just want to use **split family**
you can: `include `rfc/split.hpp`. Header files have been separated by
family.

Families:
 - valid
 - parse
 - split
 - join
 - substitute
 - match
 - get
 - count

 ## Examples:

 ### valid family: for validation a pattern.

 ```C++
#include <iostream>
#include "rfc/valid.hpp"

int main(){

    /// regex_is_valid

    const char* r = k5::regex_is_valid( "/\/\\" ); // returns regex_error.what() or nullptr
    if( !r ){
        std::cout << "okay valid\n";
    } else {
        std::cout << "not valid: " << r << '\n';
    }

    std::cout << std::string( 20, '-' ) << '\n';

    std::string s_pat( "/\/\\" );
    if( k5::regex_is_valid( s_pat ) ){              // returns true or false
        std::cout << "okay valid\n";
    } else {
        std::cout << "not valid\n";
    }

return 0;}

/* the output:

not valid: Unexpected end of regex when escaping.
--------------------
not valid

*/
 ```

 ### parse family:
