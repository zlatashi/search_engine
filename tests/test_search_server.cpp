#include "gtest/gtest.h"
#include "../src/InvertedIndex.h"
#include "../src/SearchServer.h"
#include <vector>
#include <string>

using namespace std;

TEST(TestCaseSearchServer, TestSimple) {
    const vector<string> docs = {
        "milk milk milk milk water water water",
        "milk water water",
        "milk milk milk milk milk water water water water water",
        "americano cappuccino"
    };
    const vector<string> request = { "milk water", "sugar" };
    const std::vector<vector<RelativeIndex>> expected = {
        {
            {2, 1},
            {0, 0.7f},
            {1, 0.3f}
        },
        {
        }
    };
    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);
    SearchServer srv(idx);
    std::vector<vector<RelativeIndex>> result = srv.search(request);
    ASSERT_EQ(result.size(), expected.size());
    // compare element-wise with tolerance for floats
    ASSERT_EQ(result[0].size(), expected[0].size());
    EXPECT_EQ(result[0][0].doc_id, expected[0][0].doc_id);
    EXPECT_FLOAT_EQ(result[0][0].rank, expected[0][0].rank);
    EXPECT_EQ(result[0][1].doc_id, expected[0][1].doc_id);
    EXPECT_NEAR(result[0][1].rank, expected[0][1].rank, 1e-5f);
    EXPECT_EQ(result[0][2].doc_id, expected[0][2].doc_id);
    EXPECT_NEAR(result[0][2].rank, expected[0][2].rank, 1e-5f);
    EXPECT_TRUE(result[1].empty());
}

TEST(TestCaseSearchServer, TestTop5) {
    const vector<string> docs = {
        "london is the capital of great britain",
        "paris is the capital of france",
        "berlin is the capital of germany",
        "rome is the capital of italy",
        "madrid is the capital of spain",
        "lisboa is the capital of portugal",
        "bern is the capital of switzerland",
        "moscow is the capital of russia",
        "kiev is the capital of ukraine",
        "minsk is the capital of belarus",
        "astana is the capital of kazakhstan",
        "beijing is the capital of china",
        "tokyo is the capital of japan",
        "bangkok is the capital of thailand",
        "welcome to moscow the capital of russia the third rome",
        "amsterdam is the capital of netherlands",
        "helsinki is the capital of finland",
        "oslo is the capital of norway",
        "stockholm is the capital of sweden",
        "riga is the capital of latvia",
        "tallinn is the capital of estonia",
        "warsaw is the capital of poland"
    };
    const vector<string> request = { "moscow is the capital of russia" };
    const std::vector<vector<RelativeIndex>> expected = {
        {
            {7, 1},
            {14, 1},
            {0, 0.666666687f},
            {1, 0.666666687f},
            {2, 0.666666687f}
        }
    };
    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);
    SearchServer srv(idx);
    std::vector<vector<RelativeIndex>> result = srv.search(request);

    ASSERT_EQ(result.size(), expected.size());
    ASSERT_EQ(result[0].size(), expected[0].size());
    for (size_t i = 0; i < expected[0].size(); ++i) {
        EXPECT_EQ(result[0][i].doc_id, expected[0][i].doc_id);
        EXPECT_NEAR(result[0][i].rank, expected[0][i].rank, 1e-5f);
    }
}
