#include <gtest/gtest.h>
#include <random>
#include "utils.h"

extern "C" {
#include "list_management.h"
}

const size_t LIST_LENGTH = 100;

TEST(MANAGEMENT_TESTS, CREATE_NODE) {
    errno = 0;
    auto *node = create_node();
    free(node);
    ASSERT_TRUE(!node && (errno == ENOMEM));
}

TEST(MANAGEMENT_TESTS, FREE_NODE) {
    auto *nodeFirst = create_node();
    auto *nodeSecond = create_node();
    if (!nodeFirst || !nodeSecond) {
        throw std::runtime_error("no memory");
    }
    free(nullptr);
    free(nodeFirst);
    nodeSecond->data.country_name = static_cast<char *>(malloc(1));
    if (!nodeSecond->data.country_name) {
        throw std::runtime_error("no memory");
    }
    free(nodeSecond);
    SUCCEED();
}

TEST(MANAGEMENT_TESTS, INSERT_NODE_1) {
    country_node *head = nullptr;
    auto node = std::make_shared<country_node>();
    node->next = nullptr;

    ASSERT_EQ(insert_node(nullptr, node.get()), -1);
    ASSERT_EQ(insert_node(nullptr, nullptr), -1);
    ASSERT_EQ(insert_node(&head, node.get()), 0);
    ASSERT_EQ(head, node.get());
}

TEST(MANAGEMENT_TESTS, INSERT_NODE_2) {
    std::vector<country_node> nodes(LIST_LENGTH, {0,0, nullptr, nullptr });
    std::mt19937 random(TestConfig::testSeed);
    country_node *head = nullptr;

    for(auto &node : nodes) {
        node.data.population = random();
        ASSERT_EQ(insert_node(&head, &node), 0);
        std::cout << "node random: " << node.data.population << std::endl;
    }
    ASSERT_TRUE(head);

    country_node *previous = head;
    country_node *current = head->next;
    while (current) {
        ASSERT_TRUE(previous->data.population <= current->data.population);
        current = current->next;
    }
}
