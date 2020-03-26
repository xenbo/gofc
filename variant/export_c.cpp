//
// Created by dongbo on 2020-03-25.
//
#include "export_c.h"
#include "fc/variant.hpp"


struct govariant {
    template<class T>
    govariant(T t) : v(t) {

    }

    fc::variant v;
};

govariant *SetInt(int f) { return new govariant(f); }

govariant *SetInt64(long long f) { return new govariant(f); }

govariant *SetuInt(unsigned int f) { return new govariant(f); }

govariant *SetuInt64(unsigned long long f) { return new govariant(f); }

govariant *SetString(char *s, int len) { return new govariant(std::string((const char *) s, len)); }

govariant *SetFloat(float f) { return new govariant(f); }

govariant *SetDouble(double f) { return new govariant(f); }

int GetType(govariant *gv) { return gv->v.get_type(); }

int GetInt(govariant *gv) { return gv->v.as_int64(); }

long long GetInt64(govariant *gv) { return gv->v.as_int64(); }

unsigned int GetuInt(govariant *gv) { return gv->v.as_uint64(); }

unsigned long long GetuInt64(govariant *gv) { return gv->v.as_uint64(); }

float GetFloat(govariant *gv) { return gv->v.as_double(); }

double GetDouble(govariant *gv) { return gv->v.as_double(); }

int GetString(govariant *gv, void *s, int len) {
    auto a = std::string(gv->v.as_string());
    if (a.length() < len)
        len = a.length();

    memcpy(s, a.c_str(), len);
    return len;
}

char *ToString(govariant *gv) {
    auto a = std::string(gv->v.as_string());
    return (char *) a.c_str();
}



