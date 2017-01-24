#include <QString>
#include <QtTest>
#include <vector>
#include "../../Map/src/graph/graph.h"
#include "../../Map/src/a_star/a_star.h"
class map_test : public QObject
{
    Q_OBJECT

public:
    map_test();
    void populate_nodes();
    void populate_nodes2();
private:
    graph test_graph;
    a_star star;
private Q_SLOTS:
    void GRAPH_check_initialize();
    void GRAPH_map_check_weight();
    void GRAPH_check_map_resize();
    void GRAPH_check_neighbors();
    void GRAPH_check_lowest_node_map1();

    void STAR_check_openlist();
    void STAR_check_no_obstacle();
    void STAR_check_path();
    void cleanupTestCase();
};

map_test::map_test()
{
}
void map_test::populate_nodes()
{
    test_graph.add_weight(0, 1, 2);
    test_graph.add_weight(0, 2, 50);
    test_graph.add_weight(0, 8, 2);
    test_graph.add_weight(0, 7, 2);

    test_graph.add_weight(1, 3, 2);
    test_graph.add_weight(1, 9, 2);

    test_graph.add_weight(3, 4, 2);
    test_graph.add_weight(3, 5, 2);

    test_graph.add_weight(5, 6, 2);
    test_graph.add_weight(7, 9, 2);
}
void map_test::populate_nodes2()
{
    test_graph.add_weight(0, 1, 2);
    test_graph.add_weight(0, 2, 50);
    test_graph.add_weight(0, 8, 2);
    test_graph.add_weight(0, 7, 2);

    test_graph.add_weight(1, 3, 2);
    test_graph.add_weight(1, 9, 2);

    test_graph.add_weight(3, 4, 2);
    test_graph.add_weight(3, 5, 2);

    test_graph.add_weight(5, 6, 2);
    test_graph.add_weight(7, 9, 2);
}
void map_test::cleanupTestCase()
{
}
void map_test::GRAPH_check_lowest_node_map1()
{
   star.construct_testmap1(test_graph);
   star.start_path(0,4);
   vector<int> temp_node;
   int test_node = test_graph.return_lowest_path(0,4,0,temp_node);
   QVERIFY2(test_node == 1, "DIDNT RETURN LOWEST NODE");
   test_node = test_graph.return_lowest_path(0,4,test_node,temp_node);
   QVERIFY2(test_node == 3, "DIDNT RETURN LOWEST NODE");
   test_node = test_graph.return_lowest_path(0,4,test_node,temp_node);
   QVERIFY2(test_node == 4, "DIDNT RETURN LOWEST NODE");
   test_graph.reset(false);
   star.start_path(7,4);
   temp_node.clear();
   test_node = test_graph.return_lowest_path(7,4,7,temp_node);
   QVERIFY2(test_node == 0, "DIDNT RETURN LOWEST NODE");
   test_node = test_graph.return_lowest_path(7,4,test_node,temp_node);
   QVERIFY2(test_node == 1, "DIDNT RETURN LOWEST NODE");
   test_graph.reset(false);
}
void  map_test::GRAPH_check_neighbors()
{

    populate_nodes();
    vector<int> bad_list{1,2,7,8};
    vector<int> good_list{1,7,8};
    vector<int> neighbor_list;
    neighbor_list = test_graph.return_neighbor(0);
    QVERIFY2(neighbor_list[1] != bad_list[1], "NEIGHBORS ARE WRONG OR YOU PUT IN OBSTACLE");
    for(int i = 0; i < neighbor_list.size(); i++) {
        QVERIFY2(neighbor_list[i] == good_list[i], "NEIGHBORS ARE WRONG");
    }

    neighbor_list = test_graph.return_neighbor(3);
    good_list[0] = 1;
    good_list[1] = 4;
    good_list[2] = 5;
    for(int i = 0; i < neighbor_list.size(); i++) {
        QVERIFY2(neighbor_list[i] == good_list[i], "NEIGHBORS ARE WRONG");
    }
}
void map_test::GRAPH_check_map_resize()
{
    for(int i = 1; i < 12; i++) {
        test_graph.set_nodes(i);
        QVERIFY2(test_graph.return_size_of_edges() == i, "EDGE SIZE WRONG");
        QVERIFY2(test_graph.return_size_of_nodes() == i, "NODE SIZE WRONG");
    }
}
/*
   The function below is responsible for checking if the initialization of the map is correct
*/
void map_test::GRAPH_check_initialize()
{
    int nodes = test_graph.return_nodes();

    for(int i = 0; i < nodes; i++)
    {
        for(int j = 0; j < nodes; j++)
        {
           if(i == j) {
               QVERIFY2(test_graph.return_weight(i, j) == 5, "ERROR IN WEIGHT");
               QVERIFY2(test_graph.get_movementc(i) == 1000, "ERROR IN WEIGHT");
               //Do node vals
           }
           else
               QVERIFY2(test_graph.return_weight(i, j) == 100, "ERROR IN WEIGHT");
        }
    }
}

/*
  The function below is responsible for checking if I can properly
  add weights to the adjency matrix graphs by position and destination
*/
void map_test::GRAPH_map_check_weight()
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

void map_test::STAR_check_openlist()
{
    populate_nodes();
    star.construct_testmap1(test_graph);
    test_graph.set_weight(7,0,0);
    star.find_neighbors(7,7);
    int pos = star.return_openlist(0);
    QVERIFY2(pos == 0, "ERROR IN OPENLIST");
    pos = star.return_openlist(1);
    QVERIFY2(pos == 9, "ERROR IN OPENLIST");

    star.find_neighbors(1,1);
    pos = star.return_openlist(0);
    QVERIFY2(pos == 0, "ERROR IN OPENLIST");
    pos = star.return_openlist(1);
    QVERIFY2(pos == 3, "ERROR IN OPENLIST");
    pos = star.return_openlist(2);
    QVERIFY2(pos == 9, "ERROR IN OPENLIST");
}
void map_test::STAR_check_no_obstacle()
{
    star.find_neighbors(0,0);
    int pos = star.return_openlist(0);
    QVERIFY2(pos == 1, "ERROR IN OPENLIST");
    pos = star.return_openlist(1);
    QVERIFY2(pos == 7, "ERROR IN OPENLIST");
    pos = star.return_openlist(2);
    QVERIFY2(pos == 8, "ERROR IN OPENLIST");
}
void map_test::STAR_check_path()
{
    vector<int> test_path{7,0,1,3,5,6};
    vector<int> temp;
    star.reset(true);
    star.start_path(7,6);
    temp = star.return_path();
    for(int i = 0; i< temp.size(); i++) {
        QVERIFY2(temp[i] == test_path[i], "PATH IS WRONG");
    }
    vector<int> test_path2{0,1,3,4};
    star.reset(true);
   // star.construct_testmap1(test_graph);
    star.start_path(0,4);
    temp = star.return_path();
    for(int i = 0; i< temp.size(); i++) {
        QVERIFY2(temp[i] == test_path2[i], "PATH IS WRONG");
    }
}

QTEST_APPLESS_MAIN(map_test)

#include "map.moc"
