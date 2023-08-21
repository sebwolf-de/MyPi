#include <iostream>
#include <random>

#include <mpi.h>

inline bool withinCircle(double x, double y) { return x * x + y * y < 1.0; }

uint64_t countWithinCircle(uint64_t numSamples) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-1.0, 1.0);

  uint64_t within = 0;
  for (uint64_t n = 0; n < numSamples; ++n) {
    const double x = dis(gen);
    const double y = dis(gen);
    within += static_cast<unsigned long>(withinCircle(x, y));
  }

  return within;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "usage: mypi n, where n is the number of samples." << std::endl;
    return 1;
  }

  MPI_Init(&argc, &argv);

  int worldRank;
  MPI_Comm_rank(MPI_COMM_WORLD, &worldRank);
  int worldSize;
  MPI_Comm_size(MPI_COMM_WORLD, &worldSize);

  const uint64_t globalNumSamples = std::atoi(argv[1]);

  if (worldRank == 0) {
    std::cout << "Compute the value of PI with " << globalNumSamples << " samples." << std::endl;
  }

  const auto localNumSamples = globalNumSamples / worldSize;
  const auto localC = countWithinCircle(localNumSamples);
  std::cout << "Rank " << worldRank << ": " << localC << " / " << localNumSamples << std::endl;

  uint64_t globalC;
  MPI_Reduce(&localC, &globalC, 1, MPI_UNSIGNED_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

  if (worldRank == 0) {
    std::cout << "Global: " << globalC << std::endl;
    const auto volume = 4.0;
    std::cout << "PI = "
              << volume * static_cast<double>(globalC) /
                     static_cast<double>(localNumSamples * worldSize)
              << std::endl;
  }

  MPI_Finalize();
  return 0;
}
