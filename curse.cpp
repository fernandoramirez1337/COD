#include <iostream>
#include <random>
#include <cmath>
#include <limits>

#define NUMBER_OF_POINTS 100

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> distrib(0.0, 1.0);

template <int N> struct canvas;
template <int N> struct point;

template <int N> struct canvas
{
    point<N> points[NUMBER_OF_POINTS];
    double min_distance, max_distance;
    int list[10] = {0};

    canvas()
    {
        max_distance = 0;
        min_distance = std::numeric_limits<double>::max();

        for (int i = 0; i < NUMBER_OF_POINTS; i++)
        {
            for (int j = i + 1; j < NUMBER_OF_POINTS; j++)
            {
                double tmp_ = 0;
                for (int k = 0; k < N; k++)
                {
                    tmp_ += pow(points[i].data[k] - points[j].data[k], 2);
                }
                double distance_ij = sqrt(static_cast<double>(tmp_));

                if (distance_ij > max_distance) max_distance = distance_ij;
                if (distance_ij < min_distance) min_distance = distance_ij;
            }
        }

        for (int i = 0; i < NUMBER_OF_POINTS; i++)
        {
            for (int j = i + 1; j < NUMBER_OF_POINTS; j++)
            {
                double tmp_ = 0;
                for (int k = 0; k < N; k++)
                {
                    tmp_ += pow(points[i].data[k] - points[j].data[k], 2);
                }
                double distance_ij = sqrt(static_cast<double>(tmp_));
                distance_ij = (distance_ij - min_distance) / (max_distance - min_distance);

                for (int k = 1; k <= 10; k++)
                {
                    if (distance_ij <= static_cast<double>(k) / 10)
                    {
                        list[k - 1]++;
                        break; // Break once distance is added to one bucket
                    }
                }
            }
        }
    }
};

template <int N> struct point
{
    double data[N];

    point()
    {
        for (int i = 0; i < N; i++)
        {
            data[i] = distrib(gen);
        }
    }
};

int main()
{
    const int NUMBER_OF_DIMENSIONS = 5000;
    std::cout << std::fixed;
    std::cout.precision(1);

    canvas<NUMBER_OF_DIMENSIONS> canv;
    std::cout << std::endl
              << "Curse of Dimensionality" << std::endl;
    std::cout << "Number of points: " << NUMBER_OF_POINTS << std::endl;
    std::cout << "Number of dimensions: " << NUMBER_OF_DIMENSIONS << std::endl;
    std::cout << "Ratio: (min: " << canv.min_distance << " max: " << canv.max_distance << ")" << std::endl;

    int N_OF_EVALUATED_POINTS = 0;
    for (int i = 0; i < 10; i++)
    {
        std::cout << static_cast<double>(i + 1) / 10 << "  " << canv.list[i] << std::endl;
        N_OF_EVALUATED_POINTS += canv.list[i];
    }
    std::cout << "Evaluated points: " << N_OF_EVALUATED_POINTS << std::endl;

    return 0;
}
