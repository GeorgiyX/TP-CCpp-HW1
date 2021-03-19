#include <gtest/gtest.h>
#include <experimental/filesystem>
#include <fstream>
#include "utils.h"

extern "C" {
#include "io_list_operations.h"
}
const std::string ERROR_COUNTRY_NAME = "0 0 0.00 error_country_name\n";
namespace fs = std::experimental::filesystem;

TEST_F(IO_TEST, RRINT_ERROR_COUNTRY) {
    auto node = std::make_shared<country_node>();
    node->data.square = 0;
    node->data.population = 0;
    node->data.density = 0;
    node->next = nullptr;
    node->data.country_name = nullptr;
    print_list(node.get());
    ASSERT_EQ(getTestOutput(), ERROR_COUNTRY_NAME);
}

TEST_F(IO_TEST, COMPLEX_TEST) {
    country_node *head = nullptr;
    for (auto &entity : fs::directory_iterator(TestConfig::testDataPath)) {
        setTestInput(entity / "in.txt");
        std::cerr << "FILE INPUT:" << std::endl;
        std::cerr << file2string(IN_STREAM_FILE) << std::endl;
        std::cerr << "FILE INPUT" << std::endl;
        errno = 0;
        head = get_ordered_list();
        ASSERT_TRUE(!head == (errno == ENOMEM));
        print_list(head);
        free_list(head);
        ASSERT_EQ(getTestOutput(), file2string(entity / "out.txt"));
        clearTestOutput();
    }
}
