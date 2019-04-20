// Copyright 2019 Zhivaev Artem

#ifndef MODULES_REGEXPR_INCLUDE_MATCH_NODE_H_
#define MODULES_REGEXPR_INCLUDE_MATCH_NODE_H_

#include <string>
#include <set>
#include <vector>
#include <array>


class Matcher {
 public:
    virtual bool match(std::string::const_iterator &it) const = 0;
    void setNext(Matcher *pn);
    Matcher();
    virtual ~Matcher();
 protected:
    Matcher *next_; /* if next_ matched, stop current matching */
    int min_, max_;

    void initModif(std::string::const_iterator &it);

    static const std::array<char, 62> kAlphabet;

 private:
    static std::pair<int, int> parseBraces(std::string::const_iterator &it);
};

class MCharSet : public Matcher {
 public:
    virtual bool match(std::string::const_iterator &it) const override;
    MCharSet(std::string::const_iterator &it);
 protected:
    std::set<char> chSet_;
};

class MGroup : public Matcher {
 public:
    virtual bool match(std::string::const_iterator &it) const override;
    MGroup(std::string::const_iterator &it);
    ~MGroup();
 protected:
    std::vector<Matcher*> members_;
};

#endif // MODULES_REGEXPR_INCLUDE_MATCH_NODE_H_

