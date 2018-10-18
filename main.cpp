#include <iostream>
#include <vector>

const int INF = 1000000000;

struct Section {
    int length, end;
};

struct Data {
    int houses, stations;
    Data(int houses, int stations) {
        this->houses = houses;
        this->stations = stations;
    }
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

Data * ReadData(std::istream &input) {
    int houses, stations;
    input >> houses >> stations;
    Data * data =new Data(houses, stations);
    return data;
}

std::vector<int> ReadRoad(const Data * data, std::istream &input) {
    std::vector<int> road(data->houses);
    for (int i = 0; i < data->houses; ++i) {
        input >> road[i];
    }
    return road;
}

void PrintAnswer(const Data * data, const std::vector<int> road,
    const std::vector<std::vector<Section>> result, std::ostream &output) {
    int left = 0, station = data->stations;
    output << result[left][station].length << "\n";
    for (int i = 0; i < data->stations; ++i, --station) {
        output << road[(left + result[left][station].end) / 2] << " ";
        left = result[left][station].end + 1;
    }
}

std::vector<int> CalculatePrefixSums(const std::vector<int> & road) {
    std::vector<int> prefixSums(road.size() + 1, 0);
    for (int i = 0; i < road.size(); ++i) {
        prefixSums[i + 1] = prefixSums[i] + road[i];
    }
    return prefixSums;
}

std::vector<std::vector<int>> CalculateSums(const Data* data, const std::vector<int> & road,
    const std::vector<int> & prefixSums, std::vector<std::vector<Section>> & result) {
    std::vector<std::vector<int>> sums(data->houses);
    for (int left = 0; left < data->houses; ++left) {
        result[left].resize(data->stations + 1);
        sums[left].resize(data->houses);
        for (int right = left; right < data->houses; right += 2) {
            int middle = (left + right) / 2;
            sums[left][right] = prefixSums[right + 1] - prefixSums[middle + 1]
                - prefixSums[middle] + prefixSums[left];
            if (right < data->houses - 1)
                sums[left][right + 1] = sums[left][right] + road[right + 1] - road[middle];
            if (right == data->houses - 1 || right == data->houses - 2) {
                result[left][1].length = sums[left][data->houses - 1];
                result[left][1].end = data->houses - 1;
            }
        }
    }
    return sums;
}

void CalculateResult(const Data * data, std::vector<std::vector<Section>> & result,
    const std::vector<std::vector<int>> sums) {
    for (int station = 2; station <= data->stations; ++station) {
        for (int left = 0; left < data->houses - station + 1; ++left) {
            result[left][station].length = INF;
            for (int right = left; right < data->houses - station + 1; ++right) {
                if (sums[left][right] + result[right + 1][station - 1].length <
                    result[left][station].length) {
                    result[left][station].length =
                        sums[left][right] + result[right + 1][station - 1].length;
                    result[left][station].end = right;
                }
            }
        }
    }
}

std::vector<std::vector<Section>> Dynamic_Programming(const Data * data,
    const std::vector<int> & road) {
    std::vector<std::vector<Section>> result(data->houses);
    const std::vector<int> prefixSums = CalculatePrefixSums(road);
    const std::vector<std::vector<int>> sums = CalculateSums(data, road, prefixSums, result);
    CalculateResult(data, result, sums);
    return result;
}
