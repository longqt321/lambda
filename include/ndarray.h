#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include "utils.h"

template<typename T>
class ndarray{
    public:
        ndarray(){
            this->n_dims = 0;
        }
        ndarray(const std::vector<size_t>& dims){
            this->n_dims = dims.size();
            this->shape = dims;
            size_t n=1;
            for (const size_t& d: dims){
                n*=d;
            }
            this->n_elements = n;
            this->data = new T[n];
            for (int i =0;i<this->n_elements;++i){
                this->data[i] = i;
            }
        }
        virtual ~ndarray(){
            delete this->data;
        }
        template<typename... Args>
        T& operator()(Args... args){
            const std::vector<int> indices{static_cast<int>(args)...};
            if (indices.size() != this->n_dims){
                throw std::invalid_argument("Invalid dimensions");
            }
            size_t index = 0;
            size_t stride = 1;
            for (int i = static_cast<int>(this->n_dims)-1;i >=0;--i){
                if (indices[i] >= shape[i]) {
                    std::ostringstream oss;
                    oss << "Index " << indices[i] << " out of bounds for dimension "
                        << i << " with size " << shape[i];
                    throw std::out_of_range(oss.str());
                }
                index += indices[i]*stride;
                stride *= this->shape[i];
            }
            if (index >= this->n_elements){
                std::ostringstream oss;
                oss << "There are only " << this->n_elements
                << " elements, trying to access " << index << "th element";
                throw std::out_of_range(oss.str());
            }
            return this->data[index];
        }
        ndarray<T>& operator=(const ndarray<T>& other){
            if (this->shape != other.shape) {
                throw std::invalid_argument("Shapes do not match for assignment");
            }
            this->n_elements = other.n_elements;
            this->n_dims = other.n_dims;
            this->shape = other.shape;
            delete[] this->data; // Free existing data
            this->data = new T[this->n_elements];
            for (size_t i = 0; i < this->n_elements; ++i) {
                this->data[i] = other.data[i];
            }
            return *this;
        }
        ndarray<T> operator+(const ndarray& other) const{
            if (this->shape != other.shape) {
                throw std::invalid_argument("Shapes do not match for addition");
            }
            ndarray<T>* result = new ndarray<T>(this->shape);
            for (size_t i = 0; i < this->n_elements; ++i) {
                result->data[i] = this->data[i] + other.data[i];
            }
            return *result;
        }
        ndarray<T> operator-(const ndarray& other) const{
            if (this->shape != other.shape) {
                throw std::invalid_argument("Shapes do not match for subtraction");
            }
            ndarray<T>* result = new ndarray<T>(this->shape);
            for (size_t i = 0; i < this->n_elements; ++i) {
                result->data[i] = this->data[i] - other.data[i];
            }
            return *result;
        }
        ndarray<T> operator*(const ndarray& other) const{
            if (this->shape != other.shape) {
                throw std::invalid_argument("Shapes do not match for multiplication");
            }
            ndarray<T>* result = new ndarray<T>(this->shape);
            for (size_t i = 0; i < this->n_elements; ++i) {
                result->data[i] = this->data[i] * other.data[i];
            }
            return *result;
        }
        ndarray<T> operator*(const T& scalar) const {
            ndarray<T>* result = new ndarray<T>(this->shape);
            for (size_t i = 0; i < this->n_elements; ++i) {
                result->data[i] = this->data[i] * scalar;
            }
            return *result;
        }
        ndarray<T> dot(const ndarray& other) const {
            if (this->n_dims != 2 || other.n_dims != 2) {
                throw std::invalid_argument("Dot product is only defined for 2D arrays");
            }
            if (this->shape[1] != other.shape[0]) {
                throw std::invalid_argument("Inner dimensions do not match for dot product");
            }
            std::vector<size_t> result_shape = {this->shape[0], other.shape[1]};
            ndarray<T>* result = new ndarray<T>(result_shape);
            for (size_t i = 0; i < this->shape[0]; ++i) {
                for (size_t j = 0; j < other.shape[1]; ++j) {
                    T sum = 0;
                    for (size_t k = 0; k < this->shape[1]; ++k) {
                        sum += this->data[i * this->shape[1] + k] * other.data[k * other.shape[1] + j];
                    }
                    result->data[i * result_shape[1] + j] = sum;
                }
            }
            return *result;
        }
        ndarray<T> T() const {
            if (this->n_dims != 2) {
                throw std::invalid_argument("Transpose is only defined for 2D arrays");
            }
            std::vector<size_t> transposed_shape = {this->shape[1], this->shape[0]};
            ndarray<T>* transposed = new ndarray<T>(transposed_shape);
            for (size_t i = 0; i < this->shape[0]; ++i) {
                for (size_t j = 0; j < this->shape[1]; ++j) {
                    transposed->data[j * transposed_shape[1] + i] = this->data[i * this->shape[1] + j];
                }
            }
            return *transposed;
        }
        std::vector<size_t>shape;
        size_t n_dims;
        size_t n_elements;
        T* data;
    private:

};

template<typename T,typename U>
ndarray<T> operator*(const U& scalar, const ndarray<T>& array) {
    return array * static_cast<T>(scalar);
}