#include "algorithms/md/hymd/preprocessing/column_matches/jaccard.h"

#include <iterator>       // for istream_iterator, operator==
#include <sstream>        // for basic_istringstream, istringstream
#include <string>         // for hash, string, operator==
#include <unordered_set>  // for unordered_set

namespace algos::hymd::preprocessing::column_matches::similarity_measures {
double StringJaccardIndex(std::string const& s1, std::string const& s2) {
    std::istringstream iss1(s1), iss2(s2);
    std::unordered_set<std::string> set1{std::istream_iterator<std::string>{iss1},
                                         std::istream_iterator<std::string>{}};
    std::unordered_set<std::string> set2{std::istream_iterator<std::string>{iss2},
                                         std::istream_iterator<std::string>{}};

    return JaccardIndex(set1, set2);
}
}  // namespace algos::hymd::preprocessing::column_matches::similarity_measures
