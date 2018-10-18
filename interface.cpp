#include <iostream>
#include <vector>

const int INF = 1000000000;

struct Section {
    int length, end;
};

struct Data {
    int houses, stations;
};

Data * ReadData(std::istream &input = std::cin);

std::vector<int> ReadRoad(const Data * info, std::istream &input = std::cin);

void PrintAnswer(const Data * data, const std::vector<int> road,
    const std::vector<std::vector<Section>> result, std::ostream &output = std::cout);

std::vector<int> CalculatePrefixSums(const std::vector<int> & road);

std::vector<std::vector<int>> CalculateSums(const Data* data, const std::vector<int> & road,
    const std::vector<int> & prefixSums, std::vector<std::vector<Section>> & result);

void CalculateResult(const Data * data, std::vector<std::vector<Section>> & result,
    const std::vector<std::vector<int>> sums);

std::vector<std::vector<Section>> Dynamic_Programming(const Data * data,
    const std::vector<int> & road);

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    const Data * data = ReadData();
    const auto & road = ReadRoad(data);
    const auto & result = Dynamic_Programming(data, road);
    PrintAnswer(data, road, result);
    return 0;
}
