#include "booleanparser.h"
#include <QList>

bool BooleanParser::parse(const QString &expr)
{
    in = expr;
    in.replace(" ", "");
    pos = 0;

    return parseOrExpression();
}

bool BooleanParser::parseOrExpression()
{
    bool r1 = parseAndExpression();
    if(matchToken("||")){
        QList<bool> l;
        l.append(r1);
        while(matchToken("||")){
            pos += 2;
            l.append(parseAndExpression());
        }
        bool f = false;
        for(int i = 0; i < l.count(); ++i){
            if(l.at(i)){
                f = true;
                break;
            }
        }
        return f;
    }else {
        return r1;
    }

}

bool BooleanParser::parseAndExpression()
{
    bool r1= parseNotExpression();
    if (matchToken("&&")) {
        QList<bool> l;
        l.append(r1);
        while(matchToken("&&")){
            pos += 2;
            l.append(parseNotExpression());
        }
        bool f = true;
        for(int i = 0; i < l.count(); ++i){
            if(!l.at(i)){
                f = false;
                break;
            }
        }
        return f;
    } else {
        return r1;
    }
}

bool BooleanParser::parseNotExpression()
{
    if (matchToken("!")) {
        while (matchToken("!")){
            pos += 1;
        }
        bool f = parseAtom();
        return !f;
    } else {
        return parseAtom();
    }
}

bool BooleanParser::parseAtom()
{
    if (matchToken("(")) {
        bool f = true;
        pos += 1;
        f = parseOrExpression();
        pos += 1;
        return f;
    } else {
        return parseIdentifier();
    }
}

bool BooleanParser::parseIdentifier()
{
    int startPos = pos;
    while (pos < in.length() && in[pos].isLetterOrNumber())
        ++pos;

    if (pos > startPos) {
        QString str = in.mid(startPos, pos - startPos);
        if(str.toLower() == "true"){
            return true;
        }else{
            return false;
        }
    } else {
        return false;
    }
}

bool BooleanParser::matchToken(const QString &str) const
{
    return in.mid(pos, str.length()) == str;
}
