#include <gtest/gtest.h>
#include <random>
#include <memory>
#include "utils.h"

extern "C" {
#include "list_management.h"
}

const size_t LIST_LENGTH = 250;
const size_t MIN_RANDOM = 1;
const size_t MAX_RANDOM = 1000;

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
    std::uniform_int_distribution<size_t> distribution(MIN_RANDOM, MAX_RANDOM);
    for (auto &node : nodes) {
        node.data.population = distribution(gen);
        node.data.square = distribution(gen);
        node.data.density = node.data.population / node.data.square;
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
