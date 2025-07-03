#include<iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

// Function to normalize the decision matrix
void normalizeMatrix(vector<vector<double>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    vector<double> columnSum(m, 0.0);

    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            columnSum[j] += matrix[i][j] * matrix[i][j];
        }
        columnSum[j] = sqrt(columnSum[j]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] /= columnSum[j];
        }
    }
}

// Function to apply weights to the normalized matrix
void applyWeights(vector<vector<double>>& matrix, const vector<double>& weights) {
    int n = matrix.size();
    int m = matrix[0].size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] *= weights[j];
        }
    }
}

// Function to find ideal and negative ideal solutions
void findIdealSolutions(const vector<vector<double>>& matrix, vector<double>& ideal, vector<double>& negativeIdeal) {
    int m = matrix[0].size();
    int n = matrix.size();

    ideal.assign(m, numeric_limits<double>::lowest());
    negativeIdeal.assign(m, numeric_limits<double>::max());

    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            ideal[j] = max(ideal[j], matrix[i][j]);
            negativeIdeal[j] = min(negativeIdeal[j], matrix[i][j]);
        }
    }
}

// Function to calculate distances from ideal and negative ideal solutions
void calculateDistances(const vector<vector<double>>& matrix, const vector<double>& ideal, const vector<double>& negativeIdeal, vector<double>& distancesPositive, vector<double>& distancesNegative) {
    int n = matrix.size();
    int m = matrix[0].size();

    distancesPositive.assign(n, 0.0);
    distancesNegative.assign(n, 0.0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            distancesPositive[i] += pow(matrix[i][j] - ideal[j], 2);
            distancesNegative[i] += pow(matrix[i][j] - negativeIdeal[j], 2);
        }
        distancesPositive[i] = sqrt(distancesPositive[i]);
        distancesNegative[i] = sqrt(distancesNegative[i]);
    }
}

// Function to calculate performance scores and rank alternatives
void calculatePerformanceScores(const vector<double>& distancesPositive, const vector<double>& distancesNegative, vector<double>& scores) {
    int n = distancesPositive.size();
    scores.resize(n);

    for (int i = 0; i < n; i++) {
        scores[i] = distancesNegative[i] / (distancesPositive[i] + distancesNegative[i]);
    }
}

int main(){

    vector<vector<double>> matrix = {
        {15, 4000, 2.4, 2, 0.75},
        {17, 5000, 2.6, 2, 0.7},
        {16, 4500, 2.5, 2, 0.9},
        {18, 5500, 2.4, 4, 0.8},
    };
    
    vector<double> weights = {0.3, 0.25, 0.2, 0.15, 0.1};

    // Normalize matrix
    normalizeMatrix(matrix);
    
    // Apply weights
    applyWeights(matrix, weights);
    
    // Find ideal solutions
    vector<double> ideal, negativeIdeal;
    findIdealSolutions(matrix, ideal, negativeIdeal);
    
    // Calculate distances
    vector<double> distancesPositive, distancesNegative;
    calculateDistances(matrix, ideal, negativeIdeal, distancesPositive, distancesNegative);
    
    // Calculate performance scores
    vector<double> scores;
    calculatePerformanceScores(distancesPositive, distancesNegative, scores);
    
    // Display ranks
    cout << "Performance Scores and Rankings:\n";
    for (size_t i = 0; i < scores.size(); i++) {
        cout << "Alternative " << i + 1 << ": Score = " << scores[i] << endl;
    }

    return 0;
}