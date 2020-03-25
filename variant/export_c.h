//
// Created by dongbo on 2020-03-25.
//

#ifndef FC_VARIANT_EXPORT_C_H
#define FC_VARIANT_EXPORT_C_H


#ifdef __cplusplus
extern "C" {
#endif

typedef struct govariant govariant;


govariant *SetInt(int f);
govariant *SetInt64(long long f);
govariant *SetuInt(unsigned int f);
govariant *SetuInt64(unsigned long long f);
govariant *SetString(char *s, int len);
govariant *SetFloat(float f);
govariant *SetDouble(double f);
int GetType(govariant *gv);
int GetInt(govariant *gv);
long long GetInt64(govariant *gv);
unsigned int GetuInt(govariant *gv);
unsigned long long GetuInt64(govariant *gv);
float GetFloat(govariant *gv);
double GetDouble(govariant *gv);
int GetString(govariant *gv, void *s, int len);


#ifdef __cplusplus
}
#endif

#endif //FC_VARIANT_EXPORT_C_H
