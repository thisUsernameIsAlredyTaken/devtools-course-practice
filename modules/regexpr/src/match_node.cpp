#include "include/match_node.h"

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
}

MCharSet::MCharSet(const string &s) {
    /*
     * TODO
     */
}



bool MGroup::match(string::const_iterator &it) const {
    /*
     * TODO
     */
}

MGroup::MGroup(const string &s) {
    /*
     * TODO
     */
}

MGroup::~MGroup() {
    for (auto i : members_) {
        delete i;
    }
}

