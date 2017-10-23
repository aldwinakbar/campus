#include <cmath>
#include <vector>
#include <iostream>
#include <iomanip>

double gaussian (double x, double mu, double sigma) {
  return std::exp( -(((x-mu)/(sigma))*((x-mu)/(sigma)))/2.0 );
}

std::vector<std::vector<double>> produce2dGaussianKernel (int kernelRadius) {
  double sigma = kernelRadius/2.;
  std::vector<std::vector<double>> kernel2d(2*kernelRadius+1, std::vector<double>(2*kernelRadius+1));
  double sum = 0;
  // compute values
  for (int row = 0; row < kernel2d.size(); row++)
    for (int col = 0; col < kernel2d[row].size(); col++) {
      double x = gaussian(row, kernelRadius, sigma)
               * gaussian(col, kernelRadius, sigma);
      kernel2d[row][col] = x;
      sum += x;
    }
  // normalize
  for (int row = 0; row < kernel2d.size(); row++)
    for (int col = 0; col < kernel2d[row].size(); col++)
      kernel2d[row][col] /= sum;
  return kernel2d;
}

int main() {
  std::vector<std::vector<double>> kernel2d = produce2dGaussianKernel(1);
  std::cout << std::setprecision(5) << std::fixed;
  for (int row = 0; row < kernel2d.size(); row++) {
    for (int col = 0; col < kernel2d[row].size(); col++)
      std::cout << kernel2d[row][col] << ' ';
    std::cout << '\n';
  }
}