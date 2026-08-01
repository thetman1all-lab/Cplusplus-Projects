#ifndef TENSOR_HPP
#define TENSOR_HPP

#include <vector>

class Tensor {

private:
    // ========== Private Data Members ==========
    std::vector<float> data_;       // The actual numbers stored in a flat 1D array
    std::vector<int>   shape_;      // e.g. {2, 3, 4}
    std::vector<int>   strides_;    // Precomputed strides for fast indexing

    // Helpers to make public members cleaner
    void compute_strides();                           // calculates strides_ from shape_
    int  flat_index(int i, int j) const;              // helper for 2D
    int  flat_index(int i, int j, int k) const;       // helper for 3D
    int flat_index(int i, int j, int k, int l) const; // helper for 4D


public:
    // Constructors & Destructor
    //==================================================================================================================

    Tensor();                                      // default (empty tensor)
    Tensor(const std::vector<int>& shape);         // create with given shape (uninitialized or zeroed)
    Tensor(const std::vector<int>& shape, float value); // fill with a constant
    Tensor(const Tensor& other);                   // copy constructor
    Tensor(Tensor&& other) noexcept;               // move constructor
    ~Tensor();

    Tensor& operator=(const Tensor& other);        // copy assignment
    Tensor& operator=(Tensor&& other) noexcept;    // move assignment


    // Shape & Size Information
    //==================================================================================================================

    const std::vector<int>& shape() const;
    int rank() const;                              // number of dimensions
    int size() const;                              // total number of elements (numel)
    int size(int dim) const;                       // size of a specific dimension
    bool empty() const;


    // Element Access
    //==================================================================================================================

    float& operator()(int i);                      // 1D access
    float  operator()(int i) const;

    float& operator()(int i, int j);               // 2D access
    float  operator()(int i, int j) const;

    float& operator()(int i, int j, int k);        // 3D access
    float  operator()(int i, int j, int k) const;

    float& operator()(int i, int j, int k, int l); // 4D access
    float  operator()(int i, int j, int k, int l) const;

    float* data();                                 // raw pointer to underlying data
    const float* data() const;


    // Element-wise Arithmetic (binary)
    //==================================================================================================================

    Tensor operator+(const Tensor& other) const;
    Tensor operator-(const Tensor& other) const;
    Tensor operator*(const Tensor& other) const;   // element-wise (Hadamard)
    Tensor operator/(const Tensor& other) const;

    Tensor& operator+=(const Tensor& other);
    Tensor& operator-=(const Tensor& other);
    Tensor& operator*=(const Tensor& other);
    Tensor& operator/=(const Tensor& other);


    // Scalar Arithmetic
    //==================================================================================================================

    Tensor operator+(float scalar) const;
    Tensor operator-(float scalar) const;
    Tensor operator*(float scalar) const;
    Tensor operator/(float scalar) const;

    Tensor& operator+=(float scalar);
    Tensor& operator-=(float scalar);
    Tensor& operator*=(float scalar);
    Tensor& operator/=(float scalar);

    // Optional but convenient (so you can write 5 * tensor)
    friend Tensor operator+(float scalar, const Tensor& t);
    friend Tensor operator*(float scalar, const Tensor& t);


    // Unary Operations
    //==================================================================================================================

    Tensor operator-() const;                      // negation
    Tensor abs() const;
    Tensor relu() const;                           // max(0, x) – useful later


    // Linear Algebra
    //==================================================================================================================

    Tensor matmul(const Tensor& other) const;      // matrix multiplication
    Tensor transpose() const;                      // 2D transpose
    Tensor outer(const Tensor& other) const;       // outer product (useful for gradients later)


    // Reductions
    //==================================================================================================================

    float sum() const;                             // sum of all elements
    float mean() const;
    float max() const;
    float min() const;

    // Optional but very useful later:
    Tensor sum(int axis) const;                    // sum along a specific axis
    Tensor mean(int axis) const;


    // Shape Manipulation
    //==================================================================================================================

    Tensor reshape(const std::vector<int>& new_shape) const;
    void reshape_(const std::vector<int>& new_shape);   // in-place version (optional)


    // Utility/Debugging
    //==================================================================================================================

    void fill(float value);
    void zeros();
    void ones();
    void random(float min = 0.0f, float max = 1.0f);   // simple uniform random

    void print(const std::string& name = "") const;     // nice formatted printing

};

#endif