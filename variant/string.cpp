#include <fc/string.hpp>
#include <fc/utility.hpp>
#include <fc/fwd_impl.hpp>

#include <sstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <locale>
#include <limits>

/**
 *  Implemented with std::string for now.
 */

namespace fc {
    class comma_numpunct : public std::numpunct<char> {
    protected:
        virtual char do_thousands_sep() const { return ','; }

        virtual std::string do_grouping() const { return "\03"; }
    };

    std::string to_pretty_string(int64_t value) {
        std::stringstream ss;
        ss.imbue({std::locale(), new comma_numpunct});
        ss << std::fixed << value;
        return ss.str();
    }

#ifdef USE_FC_STRING
    string::string(const char* s, int l) :my(s,l){ }
    string::string(){}
    string::string( const fc::string& c ):my(*c.my) { }
    string::string( string&& m ):my(fc::move(*m.my)) {}
    string::string( const char* c ):my(c){}
    string::string( const_iterator b, const_iterator e ):my(b,e){}
    string::string( const std::string& s ):my(s) {}
    string::string( std::string&& s ):my(fc::move(s)) {}
    string::~string() { }
    string::operator std::string&() { return *my; }
    string::operator const std::string&()const { return *my; }
    char* string::data() { return &my->front(); }

    string::iterator string::begin()            { return &(*this)[0]; }
    string::iterator string::end()              { return &(*this)[size()]; }
    string::const_iterator string::begin()const { return my->c_str(); }
    string::const_iterator string::end()const   { return my->c_str() + my->size(); }

    char&       string::operator[](size_t idx)      { return (*my)[idx]; }
    const char& string::operator[](size_t idx)const { return (*my)[idx]; }

    void       string::reserve(size_t r)           { my->reserve(r); }
    size_t   string::size()const                   { return my->size(); }
    size_t   string::find(char c, size_t p)const { return my->find(c,p); }
    size_t   string::find(const fc::string& str, size_t pos /* = 0 */) const { return my->find(str, pos); }
    size_t   string::find(const char* s, size_t pos /* = 0 */) const { return my->find(s,pos); }
    size_t   string::rfind(char c, size_t p)const { return my->rfind(c,p); }
    size_t   string::rfind(const char* c, size_t p)const { return my->rfind(c,p); }
    size_t   string::rfind(const fc::string& c, size_t p)const { return my->rfind(c,p); }
    size_t   string::find_first_of(const fc::string& str, size_t pos /* = 0 */) const { return my->find_first_of(str, pos); }
    size_t   string::find_first_of(const char* s, size_t pos /* = 0 */) const { return my->find_first_of(s, pos); }

    fc::string& string::replace(size_t pos,  size_t len,  const string& str) { my->replace(pos, len, str); return *this; }
    fc::string& string::replace(size_t pos,  size_t len,  const char* s) { my->replace(pos, len, s); return *this; }

    void       string::clear()                       { my->clear(); }
    void       string::resize( size_t s )          { my->resize(s); }

    fc::string string::substr( size_t start, size_t len )const { return my->substr(start,len); }
    const char* string::c_str()const                        { return my->c_str(); }

    bool    string::operator == ( const char* s )const   { return *my == s; }
    bool    string::operator == ( const string& s )const { return *my == *s.my; }
    bool    string::operator != ( const string& s )const { return *my != *s.my; }

    string& string::operator =( const string& c )          { *my = *c.my; return *this; }
    string& string::operator =( string&& c )               { *my = fc::move( *c.my ); return *this; }

    string& string::operator+=( const string& s )          { *my += *s.my; return *this; }
    string& string::operator+=( char c )                   { *my += c; return *this; }

    bool operator < ( const string& a, const string& b )   { return *a.my < *b.my; }
    string operator + ( const string& s, const string& c ) { return string(s) += c; }
    string operator + ( const string& s, char c ) 	 { return string(s) += c; }
#endif // USE_FC_STRING


    template<class Type>
    Type stringToNum(const string &str) {
        std::istringstream iss(str);
        Type num;
        iss >> num;
        return num;
    }

    template<class T>
    std::string ConvertToString(T value) {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }

    int64_t to_int64(const fc::string &i) {
        return stringToNum<int64_t>(i);
    }

    uint64_t to_uint64(const fc::string &i) {
        return stringToNum<uint64_t>(i);
    }

    double to_double(const fc::string &i) {
        return stringToNum<double>(i);
    }

    fc::string to_string(double d) {
        // +2 is required to ensure that the double is rounded correctly when read back in.  http://docs.oracle.com/cd/E19957-01/806-3568/ncg_goldberg.html
        std::stringstream ss;
        ss << std::setprecision(std::numeric_limits<double>::digits10 + 2) << std::fixed << d;
        return ss.str();
    }

    fc::string to_string(uint64_t d) {
        return ConvertToString<uint64_t>(d);
    }

    fc::string to_string(int64_t d) {
        return ConvertToString<int64_t>(d);
    }

    fc::string to_string(uint16_t d) {
        return ConvertToString<uint16_t>(d);
    }

    inline string &ltrim(string &str) {
        string::iterator p = find_if(str.begin(), str.end(), std::not1(std::ptr_fun<int, int>(isspace)));
        str.erase(str.begin(), p);
        return str;
    }

    inline string &rtrim(string &str) {
        string::reverse_iterator p = find_if(str.rbegin(), str.rend(), std::not1(std::ptr_fun<int, int>(isspace)));
        str.erase(p.base(), str.end());
        return str;
    }

    inline string &trim1(string &str) {
        ltrim(rtrim(str));
        return str;

    }

    std::string trim(const std::string &s) {
        auto cpy = s;
        auto s1 = trim1(cpy);
        return s1;

    }

    std::string to_lower(const std::string &s) {
        auto cpy = s;
        std::transform(s.begin(), s.end(), cpy.begin(), ::tolower);
        return cpy;
    }

    string trim_and_normalize_spaces(const string &s) {
        string result = (s);

        return result;
    }

} // namespace fc


