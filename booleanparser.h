#ifndef BOOLEANPARSER_H
#define BOOLEANPARSER_H


class BooleanParser
{
public:
    //Node *parse(const QString &expr);
    bool parse(const QString &expr);

private:
    bool parseOrExpression();
    bool parseAndExpression();
    bool parseNotExpression();
    bool parseAtom();
    bool parseIdentifier();
    void addChild(Node *parent, Node *child);
    void addToken(Node *parent, const QString &str, Node::Type type);
    bool matchToken(const QString &str) const;

    QString in;
    int pos;
};

#endif
