#ifndef MULTI_LANG_H
#define MULTI_LANG_H
#include <string>
#include <map>
#include <vector>

using namespace std;

namespace multiLang{
    void init();
    string get(int langIdx, string key);
}
#endif