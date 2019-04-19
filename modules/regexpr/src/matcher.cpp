// Copyright 2019 Zhivaev Artem

#include "include/matcher.h"

using std::string;

void Matcher::setNext(Matcher *next) {
    next_ = next;
}

Matcher::Matcher()
    : next_(nullptr), mod_(Modif::kNone), min_(-1), max_(-1) {}

Matcher::~Matcher() {}



bool MCharSet::match(string::const_iterator &it) const {
    /*
     * TODO
     */
    return false;
}

MCharSet::MCharSet(string::const_iterator &it) {
    /*
     * TODO
     */
    if (*it == '[') {
        while (*it != ']') {
            ++it;
        }
        ++it;
    } else {
        ++it;
    }
}


bool MGroup::match(string::const_iterator &it) const {
    /*
     * TODO
     */
    return false;
}

MGroup::MGroup(string::const_iterator &it) {
    /*
     * TODO
     */
}

MGroup::~MGroup() {
    for (auto i : members_) {
        delete i;
    }
}

