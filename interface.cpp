#include <iostream>
#include <vector>

const int INF = 1000000000;

//segment structure storing its length and the index of the last element
struct Section {
    int length, end;
};

//structure to store the number of houses and stations
struct Data {
    int houses, stations;
};

//number reading function
Data * ReadData(std::istream &input = std::cin);

//function to read the coordinates of houses in the vector
std::vector<int> ReadRoad(const Data * info, std::istream &input = std::cin);

//function to display the result
void PrintAnswer(const Data * data, const std::vector<int> road,
    const std::vector<std::vector<Section>> result, std::ostream &output = std::cout);

//function to count prefix sums
std::vector<int> CalculatePrefixSums(const std::vector<int> & road);

//function to calculate the minimum amounts for all sub-cuts of houses with one charging station
std::vector<std::vector<int>> CalculateSums(const Data* data, const std::vector<int> & road,
    const std::vector<int> & prefixSums, std::vector<std::vector<Section>> & result);

//function to calculate the minimum distance for prefixes with the number of stations from 2 and more
void CalculateResult(const Data * data, std::vector<std::vector<Section>> & result,
    const std::vector<std::vector<int>> sums);

//a function combining all the components of a solution to store them in a two-dimensional vector of segments
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
