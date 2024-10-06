#pragma once

#include <bitset>
#include <string>
#include <unordered_map>
#include <vector>

#include "dc/FastADC/model/predicate.h"

std::vector<std::string> different_column_predicates_expected = {
        "t.A == s.A", "t.A != s.A", "t.A > s.A",  "t.A < s.A",  "t.A >= s.A", "t.A <= s.A",
        "t.A == s.C", "t.A != s.C", "t.A > s.C",  "t.A < s.C",  "t.A >= s.C", "t.A <= s.C",
        "t.A == s.D", "t.A != s.D", "t.A > s.D",  "t.A < s.D",  "t.A >= s.D", "t.A <= s.D",
        "t.B == s.B", "t.B != s.B", "t.B > s.B",  "t.B < s.B",  "t.B >= s.B", "t.B <= s.B",
        "t.C == s.C", "t.C != s.C", "t.C > s.C",  "t.C < s.C",  "t.C >= s.C", "t.C <= s.C",
        "t.C == s.D", "t.C != s.D", "t.C > s.D",  "t.C < s.D",  "t.C >= s.D", "t.C <= s.D",
        "t.D == s.D", "t.D != s.D", "t.D > s.D",  "t.D < s.D",  "t.D >= s.D", "t.D <= s.D",
        "t.E == s.E", "t.E != s.E", "t.E > s.E",  "t.E < s.E",  "t.E >= s.E", "t.E <= s.E",
        "t.F == s.F", "t.F != s.F", "t.G == s.G", "t.G != s.G",
};

std::vector<std::string> num_single_column_predicate_group_expected = {
        "t.A == s.A", "t.A != s.A", "t.A > s.A", "t.A < s.A", "t.A >= s.A", "t.A <= s.A",
        "t.B == s.B", "t.B != s.B", "t.B > s.B", "t.B < s.B", "t.B >= s.B", "t.B <= s.B",
        "t.C == s.C", "t.C != s.C", "t.C > s.C", "t.C < s.C", "t.C >= s.C", "t.C <= s.C",
        "t.D == s.D", "t.D != s.D", "t.D > s.D", "t.D < s.D", "t.D >= s.D", "t.D <= s.D",
        "t.E == s.E", "t.E != s.E", "t.E > s.E", "t.E < s.E", "t.E >= s.E", "t.E <= s.E"};

std::vector<std::string> num_cross_column_predicate_group_expected = {
        "t.A == s.C", "t.A != s.C", "t.A > s.C", "t.A < s.C", "t.A >= s.C", "t.A <= s.C",
        "t.A == s.D", "t.A != s.D", "t.A > s.D", "t.A < s.D", "t.A >= s.D", "t.A <= s.D",
        "t.C == s.D", "t.C != s.D", "t.C > s.D", "t.C < s.D", "t.C >= s.D", "t.C <= s.D"};

std::vector<std::string> str_single_column_predicate_group_expected = {"t.F == s.F", "t.F != s.F",
                                                                       "t.G == s.G", "t.G != s.G"};

std::vector<std::string> str_cross_column_predicate_group_expected = {};

std::vector<std::pair<size_t, size_t>> expected_column_indices = {
        {5, 5}, {6, 6}, {0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {0, 2}, {0, 3}, {2, 3}};

std::vector<std::vector<size_t>> expected_eq_masks = {{0}, {1},  {2},  {4},  {6},
                                                      {8}, {10}, {12}, {14}, {16}};

std::vector<std::vector<size_t>> expected_gt_masks = {{},  {},   {3},  {5},  {7},
                                                      {9}, {11}, {13}, {15}, {17}};

std::vector<std::vector<size_t>> expected_correction_map = {
        {48, 49},         {50, 51},         {0, 1, 3, 4},     {2, 3, 4, 5},     {18, 19, 21, 22},
        {20, 21, 22, 23}, {24, 25, 27, 28}, {26, 27, 28, 29}, {36, 37, 39, 40}, {38, 39, 40, 41},
        {42, 43, 45, 46}, {44, 45, 46, 47}, {6, 7, 9, 10},    {8, 9, 10, 11},   {12, 13, 15, 16},
        {14, 15, 16, 17}, {30, 31, 33, 34}, {32, 33, 34, 35}};

std::bitset<algos::fastadc::kPredicateBits> VectorToBitset(std::vector<size_t> const& positions) {
    std::bitset<algos::fastadc::kPredicateBits> bset;
    for (auto pos : positions) {
        bset.set(pos);
    }
    return bset;
}

std::unordered_map<uint64_t, size_t> expected_clue_set = {
        {2082, 1},   {65570, 1},  {67584, 1},  {67616, 1},  {131104, 1}, {133122, 1}, {133157, 1},
        {148101, 1}, {166152, 1}, {166408, 1}, {168096, 1}, {172448, 1}, {172680, 1}, {172682, 1},
        {172711, 1}, {172712, 1}, {172714, 1}, {174087, 1}, {174728, 1}, {174730, 1}};

std::vector<size_t> expected_cardinality_mask = {1,  3,  5,  7,  9,  11, 13, 15, 17,
                                                 19, 21, 23, 25, 27, 29, 31, 33, 35,
                                                 37, 39, 41, 43, 45, 47, 49, 51};

std::vector<std::vector<size_t>> expected_evidence_set = {
        {1,  3,  5,  7,  9,  11, 13, 15, 17, 19, 20, 22, 25,
         27, 29, 31, 32, 34, 37, 39, 41, 43, 45, 47, 49, 51},
        {0,  4,  5,  7,  8,  10, 13, 14, 16, 19, 20, 22, 25,
         26, 28, 31, 32, 34, 37, 38, 40, 43, 45, 47, 48, 50},
        {1,  3,  5,  7,  9,  11, 13, 15, 17, 19, 20, 22, 25,
         27, 29, 31, 33, 35, 37, 39, 41, 43, 44, 46, 49, 50},
        {1,  3,  5,  7,  9,  11, 13, 15, 17, 19, 21, 23, 25,
         27, 29, 30, 34, 35, 37, 39, 41, 43, 44, 46, 49, 51},
        {1,  2,  4,  7,  9,  11, 13, 14, 16, 19, 21, 23, 25,
         27, 29, 31, 32, 34, 37, 38, 40, 43, 44, 46, 49, 51},
        {1,  2,  4,  7,  8,  10, 13, 14, 16, 19, 21, 23, 25,
         26, 28, 31, 32, 34, 37, 38, 40, 43, 45, 47, 49, 51},
        {1,  3,  5,  6,  10, 11, 13, 14, 16, 19, 20, 22, 25,
         26, 28, 31, 32, 34, 37, 39, 41, 43, 45, 47, 49, 51},
        {1,  3,  5,  7,  9,  11, 13, 15, 17, 19, 20, 22, 25,
         27, 29, 30, 34, 35, 37, 39, 41, 43, 44, 46, 49, 51},
        {1,  2,  4,  7,  8,  10, 13, 14, 16, 19, 20, 22, 25,
         26, 28, 31, 32, 34, 37, 38, 40, 43, 45, 47, 49, 51},
        {1,  2,  4,  7,  9,  11, 13, 14, 16, 19, 21, 23, 25,
         27, 29, 31, 32, 34, 36, 40, 41, 43, 44, 46, 49, 51},
        {1,  2,  4,  7,  8,  10, 13, 14, 16, 19, 21, 23, 25,
         26, 28, 31, 32, 34, 37, 38, 40, 43, 44, 46, 49, 51},
        {0,  4,  5,  7,  9,  11, 13, 15, 17, 19, 20, 22, 25,
         27, 29, 31, 32, 34, 37, 39, 41, 43, 44, 46, 48, 51},
        {0,  4,  5,  7,  8,  10, 13, 14, 16, 19, 21, 23, 25,
         27, 29, 31, 32, 34, 37, 39, 41, 43, 44, 46, 48, 50},
        {1,  3,  5,  7,  9,  11, 13, 15, 17, 19, 21, 23, 25,
         27, 29, 31, 32, 34, 37, 39, 41, 43, 44, 46, 49, 50},
        {1,  2,  4,  7,  8,  10, 13, 14, 16, 19, 20, 22, 25,
         26, 28, 31, 32, 34, 37, 38, 40, 43, 45, 47, 49, 50},
        {1,  3,  5,  7,  8,  10, 13, 14, 16, 19, 20, 22, 25,
         26, 28, 31, 32, 34, 36, 40, 41, 43, 45, 47, 49, 51},
        {0,  4,  5,  7,  9,  11, 12, 16, 17, 19, 21, 23, 25,
         26, 28, 31, 32, 34, 37, 38, 40, 43, 45, 47, 48, 51},
        {1,  2,  4,  7,  8,  10, 13, 14, 16, 19, 21, 23, 25,
         26, 28, 31, 32, 34, 37, 38, 40, 43, 44, 46, 49, 50},
        {1,  3,  5,  7,  9,  11, 13, 15, 17, 19, 20, 22, 25,
         27, 29, 30, 34, 35, 37, 39, 41, 43, 45, 47, 49, 50},
        {1,  2,  4,  7,  8,  10, 13, 14, 16, 19, 21, 23, 25,
         26, 28, 31, 32, 34, 37, 38, 40, 43, 45, 47, 49, 50}};

std::vector<std::vector<size_t>> expected_transformed_evidence_set = {
        {11, 13, 14, 15, 18, 19, 22, 24, 26, 28, 29, 31, 33,
         35, 37, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51},
        {7,  9,  11, 13, 14, 18, 19, 22, 24, 26, 28, 29, 31,
         33, 35, 37, 39, 41, 43, 45, 46, 47, 48, 49, 50, 51},
        {7,  9,  11, 13, 14, 18, 19, 21, 23, 26, 28, 29, 31,
         33, 35, 37, 39, 41, 43, 45, 46, 47, 48, 49, 50, 51},
        {11, 13, 14, 18, 19, 21, 23, 26, 28, 30, 32, 33, 35,
         37, 39, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51},
        {5,  9,  11, 13, 14, 15, 18, 19, 21, 23, 26, 28, 29,
         31, 33, 35, 37, 41, 43, 44, 45, 46, 47, 49, 50, 51},
        {3,  13, 18, 20, 21, 23, 25, 27, 30, 32, 33, 35, 37,
         38, 39, 40, 41, 42, 43, 44, 45, 47, 48, 49, 50, 51},
        {6,  13, 16, 20, 21, 23, 25, 27, 30, 32, 34, 35, 37,
         38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51},
        {7,  9,  11, 13, 14, 15, 18, 19, 21, 23, 26, 28, 30,
         32, 33, 35, 37, 41, 43, 45, 46, 47, 48, 49, 50, 51},
        {8,  10, 15, 16, 17, 20, 21, 23, 25, 27, 30, 32, 34,
         36, 37, 38, 40, 42, 44, 45, 46, 47, 48, 49, 50, 51},
        {8,  10, 15, 16, 18, 20, 22, 24, 26, 28, 29, 31, 35,
         36, 37, 38, 40, 42, 44, 45, 46, 47, 48, 49, 50, 51},
        {8,  10, 11, 14, 18, 19, 21, 23, 26, 28, 29, 31, 33,
         35, 36, 37, 39, 42, 44, 45, 46, 47, 48, 49, 50, 51},
        {4,  8,  10, 14, 17, 19, 22, 24, 25, 27, 30, 32, 33,
         34, 36, 37, 39, 40, 42, 44, 45, 46, 48, 49, 50, 51},
        {12, 15, 16, 17, 20, 21, 23, 25, 27, 30, 32, 34, 36,
         38, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51},
        {12, 15, 16, 17, 20, 22, 24, 25, 27, 29, 31, 34, 36,
         38, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51},
        {12, 15, 16, 17, 20, 22, 24, 25, 27, 30, 32, 34, 36,
         38, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51},
        {12, 17, 19, 22, 24, 26, 28, 29, 31, 33, 34, 36, 38,
         39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51},
        {12, 16, 17, 20, 22, 24, 25, 27, 30, 32, 34, 36, 38,
         39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51},
        {12, 16, 17, 20, 21, 23, 25, 27, 30, 32, 34, 36, 38,
         39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51},
        {6,  12, 19, 22, 24, 26, 28, 29, 31, 33, 34, 35, 36,
         38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51},
        {12, 16, 17, 20, 22, 24, 25, 27, 29, 31, 34, 36, 38,
         39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51},
};

std::vector<std::vector<size_t>> expected_mutex_map = {{0, 21, 22, 23, 24, 49},
                                                       {1, 25, 26, 27, 28, 50},
                                                       {2, 29, 30, 31, 32, 51},
                                                       {3, 16, 19, 20, 33, 46},
                                                       {4, 11, 14, 38, 40, 47},
                                                       {5, 7, 9, 42, 44, 48},
                                                       {6, 17, 18, 34, 35, 45},
                                                       {5, 7, 9, 42, 44, 48},
                                                       {8, 12, 13, 36, 37, 41},
                                                       {5, 7, 9, 42, 44, 48},
                                                       {10, 43},
                                                       {4, 11, 14, 38, 40, 47},
                                                       {8, 12, 13, 36, 37, 41},
                                                       {8, 12, 13, 36, 37, 41},
                                                       {4, 11, 14, 38, 40, 47},
                                                       {15, 39},
                                                       {3, 16, 19, 20, 33, 46},
                                                       {6, 17, 18, 34, 35, 45},
                                                       {6, 17, 18, 34, 35, 45},
                                                       {3, 16, 19, 20, 33, 46},
                                                       {3, 16, 19, 20, 33, 46},
                                                       {0, 21, 22, 23, 24, 49},
                                                       {0, 21, 22, 23, 24, 49},
                                                       {0, 21, 22, 23, 24, 49},
                                                       {0, 21, 22, 23, 24, 49},
                                                       {1, 25, 26, 27, 28, 50},
                                                       {1, 25, 26, 27, 28, 50},
                                                       {1, 25, 26, 27, 28, 50},
                                                       {1, 25, 26, 27, 28, 50},
                                                       {2, 29, 30, 31, 32, 51},
                                                       {2, 29, 30, 31, 32, 51},
                                                       {2, 29, 30, 31, 32, 51},
                                                       {2, 29, 30, 31, 32, 51},
                                                       {3, 16, 19, 20, 33, 46},
                                                       {6, 17, 18, 34, 35, 45},
                                                       {6, 17, 18, 34, 35, 45},
                                                       {8, 12, 13, 36, 37, 41},
                                                       {8, 12, 13, 36, 37, 41},
                                                       {4, 11, 14, 38, 40, 47},
                                                       {15, 39},
                                                       {4, 11, 14, 38, 40, 47},
                                                       {8, 12, 13, 36, 37, 41},
                                                       {5, 7, 9, 42, 44, 48},
                                                       {10, 43},
                                                       {5, 7, 9, 42, 44, 48},
                                                       {6, 17, 18, 34, 35, 45},
                                                       {3, 16, 19, 20, 33, 46},
                                                       {4, 11, 14, 38, 40, 47},
                                                       {5, 7, 9, 42, 44, 48},
                                                       {0, 21, 22, 23, 24, 49},
                                                       {1, 25, 26, 27, 28, 50},
                                                       {2, 29, 30, 31, 32, 51}};

std::vector<std::string> expected_denial_constraints = {
        "¬{ t.A != s.A ∧ t.A != s.C ∧ t.A >= s.D ∧ t.D < s.D }",
        "¬{ t.A != s.A ∧ t.A < s.C ∧ t.A >= s.D ∧ t.E <= s.E }",
        "¬{ t.A != s.A ∧ t.A < s.C ∧ t.C >= s.C }",
        "¬{ t.A != s.A ∧ t.A <= s.C ∧ t.B <= s.B ∧ t.C >= s.C }",
        "¬{ t.A != s.A ∧ t.A <= s.C ∧ t.B <= s.B ∧ t.E <= s.E }",
        "¬{ t.A != s.A ∧ t.A <= s.C ∧ t.C >= s.C ∧ t.D >= s.D }",
        "¬{ t.A != s.A ∧ t.A <= s.C ∧ t.D >= s.D ∧ t.E <= s.E }",
        "¬{ t.A != s.A ∧ t.A <= s.D ∧ t.B <= s.B ∧ t.C != s.D ∧ t.G != s.G }",
        "¬{ t.A != s.A ∧ t.A <= s.D ∧ t.B <= s.B ∧ t.E <= s.E }",
        "¬{ t.A != s.A ∧ t.A <= s.D ∧ t.C != s.D ∧ t.E >= s.E ∧ t.G != s.G }",
        "¬{ t.A != s.A ∧ t.A <= s.D ∧ t.C >= s.C }",
        "¬{ t.A != s.A ∧ t.A <= s.D ∧ t.D >= s.D }",
        "¬{ t.A != s.A ∧ t.A == s.D }",
        "¬{ t.A != s.A ∧ t.A > s.C ∧ t.D < s.D }",
        "¬{ t.A != s.A ∧ t.A >= s.C ∧ t.B <= s.B ∧ t.D <= s.D }",
        "¬{ t.A != s.A ∧ t.A >= s.C ∧ t.C <= s.C }",
        "¬{ t.A != s.A ∧ t.A >= s.C ∧ t.D <= s.D ∧ t.E >= s.E }",
        "¬{ t.A != s.A ∧ t.A >= s.C ∧ t.D <= s.D ∧ t.G == s.G }",
        "¬{ t.A != s.A ∧ t.A >= s.D ∧ t.B <= s.B ∧ t.D < s.D }",
        "¬{ t.A != s.A ∧ t.A >= s.D ∧ t.C <= s.C ∧ t.D < s.D }",
        "¬{ t.A != s.A ∧ t.A >= s.D ∧ t.C <= s.C ∧ t.G == s.G }",
        "¬{ t.A != s.A ∧ t.A >= s.D ∧ t.D < s.D ∧ t.E >= s.E }",
        "¬{ t.A != s.A ∧ t.A >= s.D ∧ t.D <= s.D ∧ t.G == s.G }",
        "¬{ t.A != s.A ∧ t.B >= s.B ∧ t.C != s.D ∧ t.E >= s.E ∧ t.G != s.G }",
        "¬{ t.A != s.A ∧ t.B >= s.B ∧ t.C > s.D ∧ t.E >= s.E }",
        "¬{ t.A != s.A ∧ t.C != s.D ∧ t.D < s.D ∧ t.E >= s.E ∧ t.G != s.G }",
        "¬{ t.A != s.A ∧ t.F == s.F }",
        "¬{ t.A != s.C ∧ t.A >= s.D ∧ t.B >= s.B ∧ t.D < s.D }",
        "¬{ t.A != s.C ∧ t.A >= s.D ∧ t.D < s.D ∧ t.E <= s.E }",
        "¬{ t.A != s.C ∧ t.A >= s.D ∧ t.D < s.D ∧ t.F != s.F }",
        "¬{ t.A != s.C ∧ t.A >= s.D ∧ t.D < s.D ∧ t.G != s.G }",
        "¬{ t.A != s.C ∧ t.C >= s.C ∧ t.D < s.D }",
        "¬{ t.A != s.D ∧ t.B <= s.B ∧ t.C >= s.C ∧ t.F == s.F }",
        "¬{ t.A != s.D ∧ t.B <= s.B ∧ t.D >= s.D ∧ t.F == s.F }",
        "¬{ t.A != s.D ∧ t.B <= s.B ∧ t.E <= s.E ∧ t.F == s.F }",
        "¬{ t.A != s.D ∧ t.B <= s.B ∧ t.F == s.F ∧ t.G != s.G }",
        "¬{ t.A != s.D ∧ t.C >= s.C ∧ t.F == s.F ∧ t.G != s.G }",
        "¬{ t.A != s.D ∧ t.D >= s.D ∧ t.F == s.F ∧ t.G != s.G }",
        "¬{ t.A != s.D ∧ t.E <= s.E ∧ t.F == s.F ∧ t.G != s.G }",
        "¬{ t.A < s.A ∧ t.A != s.C ∧ t.A >= s.D ∧ t.D != s.D }",
        "¬{ t.A < s.A ∧ t.A != s.C ∧ t.C >= s.C ∧ t.D != s.D }",
        "¬{ t.A < s.A ∧ t.A < s.C ∧ t.A >= s.D }",
        "¬{ t.A < s.A ∧ t.A <= s.C ∧ t.D >= s.D }",
        "¬{ t.A < s.A ∧ t.A > s.C ∧ t.D != s.D }",
        "¬{ t.A < s.A ∧ t.A >= s.C ∧ t.B <= s.B }",
        "¬{ t.A < s.A ∧ t.A >= s.C ∧ t.E >= s.E }",
        "¬{ t.A < s.A ∧ t.A >= s.C ∧ t.G == s.G }",
        "¬{ t.A < s.A ∧ t.A >= s.D ∧ t.B <= s.B }",
        "¬{ t.A < s.A ∧ t.A >= s.D ∧ t.C <= s.C }",
        "¬{ t.A < s.A ∧ t.A >= s.D ∧ t.E >= s.E }",
        "¬{ t.A < s.A ∧ t.A >= s.D ∧ t.G == s.G }",
        "¬{ t.A < s.A ∧ t.B <= s.B ∧ t.C != s.D ∧ t.G != s.G }",
        "¬{ t.A < s.A ∧ t.B <= s.B ∧ t.C >= s.C }",
        "¬{ t.A < s.A ∧ t.B <= s.B ∧ t.D >= s.D }",
        "¬{ t.A < s.A ∧ t.B <= s.B ∧ t.E <= s.E }",
        "¬{ t.A < s.A ∧ t.B >= s.B ∧ t.C > s.D ∧ t.G == s.G }",
        "¬{ t.A < s.A ∧ t.C != s.D ∧ t.E <= s.E ∧ t.G == s.G }",
        "¬{ t.A < s.A ∧ t.C != s.D ∧ t.E >= s.E ∧ t.G != s.G }",
        "¬{ t.A < s.A ∧ t.C >= s.C ∧ t.G == s.G }",
        "¬{ t.A < s.A ∧ t.D > s.D }",
        "¬{ t.A < s.A ∧ t.D >= s.D ∧ t.G == s.G }",
        "¬{ t.A < s.C ∧ t.A != s.D ∧ t.C >= s.C }",
        "¬{ t.A < s.C ∧ t.A > s.D ∧ t.E <= s.E }",
        "¬{ t.A < s.C ∧ t.A >= s.D ∧ t.B >= s.B }",
        "¬{ t.A < s.C ∧ t.A >= s.D ∧ t.D < s.D }",
        "¬{ t.A < s.C ∧ t.A >= s.D ∧ t.D <= s.D ∧ t.E <= s.E }",
        "¬{ t.A < s.C ∧ t.A >= s.D ∧ t.E <= s.E ∧ t.F != s.F }",
        "¬{ t.A < s.C ∧ t.B >= s.B ∧ t.C >= s.C }",
        "¬{ t.A < s.C ∧ t.C >= s.C ∧ t.D <= s.D }",
        "¬{ t.A < s.C ∧ t.C >= s.C ∧ t.F != s.F }",
        "¬{ t.A < s.D ∧ t.B <= s.B ∧ t.C != s.D ∧ t.G != s.G }",
        "¬{ t.A < s.D ∧ t.B <= s.B ∧ t.E <= s.E }",
        "¬{ t.A < s.D ∧ t.B <= s.B ∧ t.F == s.F }",
        "¬{ t.A < s.D ∧ t.C >= s.C }",
        "¬{ t.A < s.D ∧ t.D >= s.D }",
        "¬{ t.A < s.D ∧ t.E <= s.E ∧ t.F == s.F }",
        "¬{ t.A <= s.A ∧ t.A != s.C ∧ t.A != s.D ∧ t.C >= s.C ∧ t.D != s.D ∧ t.G != s.G }",
        "¬{ t.A <= s.A ∧ t.A != s.C ∧ t.A > s.D ∧ t.D != s.D ∧ t.G != s.G }",
        "¬{ t.A <= s.A ∧ t.A != s.C ∧ t.A >= s.D ∧ t.B >= s.B ∧ t.D != s.D ∧ t.G != s.G }",
        "¬{ t.A <= s.A ∧ t.A != s.C ∧ t.A >= s.D ∧ t.D != s.D ∧ t.F != s.F }",
        "¬{ t.A <= s.A ∧ t.A != s.C ∧ t.B >= s.B ∧ t.C >= s.C ∧ t.D != s.D ∧ t.G != s.G }",
        "¬{ t.A <= s.A ∧ t.A != s.C ∧ t.C >= s.C ∧ t.D != s.D ∧ t.F != s.F }",
        "¬{ t.A <= s.A ∧ t.A != s.D ∧ t.B <= s.B ∧ t.C != s.D ∧ t.G != s.G }",
        "¬{ t.A <= s.A ∧ t.A != s.D ∧ t.B <= s.B ∧ t.C >= s.C }",
        "¬{ t.A <= s.A ∧ t.A != s.D ∧ t.B <= s.B ∧ t.D >= s.D }",
        "¬{ t.A <= s.A ∧ t.A != s.D ∧ t.B <= s.B ∧ t.E <= s.E }",
        "¬{ t.A <= s.A ∧ t.A != s.D ∧ t.D > s.D ∧ t.G != s.G }",
        "¬{ t.A <= s.A ∧ t.A < s.C ∧ t.A > s.D }",
        "¬{ t.A <= s.A ∧ t.A < s.C ∧ t.A >= s.D ∧ t.D <= s.D }",
        "¬{ t.A <= s.A ∧ t.A < s.C ∧ t.A >= s.D ∧ t.F != s.F }",
        "¬{ t.A <= s.A ∧ t.A <= s.C ∧ t.A != s.D ∧ t.D >= s.D }",
        "¬{ t.A <= s.A ∧ t.A <= s.C ∧ t.A > s.D ∧ t.B <= s.B }",
        "¬{ t.A <= s.A ∧ t.A <= s.C ∧ t.A >= s.D ∧ t.B <= s.B ∧ t.D <= s.D }",
        "¬{ t.A <= s.A ∧ t.A <= s.C ∧ t.A >= s.D ∧ t.C <= s.C }",
        "¬{ t.A <= s.A ∧ t.A <= s.C ∧ t.A >= s.D ∧ t.E >= s.E }",
        "¬{ t.A <= s.A ∧ t.A <= s.C ∧ t.D == s.D }",
        "¬{ t.A <= s.A ∧ t.A <= s.C ∧ t.D >= s.D ∧ t.F != s.F }",
        "¬{ t.A <= s.A ∧ t.A > s.C ∧ t.D != s.D ∧ t.F != s.F }",
        "¬{ t.A <= s.A ∧ t.A > s.C ∧ t.D != s.D ∧ t.G != s.G }",
        "¬{ t.A <= s.A ∧ t.A > s.D ∧ t.B <= s.B ∧ t.G != s.G }",
        "¬{ t.A <= s.A ∧ t.A >= s.C ∧ t.B <= s.B ∧ t.C >= s.C }",
        "¬{ t.A <= s.A ∧ t.A >= s.C ∧ t.B <= s.B ∧ t.D >= s.D }",
        "¬{ t.A <= s.A ∧ t.A >= s.C ∧ t.B <= s.B ∧ t.E <= s.E }",
        "¬{ t.A <= s.A ∧ t.A >= s.C ∧ t.B <= s.B ∧ t.F != s.F }",
        "¬{ t.A <= s.A ∧ t.A >= s.C ∧ t.B <= s.B ∧ t.G != s.G }",
        "¬{ t.A <= s.A ∧ t.A >= s.C ∧ t.D > s.D ∧ t.G != s.G }",
        "¬{ t.A <= s.A ∧ t.A >= s.C ∧ t.E >= s.E ∧ t.F != s.F }",
        "¬{ t.A <= s.A ∧ t.A >= s.C ∧ t.E >= s.E ∧ t.G != s.G }",
        "¬{ t.A <= s.A ∧ t.A >= s.C ∧ t.F != s.F ∧ t.G == s.G }",
        "¬{ t.A <= s.A ∧ t.A >= s.D ∧ t.B <= s.B ∧ t.D <= s.D ∧ t.G != s.G }",
        "¬{ t.A <= s.A ∧ t.A >= s.D ∧ t.B <= s.B ∧ t.F != s.F }",
        "¬{ t.A <= s.A ∧ t.A >= s.D ∧ t.C <= s.C ∧ t.F != s.F }",
        "¬{ t.A <= s.A ∧ t.A >= s.D ∧ t.C <= s.C ∧ t.G != s.G }",
        "¬{ t.A <= s.A ∧ t.A >= s.D ∧ t.E >= s.E ∧ t.F != s.F }",
        "¬{ t.A <= s.A ∧ t.A >= s.D ∧ t.E >= s.E ∧ t.G != s.G }",
        "¬{ t.A <= s.A ∧ t.A >= s.D ∧ t.F != s.F ∧ t.G == s.G }",
        "¬{ t.A <= s.A ∧ t.B <= s.B ∧ t.C != s.D ∧ t.D <= s.D ∧ t.G != s.G }",
        "¬{ t.A <= s.A ∧ t.B <= s.B ∧ t.C != s.D ∧ t.E >= s.E ∧ t.G != s.G }",
        "¬{ t.A <= s.A ∧ t.B <= s.B ∧ t.C != s.D ∧ t.F != s.F ∧ t.G != s.G }",
        "¬{ t.A <= s.A ∧ t.B <= s.B ∧ t.C <= s.C ∧ t.C != s.D ∧ t.G != s.G }",
        "¬{ t.A <= s.A ∧ t.B <= s.B ∧ t.C >= s.C ∧ t.F != s.F }",
        "¬{ t.A <= s.A ∧ t.B <= s.B ∧ t.C >= s.C ∧ t.G == s.G }",
        "¬{ t.A <= s.A ∧ t.B <= s.B ∧ t.D == s.D }",
        "¬{ t.A <= s.A ∧ t.B <= s.B ∧ t.D >= s.D ∧ t.F != s.F }",
        "¬{ t.A <= s.A ∧ t.B <= s.B ∧ t.D >= s.D ∧ t.G == s.G }",
        "¬{ t.A <= s.A ∧ t.B <= s.B ∧ t.E <= s.E ∧ t.F != s.F }",
        "¬{ t.A <= s.A ∧ t.B <= s.B ∧ t.E <= s.E ∧ t.G == s.G }",
        "¬{ t.A <= s.A ∧ t.B >= s.B ∧ t.C > s.D ∧ t.F != s.F ∧ t.G == s.G }",
        "¬{ t.A <= s.A ∧ t.B >= s.B ∧ t.D > s.D ∧ t.G != s.G }",
        "¬{ t.A <= s.A ∧ t.C != s.D ∧ t.E <= s.E ∧ t.F != s.F ∧ t.G == s.G }",
        "¬{ t.A <= s.A ∧ t.C != s.D ∧ t.E >= s.E ∧ t.F != s.F ∧ t.G != s.G }",
        "¬{ t.A <= s.A ∧ t.C <= s.C ∧ t.D >= s.D }",
        "¬{ t.A <= s.A ∧ t.C >= s.C ∧ t.E >= s.E }",
        "¬{ t.A <= s.A ∧ t.C >= s.C ∧ t.F != s.F ∧ t.G == s.G }",
        "¬{ t.A <= s.A ∧ t.D > s.D ∧ t.F != s.F }",
        "¬{ t.A <= s.A ∧ t.D >= s.D ∧ t.E >= s.E }",
        "¬{ t.A <= s.A ∧ t.D >= s.D ∧ t.F != s.F ∧ t.G == s.G }",
        "¬{ t.A <= s.C ∧ t.A != s.D ∧ t.B <= s.B ∧ t.C >= s.C }",
        "¬{ t.A <= s.C ∧ t.A != s.D ∧ t.B <= s.B ∧ t.E <= s.E }",
        "¬{ t.A <= s.C ∧ t.A != s.D ∧ t.B <= s.B ∧ t.F == s.F }",
        "¬{ t.A <= s.C ∧ t.A != s.D ∧ t.C >= s.C ∧ t.D >= s.D }",
        "¬{ t.A <= s.C ∧ t.A != s.D ∧ t.C >= s.C ∧ t.F == s.F }",
        "¬{ t.A <= s.C ∧ t.A != s.D ∧ t.D >= s.D ∧ t.E <= s.E }",
        "¬{ t.A <= s.C ∧ t.A != s.D ∧ t.D >= s.D ∧ t.F == s.F }",
        "¬{ t.A <= s.C ∧ t.A != s.D ∧ t.E <= s.E ∧ t.F == s.F }",
        "¬{ t.A <= s.C ∧ t.A > s.D ∧ t.F == s.F }",
        "¬{ t.A <= s.C ∧ t.A >= s.D ∧ t.B <= s.B ∧ t.D < s.D }",
        "¬{ t.A <= s.C ∧ t.A >= s.D ∧ t.B >= s.B ∧ t.F == s.F }",
        "¬{ t.A <= s.C ∧ t.A >= s.D ∧ t.C <= s.C ∧ t.D < s.D }",
        "¬{ t.A <= s.C ∧ t.A >= s.D ∧ t.C <= s.C ∧ t.F == s.F }",
        "¬{ t.A <= s.C ∧ t.A >= s.D ∧ t.D < s.D ∧ t.E >= s.E }",
        "¬{ t.A <= s.C ∧ t.A >= s.D ∧ t.D <= s.D ∧ t.F == s.F }",
        "¬{ t.A <= s.C ∧ t.A >= s.D ∧ t.E >= s.E ∧ t.F == s.F }",
        "¬{ t.A <= s.C ∧ t.A >= s.D ∧ t.G == s.G }",
        "¬{ t.A <= s.C ∧ t.B <= s.B ∧ t.C <= s.C ∧ t.F == s.F }",
        "¬{ t.A <= s.C ∧ t.B <= s.B ∧ t.C >= s.C ∧ t.F != s.F }",
        "¬{ t.A <= s.C ∧ t.B <= s.B ∧ t.D <= s.D ∧ t.F == s.F }",
        "¬{ t.A <= s.C ∧ t.B <= s.B ∧ t.E <= s.E ∧ t.F != s.F }",
        "¬{ t.A <= s.C ∧ t.B <= s.B ∧ t.E <= s.E ∧ t.G == s.G }",
        "¬{ t.A <= s.C ∧ t.B <= s.B ∧ t.E >= s.E ∧ t.F == s.F }",
        "¬{ t.A <= s.C ∧ t.B >= s.B ∧ t.C > s.D ∧ t.G == s.G }",
        "¬{ t.A <= s.C ∧ t.B >= s.B ∧ t.C >= s.C ∧ t.F == s.F }",
        "¬{ t.A <= s.C ∧ t.B >= s.B ∧ t.D >= s.D }",
        "¬{ t.A <= s.C ∧ t.B >= s.B ∧ t.E <= s.E ∧ t.F == s.F }",
        "¬{ t.A <= s.C ∧ t.C != s.D ∧ t.E <= s.E ∧ t.G == s.G }",
        "¬{ t.A <= s.C ∧ t.C >= s.C ∧ t.D == s.D }",
        "¬{ t.A <= s.C ∧ t.C >= s.C ∧ t.D >= s.D ∧ t.F != s.F }",
        "¬{ t.A <= s.C ∧ t.C >= s.C ∧ t.E >= s.E }",
        "¬{ t.A <= s.C ∧ t.C >= s.C ∧ t.G == s.G }",
        "¬{ t.A <= s.C ∧ t.D == s.D ∧ t.E <= s.E }",
        "¬{ t.A <= s.C ∧ t.D >= s.D ∧ t.E <= s.E ∧ t.F != s.F }",
        "¬{ t.A <= s.C ∧ t.D >= s.D ∧ t.G == s.G }",
        "¬{ t.A <= s.C ∧ t.F == s.F ∧ t.G == s.G }",
        "¬{ t.A <= s.D ∧ t.B <= s.B ∧ t.C != s.D ∧ t.D <= s.D ∧ t.G != s.G }",
        "¬{ t.A <= s.D ∧ t.B <= s.B ∧ t.C != s.D ∧ t.E >= s.E ∧ t.G != s.G }",
        "¬{ t.A <= s.D ∧ t.B <= s.B ∧ t.C != s.D ∧ t.F != s.F ∧ t.G != s.G }",
        "¬{ t.A <= s.D ∧ t.B <= s.B ∧ t.C <= s.C ∧ t.C != s.D ∧ t.G != s.G }",
        "¬{ t.A <= s.D ∧ t.B <= s.B ∧ t.C <= s.C ∧ t.F == s.F }",
        "¬{ t.A <= s.D ∧ t.B <= s.B ∧ t.D <= s.D ∧ t.F == s.F }",
        "¬{ t.A <= s.D ∧ t.B <= s.B ∧ t.E <= s.E ∧ t.F != s.F }",
        "¬{ t.A <= s.D ∧ t.B <= s.B ∧ t.E <= s.E ∧ t.G == s.G }",
        "¬{ t.A <= s.D ∧ t.B <= s.B ∧ t.E >= s.E ∧ t.F == s.F }",
        "¬{ t.A <= s.D ∧ t.B >= s.B ∧ t.C > s.D ∧ t.G == s.G }",
        "¬{ t.A <= s.D ∧ t.B >= s.B ∧ t.C >= s.C }",
        "¬{ t.A <= s.D ∧ t.B >= s.B ∧ t.D >= s.D }",
        "¬{ t.A <= s.D ∧ t.B >= s.B ∧ t.E <= s.E ∧ t.F == s.F }",
        "¬{ t.A <= s.D ∧ t.C != s.D ∧ t.E <= s.E ∧ t.G == s.G }",
        "¬{ t.A <= s.D ∧ t.C != s.D ∧ t.E >= s.E ∧ t.F != s.F ∧ t.G != s.G }",
        "¬{ t.A <= s.D ∧ t.C <= s.C ∧ t.D >= s.D }",
        "¬{ t.A <= s.D ∧ t.C >= s.C ∧ t.D <= s.D }",
        "¬{ t.A <= s.D ∧ t.C >= s.C ∧ t.E >= s.E }",
        "¬{ t.A <= s.D ∧ t.C >= s.C ∧ t.F != s.F }",
        "¬{ t.A <= s.D ∧ t.C >= s.C ∧ t.G == s.G }",
        "¬{ t.A <= s.D ∧ t.D == s.D }",
        "¬{ t.A <= s.D ∧ t.D >= s.D ∧ t.E >= s.E }",
        "¬{ t.A <= s.D ∧ t.D >= s.D ∧ t.F != s.F }",
        "¬{ t.A <= s.D ∧ t.D >= s.D ∧ t.G == s.G }",
        "¬{ t.A <= s.D ∧ t.F == s.F ∧ t.G == s.G }",
        "¬{ t.A == s.A ∧ t.A != s.D ∧ t.B <= s.B ∧ t.G != s.G }",
        "¬{ t.A == s.A ∧ t.A != s.D ∧ t.C >= s.C ∧ t.G != s.G }",
        "¬{ t.A == s.A ∧ t.A != s.D ∧ t.D >= s.D ∧ t.G != s.G }",
        "¬{ t.A == s.A ∧ t.A != s.D ∧ t.E <= s.E ∧ t.G != s.G }",
        "¬{ t.A == s.A ∧ t.A <= s.C ∧ t.A != s.D ∧ t.B <= s.B }",
        "¬{ t.A == s.A ∧ t.A <= s.C ∧ t.A > s.D }",
        "¬{ t.A == s.A ∧ t.A <= s.C ∧ t.A >= s.D ∧ t.D <= s.D }",
        "¬{ t.A == s.A ∧ t.A <= s.C ∧ t.B <= s.B ∧ t.C <= s.C }",
        "¬{ t.A == s.A ∧ t.A <= s.C ∧ t.B <= s.B ∧ t.D <= s.D }",
        "¬{ t.A == s.A ∧ t.A <= s.C ∧ t.B <= s.B ∧ t.E >= s.E }",
        "¬{ t.A == s.A ∧ t.A > s.D ∧ t.G != s.G }",
        "¬{ t.A == s.A ∧ t.A >= s.C ∧ t.G != s.G }",
        "¬{ t.A == s.A ∧ t.A >= s.D ∧ t.B >= s.B ∧ t.G != s.G }",
        "¬{ t.A == s.A ∧ t.A >= s.D ∧ t.D <= s.D ∧ t.G != s.G }",
        "¬{ t.A == s.A ∧ t.B <= s.B ∧ t.C <= s.C ∧ t.G != s.G }",
        "¬{ t.A == s.A ∧ t.B <= s.B ∧ t.D <= s.D ∧ t.G != s.G }",
        "¬{ t.A == s.A ∧ t.B <= s.B ∧ t.E >= s.E ∧ t.G != s.G }",
        "¬{ t.A == s.A ∧ t.D == s.D }",
        "¬{ t.A == s.A ∧ t.F != s.F }",
        "¬{ t.A == s.C ∧ t.B <= s.B }",
        "¬{ t.A == s.C ∧ t.C <= s.C }",
        "¬{ t.A == s.C ∧ t.D >= s.D }",
        "¬{ t.A == s.C ∧ t.E >= s.E }",
        "¬{ t.A == s.C ∧ t.F == s.F }",
        "¬{ t.A == s.C ∧ t.G == s.G }",
        "¬{ t.A == s.D ∧ t.B >= s.B }",
        "¬{ t.A == s.D ∧ t.C <= s.C }",
        "¬{ t.A == s.D ∧ t.D <= s.D }",
        "¬{ t.A == s.D ∧ t.E >= s.E }",
        "¬{ t.A == s.D ∧ t.F != s.F }",
        "¬{ t.A == s.D ∧ t.G == s.G }",
        "¬{ t.A > s.A ∧ t.A <= s.C ∧ t.B >= s.B }",
        "¬{ t.A > s.A ∧ t.A <= s.C ∧ t.C >= s.C }",
        "¬{ t.A > s.A ∧ t.A <= s.C ∧ t.E <= s.E }",
        "¬{ t.A > s.A ∧ t.A <= s.D }",
        "¬{ t.A > s.A ∧ t.A >= s.C ∧ t.D <= s.D }",
        "¬{ t.A > s.C ∧ t.B >= s.B ∧ t.D < s.D }",
        "¬{ t.A > s.C ∧ t.D < s.D ∧ t.E <= s.E }",
        "¬{ t.A > s.C ∧ t.D < s.D ∧ t.F != s.F }",
        "¬{ t.A > s.C ∧ t.D < s.D ∧ t.G != s.G }",
        "¬{ t.A > s.D ∧ t.F == s.F ∧ t.G != s.G }",
        "¬{ t.A >= s.A ∧ t.A < s.D ∧ t.B <= s.B }",
        "¬{ t.A >= s.A ∧ t.A < s.D ∧ t.E <= s.E }",
        "¬{ t.A >= s.A ∧ t.A <= s.C ∧ t.A != s.D ∧ t.C >= s.C }",
        "¬{ t.A >= s.A ∧ t.A <= s.C ∧ t.A != s.D ∧ t.E <= s.E }",
        "¬{ t.A >= s.A ∧ t.A <= s.C ∧ t.A >= s.D ∧ t.B >= s.B }",
        "¬{ t.A >= s.A ∧ t.A <= s.C ∧ t.A >= s.D ∧ t.D < s.D }",
        "¬{ t.A >= s.A ∧ t.A <= s.C ∧ t.B <= s.B ∧ t.D < s.D }",
        "¬{ t.A >= s.A ∧ t.A <= s.C ∧ t.B >= s.B ∧ t.C >= s.C }",
        "¬{ t.A >= s.A ∧ t.A <= s.C ∧ t.B >= s.B ∧ t.E <= s.E }",
        "¬{ t.A >= s.A ∧ t.A <= s.C ∧ t.B >= s.B ∧ t.F != s.F }",
        "¬{ t.A >= s.A ∧ t.A <= s.C ∧ t.C >= s.C ∧ t.F != s.F }",
        "¬{ t.A >= s.A ∧ t.A <= s.C ∧ t.E <= s.E ∧ t.F != s.F }",
        "¬{ t.A >= s.A ∧ t.A <= s.C ∧ t.G == s.G }",
        "¬{ t.A >= s.A ∧ t.A <= s.D ∧ t.B <= s.B ∧ t.C <= s.C }",
        "¬{ t.A >= s.A ∧ t.A <= s.D ∧ t.B <= s.B ∧ t.D <= s.D }",
        "¬{ t.A >= s.A ∧ t.A <= s.D ∧ t.B <= s.B ∧ t.E >= s.E }",
        "¬{ t.A >= s.A ∧ t.A <= s.D ∧ t.B >= s.B ∧ t.E <= s.E }",
        "¬{ t.A >= s.A ∧ t.A <= s.D ∧ t.F != s.F }",
        "¬{ t.A >= s.A ∧ t.A <= s.D ∧ t.G == s.G }",
        "¬{ t.A >= s.A ∧ t.A == s.C }",
        "¬{ t.A >= s.A ∧ t.A >= s.C ∧ t.B >= s.B ∧ t.D <= s.D }",
        "¬{ t.A >= s.A ∧ t.A >= s.C ∧ t.D <= s.D ∧ t.F != s.F }",
        "¬{ t.A >= s.A ∧ t.A >= s.C ∧ t.D <= s.D ∧ t.G != s.G }",
        "¬{ t.A >= s.A ∧ t.A >= s.C ∧ t.D == s.D }",
        "¬{ t.A >= s.A ∧ t.A >= s.D ∧ t.B >= s.B ∧ t.D <= s.D }",
        "¬{ t.A >= s.A ∧ t.A >= s.D ∧ t.D < s.D ∧ t.G != s.G }",
        "¬{ t.A >= s.A ∧ t.C <= s.D }",
        "¬{ t.A >= s.C ∧ t.A <= s.D }",
        "¬{ t.A >= s.C ∧ t.B <= s.B ∧ t.C >= s.C ∧ t.F == s.F }",
        "¬{ t.A >= s.C ∧ t.B <= s.B ∧ t.D <= s.D ∧ t.F != s.F }",
        "¬{ t.A >= s.C ∧ t.B <= s.B ∧ t.D <= s.D ∧ t.G != s.G }",
        "¬{ t.A >= s.C ∧ t.B <= s.B ∧ t.D == s.D }",
        "¬{ t.A >= s.C ∧ t.B <= s.B ∧ t.D >= s.D ∧ t.F == s.F }",
        "¬{ t.A >= s.C ∧ t.B <= s.B ∧ t.E <= s.E ∧ t.F == s.F }",
        "¬{ t.A >= s.C ∧ t.B >= s.B ∧ t.C <= s.C }",
        "¬{ t.A >= s.C ∧ t.B >= s.B ∧ t.D <= s.D ∧ t.F == s.F }",
        "¬{ t.A >= s.C ∧ t.B >= s.B ∧ t.D <= s.D ∧ t.G == s.G }",
        "¬{ t.A >= s.C ∧ t.B >= s.B ∧ t.E >= s.E }",
        "¬{ t.A >= s.C ∧ t.C <= s.C ∧ t.D >= s.D }",
        "¬{ t.A >= s.C ∧ t.C <= s.C ∧ t.E <= s.E }",
        "¬{ t.A >= s.C ∧ t.C <= s.C ∧ t.F != s.F }",
        "¬{ t.A >= s.C ∧ t.C <= s.C ∧ t.G != s.G }",
        "¬{ t.A >= s.C ∧ t.C <= s.D }",
        "¬{ t.A >= s.C ∧ t.D <= s.D ∧ t.E <= s.E ∧ t.G == s.G }",
        "¬{ t.A >= s.C ∧ t.D <= s.D ∧ t.E >= s.E ∧ t.F != s.F }",
        "¬{ t.A >= s.C ∧ t.D <= s.D ∧ t.E >= s.E ∧ t.G != s.G }",
        "¬{ t.A >= s.C ∧ t.D <= s.D ∧ t.F != s.F ∧ t.G == s.G }",
        "¬{ t.A >= s.C ∧ t.D == s.D ∧ t.E >= s.E }",
        "¬{ t.A >= s.C ∧ t.F == s.F ∧ t.G != s.G }",
        "¬{ t.A >= s.D ∧ t.B <= s.B ∧ t.D < s.D ∧ t.F != s.F }",
        "¬{ t.A >= s.D ∧ t.B <= s.B ∧ t.D < s.D ∧ t.G != s.G }",
        "¬{ t.A >= s.D ∧ t.B >= s.B ∧ t.C <= s.C }",
        "¬{ t.A >= s.D ∧ t.B >= s.B ∧ t.D <= s.D ∧ t.F == s.F }",
        "¬{ t.A >= s.D ∧ t.B >= s.B ∧ t.D <= s.D ∧ t.G == s.G }",
        "¬{ t.A >= s.D ∧ t.B >= s.B ∧ t.E >= s.E }",
        "¬{ t.A >= s.D ∧ t.B >= s.B ∧ t.F == s.F ∧ t.G != s.G }",
        "¬{ t.A >= s.D ∧ t.C <= s.C ∧ t.D < s.D ∧ t.F != s.F }",
        "¬{ t.A >= s.D ∧ t.C <= s.C ∧ t.D < s.D ∧ t.G != s.G }",
        "¬{ t.A >= s.D ∧ t.C <= s.C ∧ t.E <= s.E }",
        "¬{ t.A >= s.D ∧ t.C <= s.C ∧ t.F != s.F ∧ t.G == s.G }",
        "¬{ t.A >= s.D ∧ t.C <= s.C ∧ t.F == s.F ∧ t.G != s.G }",
        "¬{ t.A >= s.D ∧ t.C <= s.D }",
        "¬{ t.A >= s.D ∧ t.D < s.D ∧ t.E >= s.E ∧ t.F != s.F }",
        "¬{ t.A >= s.D ∧ t.D < s.D ∧ t.E >= s.E ∧ t.G != s.G }",
        "¬{ t.A >= s.D ∧ t.D <= s.D ∧ t.E <= s.E ∧ t.G == s.G }",
        "¬{ t.A >= s.D ∧ t.D <= s.D ∧ t.F != s.F ∧ t.G == s.G }",
        "¬{ t.A >= s.D ∧ t.D <= s.D ∧ t.F == s.F ∧ t.G != s.G }",
        "¬{ t.A >= s.D ∧ t.E >= s.E ∧ t.F == s.F ∧ t.G != s.G }",
        "¬{ t.B <= s.B ∧ t.C != s.D ∧ t.D < s.D ∧ t.G != s.G }",
        "¬{ t.B <= s.B ∧ t.C < s.D }",
        "¬{ t.B <= s.B ∧ t.C <= s.C ∧ t.E <= s.E }",
        "¬{ t.B <= s.B ∧ t.C <= s.C ∧ t.F == s.F ∧ t.G != s.G }",
        "¬{ t.B <= s.B ∧ t.C <= s.D ∧ t.E <= s.E }",
        "¬{ t.B <= s.B ∧ t.C <= s.D ∧ t.G == s.G }",
        "¬{ t.B <= s.B ∧ t.C >= s.C ∧ t.D <= s.D }",
        "¬{ t.B <= s.B ∧ t.C >= s.C ∧ t.F == s.F ∧ t.G == s.G }",
        "¬{ t.B <= s.B ∧ t.D <= s.D ∧ t.E <= s.E }",
        "¬{ t.B <= s.B ∧ t.D <= s.D ∧ t.F == s.F ∧ t.G != s.G }",
        "¬{ t.B <= s.B ∧ t.D >= s.D ∧ t.F == s.F ∧ t.G == s.G }",
        "¬{ t.B <= s.B ∧ t.E <= s.E ∧ t.F == s.F ∧ t.G == s.G }",
        "¬{ t.B <= s.B ∧ t.E >= s.E ∧ t.F == s.F ∧ t.G != s.G }",
        "¬{ t.B == s.B }",
        "¬{ t.B >= s.B ∧ t.C != s.D ∧ t.E >= s.E ∧ t.F != s.F ∧ t.G != s.G }",
        "¬{ t.B >= s.B ∧ t.C <= s.C ∧ t.C > s.D ∧ t.G == s.G }",
        "¬{ t.B >= s.B ∧ t.C > s.D ∧ t.D <= s.D ∧ t.G == s.G }",
        "¬{ t.B >= s.B ∧ t.C > s.D ∧ t.E >= s.E ∧ t.F != s.F }",
        "¬{ t.B >= s.B ∧ t.C >= s.D ∧ t.E >= s.E ∧ t.G == s.G }",
        "¬{ t.C != s.D ∧ t.D < s.D ∧ t.E >= s.E ∧ t.F != s.F ∧ t.G != s.G }",
        "¬{ t.C != s.D ∧ t.D <= s.D ∧ t.E <= s.E ∧ t.G == s.G }",
        "¬{ t.C < s.D ∧ t.E <= s.E }",
        "¬{ t.C < s.D ∧ t.G != s.G }",
        "¬{ t.C <= s.C ∧ t.C != s.D ∧ t.E <= s.E ∧ t.G == s.G }",
        "¬{ t.C <= s.C ∧ t.D >= s.D ∧ t.E <= s.E }",
        "¬{ t.C <= s.C ∧ t.D >= s.D ∧ t.F == s.F }",
        "¬{ t.C <= s.C ∧ t.D >= s.D ∧ t.G == s.G }",
        "¬{ t.C <= s.C ∧ t.E <= s.E ∧ t.F == s.F }",
        "¬{ t.C <= s.D ∧ t.D >= s.D }",
        "¬{ t.C <= s.D ∧ t.E <= s.E ∧ t.G != s.G }",
        "¬{ t.C <= s.D ∧ t.F == s.F }",
        "¬{ t.C == s.C }",
        "¬{ t.C == s.D ∧ t.E >= s.E ∧ t.G == s.G }",
        "¬{ t.C >= s.C ∧ t.C <= s.D }",
        "¬{ t.D <= s.D ∧ t.E <= s.E ∧ t.F == s.F }",
        "¬{ t.D == s.D ∧ t.F == s.F }",
        "¬{ t.D == s.D ∧ t.G == s.G }",
        "¬{ t.E == s.E }"};
