#include <QString>
#include <QtTest>

class path_test : public QObject
{
    Q_OBJECT

public:
    path_test();

private Q_SLOTS:
    void path_case1();
};

path_test::path_test()
{
}

void path_test::path_case1()
{
    QVERIFY(false);
}

QTEST_APPLESS_MAIN(path_test)

#include "map.moc"
