#include <QCoreApplication>
#include "booleanparser.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    BooleanParser parser;
    qDebug() << parser.parse("true || true && false && false");
    return a.exec();
}
