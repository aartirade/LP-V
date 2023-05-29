
#include<iostream>
#include<omp.h>

using namespace std;
int minval(int arr[], int n){
  int minval = arr[0];
  #pragma omp parallel for reduction(min : minval)
    for(int i = 0; i < n; i++){
      if(arr[i] < minval) minval = arr[i];
    }
  return minval;
}

int maxval(int arr[], int n){
  int maxval = arr[0];
  #pragma omp parallel for reduction(max : maxval)
    for(int i = 0; i < n; i++){
      if(arr[i] > maxval) maxval = arr[i];
    }
  return maxval;
}

int sum(int arr[], int n){
  int sum = 0;
  #pragma omp parallel for reduction(+ : sum)
    for(int i = 0; i < n; i++){
      sum += arr[i];
    }
  return sum;
}

int average(int arr[], int n){
  return (double)sum(arr, n) / n;
}

int main(){
  int n = 5;
  int arr[] = {1,2,3,4,5};
  cout << "The minimum value is: " << minval(arr, n) << '\n';
  cout << "The maximum value is: " << maxval(arr, n) << '\n';
  cout << "The summation is: " << sum(arr, n) << '\n';
  cout << "The average is: " << average(arr, n) << '\n';
  return 0;
}


//using openmp

#include <iostream>
#include <vector>
#include <omp.h>

// Function for parallel reduction to find the minimum value
int parallelMin(const std::vector<int>& data) {
    int minVal = data[0];

    #pragma omp parallel for reduction(min: minVal)
    for (size_t i = 1; i < data.size(); ++i) {
        if (data[i] < minVal) {
            minVal = data[i];
        }
    }

    return minVal;
}

// Function for parallel reduction to find the maximum value
int parallelMax(const std::vector<int>& data) {
    int maxVal = data[0];

    #pragma omp parallel for reduction(max: maxVal)
    for (size_t i = 1; i < data.size(); ++i) {
        if (data[i] > maxVal) {
            maxVal = data[i];
        }
    }

    return maxVal;
}

// Function for parallel reduction to calculate the sum of elements
int parallelSum(const std::vector<int>& data) {
    int sum = 0;

    #pragma omp parallel for reduction(+: sum)
    for (size_t i = 0; i < data.size(); ++i) {
        sum += data[i];
    }

    return sum;
}

// Function for parallel reduction to calculate the average of elements
double parallelAverage(const std::vector<int>& data) {
    int sum = parallelSum(data);
    double average = static_cast<double>(sum) / data.size();

    return average;
}

int main() {
    std::vector<int> data = {5, 8, 2, 10, 3, 6, 1, 9, 4, 7};

    // Parallel Minimum
    int minVal = parallelMin(data);
    std::cout << "Minimum Value: " << minVal << std::endl;

    // Parallel Maximum
    int maxVal = parallelMax(data);
    std::cout << "Maximum Value: " << maxVal << std::endl;

    // Parallel Sum
    int sum = parallelSum(data);
    std::cout << "Sum: " << sum << std::endl;

    // Parallel Average
    double average = parallelAverage(data);
    std::cout << "Average: " << average << std::endl;

    return 0;
}

