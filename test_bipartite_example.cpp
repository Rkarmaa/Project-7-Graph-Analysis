#include "bipartite.cpp"

// Helper: vaidate result
void check_result(bool result, bool expected, std::string msg, int &correct_count)
{
    if (result == expected)
    {
        correct_count += 1;
    }
    else
    {
        std::cout << msg << std::endl;
        std::cout << "\texpected:" << std::endl
                  << expected << std::endl;
        std::cout << "\treceived:" << std::endl
                  << result << std::endl;
    }
}

void test_bipartite(int &correct, int &total)
{
    int correct_count = 0;
    std::string fname;
    std::string msg;

    for (int i = 1; i <= 5; i++)
    {
		fname = "bipartite_graphs/bg" + std::to_string(i) + ".txt";
        Graph G(fname);
        msg = "incorrect result for bipartite graph " + std::to_string(i);
        check_result(G.is_bipartite(), true, msg, correct_count);
    }

    std::cout << "Passed " << correct_count << "/5 tests in test_bipartite" << std::endl;

    correct += correct_count;
    total += 5;
}

void test_nonbipartite(int &correct, int &total)
{
    int correct_count = 0;
    std::string fname;
    std::string msg;

    for (int i = 1; i <= 5; i++)
    {
		fname = "non_bipartite_graphs/ng" + std::to_string(i) + ".txt";
        Graph G(fname);
        msg = "incorrect result for non-bipartite graph " + std::to_string(i);
        check_result(G.is_bipartite(), false, msg, correct_count);
    }

    std::cout << "Passed " << correct_count << "/5 tests in test_nonbipartite" << std::endl;

    correct += correct_count;
    total += 5;
}

int main()
{
    int all_passed = 0;
    int all_total = 0;

    test_bipartite(all_passed, all_total);
    test_nonbipartite(all_passed, all_total);

    std::cout << "\nPassed a total of " << all_passed << "/" << all_total << " tests." << std::endl;

    return 0;
}