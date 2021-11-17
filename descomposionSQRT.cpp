#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

template<class T, typename F = T*(*)(T*, T*)>
class sqrtTree{
    private: 
        int segments;
        F funcion;
    public:
        std::vector<T> memory;
        std::vector<T> leaders;
        
        sqrtTree(std::vector<T> &mem, F &f) 
        : memory(std::move(mem)), funcion(std::move(f)) {
            leaders.resize(segments = std::ceil(std::sqrt(memory.size( ))));
            for(int i = 0; i < segments; ++i){
                leaders[i] = *funcion(&memory[0] + i * segments ,  &memory[0] + (i + 1) * segments);
            }
        }

        T busca(const T& beg, const T& end){ // index begin, end 
            if(beg >= memory.size( )){
            return 0;
            }

            int begLeader = beg / segments + bool (beg % segments) ;
            int endLeader = end / segments;
            std::vector<T> result;

            if(begLeader >= endLeader){
                result.push_back(*funcion(&memory[0] + beg , &memory[0] + end));
            }else{
                result.push_back(*funcion(&leaders[0] + begLeader , &leaders[0] + endLeader));
                result.push_back(*funcion(&memory[0] + beg, &memory[0] + segments * begLeader));
                result.push_back(*funcion(&memory[0] + segments * endLeader, &memory[0] + end));
            }
            return *funcion(&result[0], &result[0] + result.size( ));
        }
        void update(int index, T val){             // index to update, new value
            std::vector<T> act = {memory[index], val};
            memory[index] = val;
            int ini = (index / segments) * segments;
            int fin = ((index / segments) + 1) * segments;
            leaders[index / segments] = *funcion(&memory[0] + ini, &memory[0] + fin);
        }
};

int main( ){
    int n;
	std::cin >> n;
    std::vector<int> v(n);
	for(auto& el : v){
        std::cin >> el;
    }
    
    int* (*f)(int*, int*) = std::min_element;
    sqrtTree<int> sqrtT(v, f);
    
    std::cout << sqrtT.busca(0, n - 1);
    sqrtT.update(0, 0);
    std::cout << sqrtT.busca(0, n - 1);

    return 0;
}
