## Regex Function Collection

### Cplusplus version

There are more than one header file. You can use them all, one by one
or just `include "rfc/rfc.hpp"` if you have the whole directory, or if
not, you just need `rfc.hpp`. If you just want to use **split family**
you can: `include "rfc/split.hpp"`. Header files have been separated by
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

 #### [valid family](https://github.com/k-five/RFC/blob/master/cpp/rfc/valid.hpp): for validation a pattern.

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

---


 #### [parse](https://github.com/k-five/RFC/blob/master/cpp/rfc/parse.hpp) family:

 - `parse`
 - `parse_to`

 ```C++
#include <iostream>
#include "rfc/parse.hpp"

int main( int argc,const char** argv ){

    /// parse
    std::cout << k5::parse( argv ) << '\n'; // returns a single string of all main argument

    /// parse_to
    std::string main_arg;
    k5::parse_to( argv, main_arg );         // void
    std::cout << main_arg << '\n';

return 0;}

/* the output:

 ideas   ./temp one two three
./temp one two three
./temp one two three

*/
 ```

 - `parse_count`
 - `parse_all`
 - `parse_all_to`

 ```C++
#include <iostream>
#include "rfc/parse.hpp"

int main( int argc,const char** argv ){

    /// parse_count: counts the number argument with - or -- (= single dash or double dash)
    std::cout << k5::parse_count( argv ) << '\n';

    std::puts( "----------------\n" );
    /// parse_all:   returns a vector of string of all main argument that have - or --
    for( const std::string& s : k5::parse_all( argv ) ){
        std::cout << s << '\n';
    }

    std::puts( "----------------\n" );
    /// parse_all_to: acts like parse_all but it is void
    std::vector< std::string > vs;
    k5::parse_all_to( argv, vs );
    for( const std::string& s : vs ){
        std::cout << s << '\n';
    }

return 0;}

/* the output:

 ideas   ./temp one two three
0
----------------

----------------

 ideas   ./temp -one --two ---three
3
----------------

-one
--two
--three
----------------

-one
--two
--three
 ideas   ./temp -one a --two a b ---three a b c
3
----------------

-one a
--two a b
--three a b c
----------------

-one a
--two a b
--three a b c


*/
 ```
 - `parse_index`
 - `parse_index_to`

 ```C++
#include <iostream>
#include "rfc/parse.hpp"

int main( int argc, const char** argv ){

    /// parse_index:        parse a specific argument, returns a single string
    std::cout << k5::parse_index( argv, 2 ) << '\n';

    std::puts( "---------------------------" );
    /// parse_index_to      like above,but is is void
    std::string main_arg_index_2;
    k5::parse_index_to( argv, main_arg_index_2, 2 );
    std::cout << main_arg_index_2 << '\n';

    // note:
    // index 0: -one a
    // index 1: --two a b
    // index 2: --three a b c
    // index 3: --three a b c d

return 0;}

/* the output:

 ideas $  ./temp -one a --two a b ---three a b c
--three a b c
---------------------------
--three a b c
 ideas $  ./temp -one a --two a b ---three a b c ----four a b c d
--three a b c
---------------------------
--three a b c

*/
 ```

 - `parse_index_all`
 - `parse_index_all_to`

 ```C++
#include <iostream>
#include "rfc/parse.hpp"

int main( int argc, const char** argv ){

    /// parse_index_all     parse a specific argument, but returns a vector of string of all its options
    for( const std::string& s : k5::parse_index_all( argv, 2 ) ){
        std::cout << s << '\n';
    }

    /// parse_index_all_to  like above, but it is void
    // std::vector< std::string > vs;
    // k5::parse_index_all_to( argv, vs, 2 );

return 0;}

/* the output:

 ideas $  ./temp -one a --two a b ---three a b c ----four a b c d
--three
a
b
c
 ideas $  ./temp -one a --two a b ---three aaa bbb ccc ----four a b c d
--three
aaa
bbb
ccc
 ideas $  ./temp -one a --two a b -three aaa bbb ccc ----four a b c d
-three
aaa
bbb
ccc
 ideas $  ./temp -one a --two a b three aaa bbb ccc ----four a b c d
--four
a
b
c
d
 ideas $


*/

 ```
 - `parse_option`
 - `parse_option_to`
 - `parse_option_all`
 - `parse_option_all_to`

 ```C++
#include <iostream>
#include "rfc/parse.hpp"

int main( int argc, const char** argv ){

    /// parse_option        acts like parse_index, except looking for an argument by getting a string, and return a single string
    const std::string s = k5::parse_option( argv, "--three" );
    std::cout << s << '\n';

    /// parse_option_to     like above, but is is void

    std::puts( "----------------------" );
    /// parse_option_all    like above, but return a vector of string for all part of that option
    std::vector< std::string > vs = k5::parse_option_all( argv, "--three" );
    for( const auto& s : vs ){
        std::cout << s << '\n';
    }

    /// parse_option_all_to like above, but it is void

return 0;}

/* the output:

 ideas $  # there is not --three, so there would not be any output
 ideas $  ./temp -one a --two a b three aaa bbb ccc ----four a b c d

----------------------

 ideas $
 ideas $  ./temp -one a --two a b --three aaa bbb ccc ----four a b c d
--three aaa bbb ccc
----------------------
--three
aaa
bbb
ccc
 ideas $  ./temp -one a --two a b --three 1 2 3 ----four a b c d
--three 1 2 3
----------------------
--three
1
2
3
 ideas $

*/
```

---

#### [split](https://github.com/k-five/RFC/blob/master/cpp/rfc/split.hpp) family

- `split`
- `split_to`

```C++
#include <iostream>
#include <list>
#include "rfc/split.hpp"

int main(){

    /// split   splits a string to a vector of string or other valid containers

    const std::string str( "first second third fourth fifth" );
    for( const std::string& s : k5::split( str ) ){  // delimiter by default is "\\s+"
        std::cout << s << '\n';
    }

    std::puts( "--------------------------" );
    typedef std::list< std::string > lofs;                  // list of string

    for( const std::string& s : k5::split< lofs >( str ) ){  // delimiter by default is "\\s+"
        std::cout << s << '\n';
    }

    // note
    // you can use any other delimiters

    std::puts( "--------------------------" );
    /// split_to    acts like above, but is is void
    lofs ls;
    std::string str2( "it#is#not#the#size###of#####the###dog##in#the#fight..." );
    k5::split_to( str2, ls, "#+" );
    for( const std::string& s : ls ){
        std::cout << s << ' ';
    }


return 0;}

/* the output:

first
second
third
fourth
fifth
--------------------------
first
second
third
fourth
fifth
--------------------------
it is not the size of the dog in the fight...

*/
```

---


#### [join](https://github.com/k-five/RFC/blob/master/cpp/rfc/join.hpp) family

- `join`
- `join_to`

```C++
#include <iostream>
#include <list>
#include "rfc/join.hpp"

int main(){

    typedef std::vector< int > vofi;
    typedef std::list< int >   lofi;

    vofi vi{ 1,2,3,4,5 };
    lofi li{ -1,-2,-3,-4,-5 };

    /// join        returns a single string
    std::cout << k5::join( vi )        << '\n';                     // glue by default " "
    std::cout << k5::join( vi, " + " ) << '\n';                     // the glue is " + "
    std::cout << k5::join( vi.begin(), vi.begin() + 3 ) << '\n';    // with iterator

    /// join_to     like above, but void
    std::string r;
    k5::join_to( li, r, " : " );
    std::cout << r << '\n';


return 0;}

/* the output:

1 2 3 4 5
1 + 2 + 3 + 4 + 5
1 2 3
-1 : -2 : -3 : -4 : -5

*/
```

---


#### [substitute]() family

- `substitute`
- `substitute_to`
- `substitute_all`
- `substitute_all_to`
- `substitute_at_index`
- `substitute_at_index_to`

```C++
#include <iostream>
#include "rfc/substitute.hpp"

int main(){


    /// substitute                  returns a modified string
    std::string str( "first SECOND third fourth fifth" );
    std::cout << k5::substitute( str, "[a-z]+", "---" ) << "\n\n";

    /// substitute_to               like substitute but it is void
    std::string temp;
    k5::substitute_to( str, temp, "SECOND", "###" );
    std::cout << temp << "\n\n";

    /// substitute_all              like substitute but by default is has 'g' flag and 'i' flag
    std::cout << k5::substitute_all( str, "[a-z]+", "---" ) << "\n\n";

    /// substitute_all_to           like substitute_all but it is void

    /// substitute_at_index         like substitute by with a specific index
    std::cout << k5::substitute_at_index( str, "[a-z]+", "###", 1 ) << "\n\n";

    /// substitute_at_index_to      like above, but it is void


return 0;}

/* the output:

--- SECOND third fourth fifth

first ### third fourth fifth

--- --- --- --- ---

first SECOND ### fourth fifth

*/

``

---


#### [match]() family

- `match`
- `match_to`
- `match_all`
- `match_all_to`
- `match_at_index`
- `match_at_index_to`
- `has_match`

```C++
#include <iostream>
#include "rfc/match.hpp"

int main(){

    const char* const nl2 = "\n\n";

    /// match   returns a vector of string
    std::string str( "first second 3333.3333 fourth 5555.5555" );
    for( const std::string& s :  k5::match( str, "\\d+" ) ){
        std::cout << s << ' ';
    }
    std::cout << '\n';
    for( const std::string& s :  k5::match( str, "\\d+", "g" ) ){
        std::cout << s << ' ';
    }
    std::cout << nl2;

    /// match_to

    /// match_all

    /// match_all_to
    std::vector< std::string > vs;
    k5::match_all_to( str, vs, "[a-z]+" );
    for( const auto& s : vs ){
        std::cout << s << ' ';
    }
    std::cout << nl2;

    /// match_at_index
    std::cout << k5::match_at_index( str, "\\d+", -1 ) << '\n';

    /// match_at_index_to

    /// has_match
    std::cout << std::boolalpha << k5::has_match( str, "\\d+" ) << '\n';


return 0;}

/* the output:

3333
3333 3333 5555 5555

first second fourth

5555
true

*/
```

---

#### [get]() family

- `get_prefix`
- `get_prefix_to`
- `get_suffix`
- `get_suffix_to`
- `get_prefix_of_index`
- `get_prefix_of_index_to`
- `get_suffix_of_index`
- `get_suffix_of_index_to`

```C++
#include <iostream>
#include "rfc/get.hpp"


int main(){

    const char* const nl2 = "\n\n";

    ///get_prefix
    std::string str( "How are you today? I am fine, how about you?" );
    std::cout << k5::get_prefix( str, "\\?" ) << nl2;

    ///get_prefix_to

    ///get_suffix
    std::cout << k5::get_suffix( str, "\\?" ) << nl2;

    ///get_suffix_to

    ///get_prefix_of_index
    str += " fine, too. Do you have $1 million dollars?";
    std::cout << k5::get_prefix_of_index( str, "\\?", 1 ) << nl2;

    ///get_prefix_of_index_to

    ///get_suffix_of_index
    std::cout << k5::get_suffix_of_index( str, "\\?", 1 ) << nl2;

    ///get_suffix_of_index_to


return 0;}

/* the output:

How are you today

 I am fine, how about you?

How are you today?

 fine, too. Do you have $1 million dollars?


*/

```




