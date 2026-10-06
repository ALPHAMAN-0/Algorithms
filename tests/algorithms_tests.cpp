// Tests for the programs in "SUM Algorithms" and "Problem Set 1".
//
// Every program is a stand-alone .cpp file with its own main(), so each one is
// included here unchanged inside its own namespace, with its main() renamed.
// Functions are called directly; the interactive programs are also run through
// their renamed main() with cin / cout redirected to strings.
//
// Run from the repository root:
//   g++ -std=c++17 tests/algorithms_tests.cpp -o tests/algorithms_tests.out && ./tests/algorithms_tests.out
//
// Every standard header used by the programs has to be included here first,
// so that their own #include lines do nothing once inside a namespace.

#include <algorithm>
#include <climits>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#define main programMain

namespace kadans {
#include "../SUM Algorithms/Kadans.cpp"
}
namespace prefixSum {
#include "../SUM Algorithms/prefix_Sum.cpp"
}
namespace suffixSum {
#include "../SUM Algorithms/Suffix_sum.cpp"
}
namespace problem1 {
#include "../Problem Set 1/Problem 1.cpp"
}
namespace problem2 {
#include "../Problem Set 1/Problem 2.cpp"
}
namespace problem3 {
#include "../Problem Set 1/Problem 3.cpp"
}

#undef main

typedef std::vector<int> V;

static int checks = 0;
static int failures = 0;

#define CHECK(cond)                                                          \
    do {                                                                     \
        checks++;                                                            \
        if (!(cond)) {                                                       \
            failures++;                                                      \
            std::cerr << "FAIL line " << __LINE__ << ": " << #cond << "\n"; \
        }                                                                    \
    } while (0)

// ---------------------------------------------------------------- helpers

struct Run {
    int code;
    std::string out;
};

// Runs one of the renamed main() functions with `input` as its keyboard input
// and returns its exit code together with everything it printed.
static Run runProgram(int (*program)(), const std::string &input) {
    std::istringstream in(input);
    std::ostringstream out;
    std::streambuf *oldIn = std::cin.rdbuf(in.rdbuf());
    std::streambuf *oldOut = std::cout.rdbuf(out.rdbuf());
    int code = program();
    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);
    Run result = {code, out.str()};
    return result;
}

static std::string printedLcs(std::string a, std::string b) {
    std::ostringstream out;
    std::streambuf *oldOut = std::cout.rdbuf(out.rdbuf());
    problem1::lcs(a, b);
    std::cout.rdbuf(oldOut);
    return out.str();
}

static bool contains(const std::string &text, const std::string &part) {
    return text.find(part) != std::string::npos;
}

// "n" lines of the same text, used to build inputs with many edges
static std::string repeatLine(const std::string &line, int n) {
    std::string text;
    for (int i = 0; i < n; i++)
        text += line + "\n";
    return text;
}

// Problem 2 and Problem 3 keep their graph in global arrays; clear them so
// that every scenario starts from an empty graph.
static void resetProblem2() {
    problem2::front = 0;
    problem2::rear = 0;
    std::fill(std::begin(problem2::adjSize), std::end(problem2::adjSize), 0);
    std::fill(std::begin(problem2::dist), std::end(problem2::dist), 0);
}

static void resetProblem3() {
    problem3::top = -1;
    problem3::edgeCount = 0;
    problem3::timeCounter = 0;
    std::fill(std::begin(problem3::adjSize), std::end(problem3::adjSize), 0);
    std::fill(std::begin(problem3::color), std::end(problem3::color), 0);
    std::fill(std::begin(problem3::discovery), std::end(problem3::discovery), 0);
    std::fill(std::begin(problem3::finish), std::end(problem3::finish), 0);
    std::fill(std::begin(problem3::neighborIndex), std::end(problem3::neighborIndex), 0);
    std::fill(std::begin(problem3::edgeType), std::end(problem3::edgeType), std::string());
}

static Run runBfs(const std::string &input) {
    resetProblem2();
    return runProgram(problem2::programMain, input);
}

static Run runDfs(const std::string &input) {
    resetProblem3();
    return runProgram(problem3::programMain, input);
}

// ---------------------------------------------------------- SUM Algorithms

static void testKadane() {
    CHECK(kadans::kadane(V{-2, 1, -3, 4, -1, 2, 1, -5, 4}) == 6);
    CHECK(kadans::kadane(V{-5, -2, -8, -1, -4}) == -1);
    CHECK(kadans::kadane(V{1, 2, 3}) == 6);
    CHECK(kadans::kadane(V{7}) == 7);
}

static void testKadaneWithIndices() {
    kadans::SubarrayResult mixed = kadans::kadaneWithIndices(V{-2, 1, -3, 4, -1, 2, 1, -5, 4});
    CHECK(mixed.maxSum == 6);
    CHECK(mixed.start == 3);
    CHECK(mixed.end == 6);

    // all negative: the answer is the single largest element
    kadans::SubarrayResult negative = kadans::kadaneWithIndices(V{-5, -2, -8, -1, -4});
    CHECK(negative.maxSum == -1);
    CHECK(negative.start == 3);
    CHECK(negative.end == 3);

    // best subarray is the first element; a later, smaller restart must not move it
    kadans::SubarrayResult first = kadans::kadaneWithIndices(V{5, -1, -9, 2});
    CHECK(first.maxSum == 5);
    CHECK(first.start == 0);
    CHECK(first.end == 0);
}

static void testPrefixSum() {
    V prefix = prefixSum::buildPrefixSum(V{2, 4, 6, 8, 10});
    CHECK(prefix == (V{2, 6, 12, 20, 30}));
    CHECK(prefixSum::getRangeSum(prefix, 0, 2) == 12);
    CHECK(prefixSum::getRangeSum(prefix, 1, 3) == 18);
    CHECK(prefixSum::getRangeSum(prefix, 2, 4) == 24);
    CHECK(prefixSum::getRangeSum(prefix, 3, 3) == 8);
    CHECK(prefixSum::getRangeSum(prefix, 0, 4) == 30);

    CHECK(prefixSum::buildPrefixSum(V{7}) == (V{7}));
}

static void testSuffixSum() {
    V suffix = suffixSum::buildSuffixSum(V{2, 4, 6, 8, 10});
    CHECK(suffix == (V{30, 28, 24, 18, 10}));
    CHECK(suffixSum::getRangeSum(suffix, 0, 2, 5) == 12);
    CHECK(suffixSum::getRangeSum(suffix, 1, 3, 5) == 18);
    CHECK(suffixSum::getRangeSum(suffix, 2, 4, 5) == 24);
    CHECK(suffixSum::getRangeSum(suffix, 4, 4, 5) == 10);
    CHECK(suffixSum::getRangeSum(suffix, 0, 4, 5) == 30);

    CHECK(suffixSum::buildSuffixSum(V{7}) == (V{7}));
}

// every range of a mixed array, compared with adding the elements one by one
static void testRangeSumsAgainstPlainLoop() {
    V arr = {3, -1, 4, -1, 5, -9, 2, 6};
    int n = arr.size();
    V prefix = prefixSum::buildPrefixSum(arr);
    V suffix = suffixSum::buildSuffixSum(arr);

    int prefixMismatches = 0, suffixMismatches = 0;
    for (int left = 0; left < n; left++) {
        int expected = 0;
        for (int right = left; right < n; right++) {
            expected += arr[right];
            if (prefixSum::getRangeSum(prefix, left, right) != expected)
                prefixMismatches++;
            if (suffixSum::getRangeSum(suffix, left, right, n) != expected)
                suffixMismatches++;
        }
    }
    CHECK(prefixMismatches == 0);
    CHECK(suffixMismatches == 0);
}

// ------------------------------------------------ Problem 1: LCS

static void testLcs() {
    CHECK(printedLcs("abcd", "bd") == "Length of LCS: 2\nLCS: bd\n");
    CHECK(printedLcs("AGGTAB", "GXTXAYB") == "Length of LCS: 4\nLCS: GTAB\n");
    CHECK(printedLcs("same", "same") == "Length of LCS: 4\nLCS: same\n");
    CHECK(printedLcs("abc", "xyz") == "Length of LCS: 0\nLCS: \n");
    CHECK(printedLcs("", "abc") == "Length of LCS: 0\nLCS: \n");

    // the example of the assignment, typed in like a user would
    Run run = runProgram(problem1::programMain, "abcd\nbd\n");
    CHECK(run.code == 0);
    CHECK(run.out == "X = Y = Length of LCS: 2\nLCS: bd\n");
}

// ------------------------------------------------ Problem 2: BFS distances

static void testBfs() {
    // the example of the assignment
    Run sample = runBfs("6\n7\n1 2\n1 3\n2 4\n2 5\n3 5\n4 6\n5 6\n1\n");
    CHECK(sample.code == 0);
    CHECK(sample.out == "Number of Vertex: Number of Edges: Source Vertex: "
                        "Distances from source 1:\n"
                        "Node 1: 0\nNode 2: 1\nNode 3: 1\nNode 4: 2\nNode 5: 2\nNode 6: 3\n");

    // two separate components: nodes that cannot be reached stay at -1
    Run split = runBfs("5\n2\n1 2\n4 5\n4\n");
    CHECK(split.code == 0);
    CHECK(contains(split.out, "Node 1: -1\nNode 2: -1\nNode 3: -1\nNode 4: 0\nNode 5: 1\n"));

    // the functions used directly
    resetProblem2();
    problem2::addEdge(1, 2);
    problem2::addEdge(2, 3);
    problem2::bfs(1, 4);
    CHECK(problem2::dist[1] == 0);
    CHECK(problem2::dist[2] == 1);
    CHECK(problem2::dist[3] == 2);
    CHECK(problem2::dist[4] == -1);
}

// Input that does not fit the fixed-size arrays must be refused with exit
// code 1 instead of being written outside the arrays.
static void testBfsRefusesInputThatDoesNotFit() {
    Run tooManyVertices = runBfs("200\n0\n1\n");
    CHECK(tooManyVertices.code == 1);
    CHECK(contains(tooManyVertices.out, "Invalid input"));

    CHECK(runBfs("3\n1\n500 1\n1\n").code == 1);  // vertex number too large
    CHECK(runBfs("3\n1\n1 -7\n1\n").code == 1);   // negative vertex number
    CHECK(runBfs("3\n1\n1 2\n5000\n").code == 1); // source outside the arrays
    CHECK(runBfs("3\n2\n1 2\n").code == 1);       // input ends too early
    CHECK(runBfs("abc\n").code == 1);             // not a number
    CHECK(runBfs("3\nabc\n").code == 1);

    // a row of adj[][] holds 100 neighbours: exactly 100 is fine, 101 is not
    CHECK(runBfs("3\n100\n" + repeatLine("1 2", 100) + "1\n").code == 0);
    CHECK(runBfs("3\n101\n" + repeatLine("1 2", 101) + "1\n").code == 1);

    // a self loop takes two slots of the same row
    CHECK(runBfs("3\n50\n" + repeatLine("1 1", 50) + "1\n").code == 0);
    CHECK(runBfs("3\n51\n" + repeatLine("1 1", 51) + "1\n").code == 1);

    // the largest graph that fits is still accepted
    Run largest = runBfs("99\n2\n1 99\n99 50\n99\n");
    CHECK(largest.code == 0);
    CHECK(contains(largest.out, "Node 1: 1\n"));
    CHECK(contains(largest.out, "Node 50: 1\n"));
    CHECK(contains(largest.out, "Node 99: 0\n"));
}

// ------------------------------------------------ Problem 3: DFS edge types

static void testDfsEdgeTypes() {
    // the example of the assignment
    Run sample = runDfs("3\n3\n1 2\n2 3\n3 1\n");
    CHECK(sample.code == 0);
    CHECK(sample.out == "Number of vertex: Number of edges: Output:\n"
                        "Edge_12: TE\nEdge_23: TE\nEdge_31: BE\n"
                        "The cycle is created due to the edge 31.\n");

    // no cycle: one forward edge (1->3) and one cross edge (4->3)
    Run dag = runDfs("4\n4\n1 2\n2 3\n1 3\n4 3\n");
    CHECK(dag.code == 0);
    CHECK(dag.out == "Number of vertex: Number of edges: Output:\n"
                     "Edge_12: TE\nEdge_23: TE\nEdge_13: FE\nEdge_43: CE\n");

    // a self loop is a back edge
    Run loop = runDfs("1\n1\n1 1\n");
    CHECK(loop.code == 0);
    CHECK(contains(loop.out, "Edge_11: BE\nThe cycle is created due to the edge 11.\n"));
}

static void testDfsRefusesInputThatDoesNotFit() {
    Run tooManyVertices = runDfs("150\n0\n");
    CHECK(tooManyVertices.code == 1);
    CHECK(contains(tooManyVertices.out, "Invalid input"));

    CHECK(runDfs("3\n1\n1 400\n").code == 1); // vertex number too large
    CHECK(runDfs("3\n1\n-3 1\n").code == 1);  // negative vertex number
    CHECK(runDfs("3\n2\n1 2\n").code == 1);   // input ends too early
    CHECK(runDfs("x\n").code == 1);           // not a number
    CHECK(runDfs("3\nx\n").code == 1);

    // edgeFrom[], edgeTo[] and edgeType[] hold 1000 edges
    std::string manyEdges;
    for (int i = 0; i < 1000; i++)
        manyEdges += std::to_string(1 + i % 99) + " " + std::to_string(1 + (i * 7 + 3) % 99) + "\n";
    CHECK(runDfs("99\n1000\n" + manyEdges).code == 0);
    CHECK(runDfs("99\n1001\n" + manyEdges + "1 2\n").code == 1);

    // a row of adj[][] holds 100 outgoing edges
    CHECK(runDfs("3\n100\n" + repeatLine("1 2", 100)).code == 0);
    CHECK(runDfs("3\n101\n" + repeatLine("1 2", 101)).code == 1);
}

int main() {
    testKadane();
    testKadaneWithIndices();
    testPrefixSum();
    testSuffixSum();
    testRangeSumsAgainstPlainLoop();
    testLcs();
    testBfs();
    testBfsRefusesInputThatDoesNotFit();
    testDfsEdgeTypes();
    testDfsRefusesInputThatDoesNotFit();

    std::cout << (checks - failures) << "/" << checks << " checks passed\n";
    return failures == 0 ? 0 : 1;
}
