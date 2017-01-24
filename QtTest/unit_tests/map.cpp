#include <QString>
#include <QtTest>
#include "../../Map/src/graph/graph.h"
class map_test : public QObject
{
    Q_OBJECT

public:
    map_test();
private:
    graph test_graph;


private Q_SLOTS:
    void check_initialize();
    void map_check_weight();
    void initTestCase();
    void cleanupTestCase();
};

map_test::map_test()
{
}
void map_test::initTestCase()
{

}
void map_test::cleanupTestCase()
{

}
/*
   The function below is responsible for checking if the initialization of the map is correct
*/
void map_test::check_initialize()
{
    int nodes = test_graph.return_nodes();

    for(int i = 0; i < nodes; i++)
    {
        for(int j = 0; j < nodes; j++)
        {
           if(i == j)
               QVERIFY2(test_graph.return_weight(i, j) == 2, "ERROR IN WEIGHT");
           else
               QVERIFY2(test_graph.return_weight(i, j) == 100, "ERROR IN WEIGHT");
        }
    }
}

/*
  The function below is responsible for checking if I can properly
  add weights to the adjency matrix graphs by position and destination
*/
void map_test::map_check_weight()
{
    int pos = 0;
    int des = 1;
    int weight = 2;
    test_graph.add_weight(pos, des, weight);
    QVERIFY2(test_graph.return_weight(pos, des) == weight, "ERROR IN WEIGHT");
    QVERIFY2(test_graph.return_weight(des,pos) == weight, "ERROR IN WEIGHT");

    for(int i = 0; i < 5; i++)
    {
        pos = i;
        des = 0;
        weight = 40;
        test_graph.add_weight(pos, des, weight);
        QVERIFY2(test_graph.return_weight(pos, des) == weight, "ERROR IN WEIGHT");
        QVERIFY2(test_graph.return_weight(des,pos) == weight, "ERROR IN WEIGHT");
    };
}

QTEST_APPLESS_MAIN(map_test)

#include "map.moc"
