#ifndef MODULES_REGEXPR_INCLUDE_MATCH_NODE_H_
#define MODULES_REGEXPR_INCLUDE_MATCH_NODE_H_

#include <string>
#include <set>
#include <vector>

enum Modif {
    kNone,
    kSingle,
    kAsterisk,
    kQMark,
    kRange,
};

class Matcher {
 public:
    virtual bool match(std::string::const_iterator &it) const = 0;
    void setNext(Matcher*);
    Matcher();
    virtual ~Matcher();
 protected:
    Matcher *next_;
    Modif mod_;
    int min_, max_;
};

class MCharSet : public Matcher {
 public:
    virtual bool match(std::string::const_iterator &it) const override;
    MCharSet(const std::string&);
 protected:
    std::set<char> chSet_;
};

class MGroup : public Matcher {
 public:
    virtual bool match(std::string::const_iterator &it) const override;
    MGroup(const std::string&);
    ~MGroup();
 protected:
    std::vector<Matcher*> members_;
};

#endif // MODULES_REGEXPR_INCLUDE_MATCH_NODE_H_

