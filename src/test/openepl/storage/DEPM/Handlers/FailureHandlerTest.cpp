#include "utility/UnorderedMap.h"
#include "storage/DEPM/Node/Failure.h"
#include "storage/DEPM/Handlers/MapHandler.h"

#include "test/openepl_gtest.h"

using namespace OpenEPL::DEPM;

TEST(FailureHandler, Instantiation) {
    auto map = UnorderedMap<Key, Failure>();
    auto handler = MapHandler<Failure, FailureProps>(map);
}


TEST(FailureHandler, CreateNode) {
    auto map = UnorderedMap<Key, Failure>();
    auto handler = MapHandler<Failure, FailureProps>(map);

    #define FAILURE_1_KEY "F1"
    #define FAILURE_1_PROPS "failure1 props"
    #define FAILURE_2_PROPS "failure2 props"

    //create new failure item
    auto failure1 = Failure(FailureProps(FAILURE_1_PROPS));
    EXPECT_EQ(failure1.getProperties().property, FAILURE_1_PROPS);

    //create another failure item
    auto failure2 = Failure(FailureProps(FAILURE_2_PROPS));
    EXPECT_EQ(failure2.getProperties().property, FAILURE_2_PROPS);

    // insert first failure item in to the map
    auto x = handler.insert(FAILURE_1_KEY, failure1) = failure2;
    EXPECT_EQ(handler.get(FAILURE_1_KEY).getProperties().name, FAILURE_1_KEY);
    EXPECT_EQ(handler.get(FAILURE_1_KEY).getProperties().property, FAILURE_1_PROPS);

    handler.insert("F1", failure1) = failure2;

    std::cout<<"F1: "<<handler.get("F1")<<std::endl;

    auto created = handler.create("F1", failure1);
    std::cout<<"x: "<<x<<std::endl;
    std::cout<<"failure1: "<<failure1<<std::endl;
    std::cout<<"created: "<<created<<std::endl;
    std::cout<<"F1: "<<handler.get("F1")<<std::endl;
    handler.get("F1") = x;
    std::cout<<"F1: "<<handler.get("F1")<<std::endl;
    EXPECT_FALSE(created == failure1); // separate objects
    EXPECT_NE(&created, &failure1); // separate objects
    EXPECT_EQ(created.getProperties().property, failure1.getProperties().property); // but, same value
    EXPECT_NE(std::addressof(created.getProperties()), std::addressof(failure1.getProperties())); // separate props

    EXPECT_NE(handler.get("F1"), handler.get("F1")); // retrieved objects equal
    EXPECT_EQ(&created, &handler.get("F1")); // retrieved objects equal

    handler.getProperties(failure1).property = "new value";
    EXPECT_NE(created.getProperties().property, failure1.getProperties().property); // same value

    handler.create("F2", failure1);
    handler.create("F3", failure1);
    handler.create("F4", failure1);

    EXPECT_EQ(map.size(), 4); // 4 unique items added
    EXPECT_EQ(handler.get("F4").getProperties().property, "x > y");

    handler.create("F4", FailureProps("y <= 7"));
    EXPECT_EQ(map.size(), 4); // 4 unique items added
    EXPECT_EQ(handler.get("F4").getProperties().property, "y <= 7");
}

TEST(FailureHandler, Delete) {
    auto map = UnorderedMap<Key, Failure>();
    auto handler = MapHandler<Failure, FailureProps>(map);

    handler.create("F1", FailureProps("x > y"));
    handler.create("F2", FailureProps("y < 3"));
    handler.create("F3", FailureProps("x < 6"));
    handler.create("F4", FailureProps("y > -1"));

    EXPECT_EQ(map.size(), 4); // 4 unique items added

    handler.remove("F3");
    EXPECT_EQ(map.size(), 3); // down to 3
}

TEST(FailureHandler, Create) {
    auto map = UnorderedMap<Key, Failure>();
    auto handler = MapHandler<Failure, FailureProps>(map);

    handler.create("F1", FailureProps("x > y"));
    handler.create("F2", FailureProps("y < 3"));
    handler.create("F3", FailureProps("x < 6"));
    handler.create("F4", FailureProps("y > -1"));

    EXPECT_EQ(map.size(), 4); // 4 unique items added
    EXPECT_EQ(handler.get("F4").getProperties().property, "y > -1");
    EXPECT_EQ(handler.get("F3").getProperties().property, "x < 6");
    EXPECT_EQ(handler.get("F2").getProperties().property, "y < 3");
    EXPECT_EQ(handler.get("F1").getProperties().property, "x > y");
}

TEST(FailureHandler, Update) {
    auto map = UnorderedMap<Key, Failure>();
    auto handler = MapHandler<Failure, FailureProps>(map);

    handler.create("F1", FailureProps("x > y"));
    handler.create("F2", FailureProps("y < 3"));
    handler.create("F3", FailureProps("x < 6"));
    handler.create("F4", FailureProps("y > -1"));

    EXPECT_EQ(map.size(), 4); // 4 unique items added
    handler.create("F4", FailureProps("y <= 7"));
    EXPECT_EQ(map.size(), 4); // 4 unique items added
    EXPECT_EQ(handler.get("F4").getProperties().property, "y <= 7");
}
