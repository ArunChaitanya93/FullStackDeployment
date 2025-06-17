// matmul.cpp
#include <iostream>
#include <vector>
#include <random>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
using Matrix = std::vector<std::vector<int>>;

// build n×n matrix with random ints 1–10
Matrix random_matrix(int n) {
    static std::mt19937_64 rng{std::random_device{}()};
    std::uniform_int_distribution<int> dist(1, 10);
    Matrix M(n, std::vector<int>(n));
    for(int i = 0; i < n; ++i)
      for(int j = 0; j < n; ++j)
        M[i][j] = dist(rng);
    return M;
}

// naive multiply A×B
Matrix multiply(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix C(n, std::vector<int>(n, 0));
    for(int i = 0; i < n; ++i)
      for(int k = 0; k < n; ++k)
        for(int j = 0; j < n; ++j)
          C[i][j] += A[i][k] * B[k][j];
    return C;
}

int main() {
    // parse {"size": n} from stdin
    json req;
    if(!(std::cin >> req) || !req.contains("size")) {
        std::cerr << "error: missing size\n";
        return 1;
    }
    int n = req["size"].get<int>();
    if(n < 1) {
        std::cerr << "error: size must be ≥1\n";
        return 2;
    }

    Matrix A = random_matrix(n);
    Matrix B = random_matrix(n);
    Matrix R = multiply(A, B);

    // output {"A":…, "B":…, "result":…}
    json res = { {"A", A}, {"B", B}, {"result", R} };
    std::cout << res;
    return 0;
}
