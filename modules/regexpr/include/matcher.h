// Copyright 2019 Zhivaev Artem

#ifndef MODULES_REGEXPR_INCLUDE_MATCHER_H_
#define MODULES_REGEXPR_INCLUDE_MATCHER_H_

#include <string>
#include <set>
#include <vector>
#include <array>
#include <utility>


class Matcher {
 public:
    virtual bool match(std::string::const_iterator *ptrit) const = 0;
    void setNext(Matcher *pn);
    Matcher();
    virtual ~Matcher();
 protected:
    Matcher *next_; /* if next_ matched, stop current matching */
    int min_, max_;

    void initModif(std::string::const_iterator *ptrit);

    static const std::array<char, 62> kAlphabet;

 private:
    static std::pair<int, int> parseBraces(std::string::const_iterator *pit);
};

class MCharSet : public Matcher {
 public:
    bool match(std::string::const_iterator *ptrit) const override;
    explicit MCharSet(std::string::const_iterator *ptrit);
 protected:
    std::set<char> chSet_;
};

class MGroup : public Matcher {
 public:
    bool match(std::string::const_iterator *ptrit) const override;
    explicit MGroup(std::string::const_iterator *ptrit);
    ~MGroup();
 protected:
    std::vector<Matcher*> members_;
};

#endif  // MODULES_REGEXPR_INCLUDE_MATCHER_H_

