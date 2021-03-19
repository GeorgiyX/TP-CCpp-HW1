#include <gtest/gtest.h>
#include <random>
#include <memory>
#include "utils.h"

extern "C" {
#include "list_management.h"
#include "io_list_operations.h"
}

const size_t LIST_LENGTH = 250;
const size_t MIN_RANDOM = 1;
const size_t MAX_RANDOM = 1000;
const size_t POPULATION_MULTIPLIER = 10;
const double DOUBLE_1 = 5.000123;
const double DOUBLE_2 = 5.00123;
const double DOUBLE_SMALL_1 = 0.0000001111;
const double DOUBLE_SMALL_2 = 0.0000003123;
const double DOUBLE_BIG_1 = 100000000.00012;
const double DOUBLE_BIG_2 = 100000000.000123;


TEST(MANAGEMENT_TEST, CREATE_NODE) {
    errno = 0;
    auto *node = create_node();
    free(node);
    ASSERT_TRUE(!node == (errno == ENOMEM));
}

TEST(MANAGEMENT_TEST, FREE_NODE) {
    auto *nodeFirst = create_node();
    auto *nodeSecond = create_node();
    if (!nodeFirst || !nodeSecond) {
        throw std::runtime_error("no memory");
    }
    free_node(nullptr);
    free_node(nodeFirst);
    nodeSecond->data.country_name = static_cast<char *>(malloc(1));
    if (!nodeSecond->data.country_name) {
        throw std::runtime_error("no memory");
    }
    free_node(nodeSecond);
    SUCCEED();
}

TEST(MANAGEMENT_TEST, FREE_LIST) {
    auto *nodeFirst = create_node();
    auto *nodeSecond = create_node();
    if (!nodeFirst || !nodeSecond) {
        throw std::runtime_error("no memory");
    }
    nodeFirst->next = nodeSecond;
    free_list(nodeFirst);
    SUCCEED();
}

TEST(MANAGEMENT_TEST, INSERT_NODE_1) {
    country_node *head = nullptr;
    auto node = std::make_shared<country_node>();
    node->next = nullptr;

    ASSERT_EQ(insert_node(nullptr, node.get()), -1);
    ASSERT_EQ(insert_node(nullptr, nullptr), -1);
    ASSERT_EQ(insert_node(&head, node.get()), 0);
    ASSERT_EQ(head, node.get());
}

TEST(MANAGEMENT_TEST, INSERT_NODE_2) {
    std::vector<country_node> nodes(LIST_LENGTH, {{0, 0, 0, nullptr}, nullptr});
    country_node *head = nullptr;
    std::mt19937 gen(TestConfig::testSeed);
    std::uniform_int_distribution<size_t> distrPopulation(MIN_RANDOM, POPULATION_MULTIPLIER * MAX_RANDOM);
    std::uniform_int_distribution<size_t> distrSquare(MIN_RANDOM, MAX_RANDOM);

    for (auto &node : nodes) {
        node.data.population = distrPopulation(gen);
        node.data.square = distrSquare(gen);
        node.data.density = ((double)node.data.population) / node.data.square;
        ASSERT_EQ(insert_node(&head, &node), 0);
    }
    ASSERT_TRUE(head);

    country_node *previous = head;
    country_node *current = head->next;
    while (current) {
        ASSERT_TRUE(previous->data.density <= current->data.density);
        current = current->next;
    }
}

TEST(MANAGEMENT_TEST, COMPARISON_EQUAL) {
    ASSERT_EQ(isLess(DOUBLE_BIG_1, DOUBLE_BIG_1), 0);
    ASSERT_EQ(isLess(DOUBLE_SMALL_1, DOUBLE_SMALL_1), 0);
    ASSERT_EQ(isLess(DOUBLE_1, DOUBLE_1), 0);
}

TEST(MANAGEMENT_TEST, COMPARISON_LESS) {
    ASSERT_EQ(isLess(DOUBLE_BIG_1, DOUBLE_BIG_2), 1);
    ASSERT_EQ(isLess(DOUBLE_SMALL_1, DOUBLE_SMALL_2), 1);
    ASSERT_EQ(isLess(DOUBLE_1, DOUBLE_2), 1);

}

TEST(MANAGEMENT_TEST, COMPARISON_GREATER) {
    ASSERT_EQ(isLess(DOUBLE_BIG_2, DOUBLE_BIG_1), 0);
    ASSERT_EQ(isLess(DOUBLE_SMALL_2, DOUBLE_SMALL_1), 0);
    ASSERT_EQ(isLess(DOUBLE_2, DOUBLE_1), 0);
}
