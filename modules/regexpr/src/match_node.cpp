#include "include/match_node.h"

using std::set;
using std::string;

MN_CharSetSingle::MN_CharSetSingle(const string &s) {
    for (auto i : s) {
        chSet_.insert(i);
    }
}

MN_CharSetSingle::MN_CharSetSingle(const set<char> &s) {
    chSet_ = s;
}

MN_CharSetSingle::MN_CharSetSingle(const char *s) {
    const char *p;

    for (p = s; *p != '\0'; ++p) {
        chSet_.insert(*p);
    }
}

bool MN_CharSetSingle::match(string::const_iterator &it) const {
    if (chSet_.find(*it) != chSet_.end()) {
        ++it;
        return true;
    }
    return false;
}




MN_CharSetAnyCount::MN_CharSetAnyCount(const set<char> &s)
    : MN_CharSetSingle(s) {}

MN_CharSetAnyCount::MN_CharSetAnyCount(const string &s)
    : MN_CharSetSingle(s) {}

MN_CharSetAnyCount::MN_CharSetAnyCount(const char *s)
    : MN_CharSetSingle(s) {}

bool MN_CharSetAnyCount::match(string::const_iterator &it) const {
    while (chSet_.find(*it) != chSet_.end()) {
        ++it;
    }
    return true;
}




MN_CharSetOneOrZero::MN_CharSetOneOrZero(const set<char> &s)
    : MN_CharSetOneOrZero(s) {}

MN_CharSetOneOrZero::MN_CharSetOneOrZero(const string &s)
    : MN_CharSetOneOrZero(s) {}

MN_CharSetOneOrZero::MN_CharSetOneOrZero(const char *s)
    : MN_CharSetOneOrZero(s) {}

bool MN_CharSetOneOrZero::match(string::const_iterator &it) const {
    ++it;
    return false;
}

