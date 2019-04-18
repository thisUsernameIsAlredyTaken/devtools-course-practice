#ifndef MODULES_REGEXPR_INCLUDE_MATCH_NODE_H_
#define MODULES_REGEXPR_INCLUDE_MATCH_NODE_H_

#include <string>
#include <set>

/*
 * Char class ([abc])             V
 * Any count of chars ([abc]*)    V
 * One or zero chars ([abc]?)     V
 * Some chars ([abc]{1,5})        V
 * Group ((abc|defg))             X
 */

class MatchNode {
public:
    virtual bool match(std::string::const_iterator &it) const = 0;
};

class MN_CharSetSingle : public MatchNode {
public:
    MN_CharSetSingle(const std::set<char> &s);
    MN_CharSetSingle(const std::string &s);
    MN_CharSetSingle(const char *s);
    virtual bool match(std::string::const_iterator &it) const override;
protected:
    std::set<char> chSet_;
};

class MN_CharSetAnyCount : public MN_CharSetSingle {
public:
    MN_CharSetAnyCount(const std::set<char> &s);
    MN_CharSetAnyCount(const std::string &s);
    MN_CharSetAnyCount(const char *s);
    virtual bool match(std::string::const_iterator &it) const override;
};

class MN_CharSetOneOrZero : public MN_CharSetSingle {
public:
    MN_CharSetOneOrZero(const std::set<char> &s);
    MN_CharSetOneOrZero(const std::string &s);
    MN_CharSetOneOrZero(const char *s);
    virtual bool match(std::string::const_iterator &it) const override;
};

class MN_CharSetCertainCount : public MN_CharSetSingle {
public:
    MN_CharSetCertainCount(const std::set<char> &s);
    MN_CharSetCertainCount(const std::string &s);
    MN_CharSetCertainCount(const char *s);
    virtual bool match(std::string::const_iterator &it) const override;
private:
    int minCount_;
    int maxCount_;
};

#endif // MODULES_REGEXPR_INCLUDE_MATCH_NODE_H_

