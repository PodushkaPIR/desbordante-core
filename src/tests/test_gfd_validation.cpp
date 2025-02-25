#include <filesystem>  // for path, operator/
#include <memory>      // for unique_ptr
#include <vector>      // for vector

#include <gtest/gtest.h>  // for TypedTestSuitePState, ASS...

#include "algorithms/algo_factory.h"        // for CreateAndLoadAlgorithm
#include "algorithms/gfd/gfd_validation.h"  // for GfdValidation
#include "config/names.h"                   // for kGfdData, kGraphData
#include "csv_config_util.h"                // for kTestDataDir
#include "gfd/egfd_validation.h"            // for EGfdValidation
#include "gfd/naivegfd_validation.h"        // for NaiveGfdValidation

class Gfd;

namespace algos {
class GfdHandler;
}

using namespace algos;
using algos::StdParamsMap;

namespace tests {

namespace {

auto current_path = kTestDataDir / "graph_data";

template <typename T>
class GfdValidationTest : public ::testing::Test {
protected:
    std::unique_ptr<algos::GfdHandler> CreateGfdValidationInstance(
            std::filesystem::path const& graph_path,
            std::vector<std::filesystem::path> const& gfd_paths) {
        StdParamsMap option_map = {{config::names::kGraphData, graph_path},
                                   {config::names::kGfdData, gfd_paths}};
        return algos::CreateAndLoadAlgorithm<T>(option_map);
    }
};

TYPED_TEST_SUITE_P(GfdValidationTest);

TYPED_TEST_P(GfdValidationTest, TestTrivially) {
    auto graph_path = current_path / "quadrangle.dot";
    auto gfd_path = current_path / "quadrangle_gfd.dot";
    std::vector<std::filesystem::path> gfd_paths = {gfd_path};
    auto algorithm = TestFixture::CreateGfdValidationInstance(graph_path, gfd_paths);
    int expected_size = 1;
    algorithm->Execute();
    std::vector<Gfd> gfd_list = algorithm->GfdList();
    ASSERT_EQ(expected_size, gfd_list.size());
}

TYPED_TEST_P(GfdValidationTest, TestExistingMatches) {
    auto graph_path = current_path / "directors.dot";
    auto gfd_path = current_path / "directors_gfd.dot";
    std::vector<std::filesystem::path> gfd_paths = {gfd_path};
    auto algorithm = TestFixture::CreateGfdValidationInstance(graph_path, gfd_paths);
    int expected_size = 0;
    algorithm->Execute();
    std::vector<Gfd> gfd_list = algorithm->GfdList();
    ASSERT_EQ(expected_size, gfd_list.size());
}

REGISTER_TYPED_TEST_SUITE_P(GfdValidationTest, TestTrivially, TestExistingMatches);

using GfdAlgorithms =
        ::testing::Types<algos::NaiveGfdValidation, algos::GfdValidation, algos::EGfdValidation>;

INSTANTIATE_TYPED_TEST_SUITE_P(GfdValidationTest, GfdValidationTest, GfdAlgorithms);

}  // namespace

}  // namespace tests
