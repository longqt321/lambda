#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>

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
        
    private:
        std::vector<size_t>shape;
        size_t n_dims;
        size_t n_elements;
        T* data;
};