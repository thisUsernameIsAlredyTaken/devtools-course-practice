// Copyright 2019 Zhivaev Artem

#include "include/matcher.h"

#include <iostream>
#include <algorithm>

using namespace std;

const array<char, 62> Matcher::alphabet({
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
    'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
    'u', 'v', 'w', 'x', 'y', 'z',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
});

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
    if (chSet_.find(*it) != chSet_.end()) {
        ++it;
        return true;
    }

    ++it;
    return false;
}

MCharSet::MCharSet(string::const_iterator &it) {
    if (*it == '[') {
        ++it;
        while (*it != ']') {
            if (*next(it, 1) == '-') {
                auto chSt = *it;
                advance(it, 2);
                auto chTo = *it;
                for_each(find(alphabet.begin(), alphabet.end(), chSt),
                         next(find(alphabet.begin(), alphabet.end(), chTo),
                              1),
                         [this](char ch) { chSet_.insert(ch); });
            } else {
                chSet_.insert(*it);
            }
            ++it;
        }
        ++it;
    } else {
        chSet_.insert(*it);
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

