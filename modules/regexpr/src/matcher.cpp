// Copyright 2019 Zhivaev Artem

#include "include/matcher.h"

#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

const array<char, 62> Matcher::kAlphabet = {{
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' }};

pair<int, int> Matcher::parseBraces(string::const_iterator &it) {
    pair<int, int> result;
    string str("");
    stringstream ss;

    ++it;
    while (*it != ',') {
        str += *it;
        ++it;
    }
    str += '\n';
    ++it;

    ss << str;

    str.erase();
    while (*it != '}') {
        str += *it;
        ++it;
    }
    str += '\n';
    ++it;

    ss << str;

    ss >> result.first;
    ss >> result.second;

    return result;
}

void Matcher::initModif(string::const_iterator &it) {
    if (*it == '{') {
        auto p = parseBraces(it);

        min_ = p.first;
        max_ = p.second;
    } else {
        switch (*it) {
         case '*':
            min_ = 0;
            max_ = -1;
            ++it;
            break;
         case '+':
            min_ = 1;
            max_ = -1;
            ++it;
            break;
         case '?':
            min_ = 0;
            max_ = 1;
            ++it;
            break;
         default:
            min_ = 1;
            max_ = 1;
            break;
        };
    }
}

void Matcher::setNext(Matcher *next) {
    next_ = next;
}

Matcher::Matcher()
    : next_(nullptr), min_(0), max_(0) {}

Matcher::~Matcher() {}



bool MCharSet::match(string::const_iterator &it) const {
    int i;
    for (i = 0; i != max_; ++i) {
        if (chSet_.find(*it) != chSet_.end()) {
            ++it;
        } else {
            break;
        }
    }

    if (i < min_) {
        return false;
    }
    return true;
}

MCharSet::MCharSet(string::const_iterator &it) {
    if (*it == '[') {
        ++it;
        while (*it != ']') {
            if (*next(it, 1) == '-') {
                auto chSt = *it;
                advance(it, 2);
                auto chTo = *it;
                for_each(find(kAlphabet.begin(), kAlphabet.end(), chSt),
                         next(find(kAlphabet.begin(), kAlphabet.end(), chTo),
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

    initModif(it);
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

