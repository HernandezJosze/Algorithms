#include <iostream>
#include <vector>

template <typename T>
void auxMergesort(T *ini, T *mid, T *fin){
   T temp[fin - ini];
   int i = 0;
   T *part1 = ini, *part2 = mid;
   while(part1 < mid && part2 < fin){
      if(*part1 <= *part2){
         temp[i] = *part1;
         ++i, part1++;
      }else{
         temp[i] = *part2;
         ++i, part2++;
      }
   }
   while(part1 < mid){
      temp[i++] = *part1++;
   }
   while(part2 < fin){
      temp[i++] = *part2++;
   }
   i = 0;
   while(ini < fin){
      *ini++ = temp[i++];
   }
}

template <typename T>
void mergesort(T *ini, T *fin){
   if(ini + 1 >= fin){
      return;
   }
   T *middle = (fin - ini) / 2 + ini;
   mergesort(ini, middle);
   mergesort(middle, fin);
   auxMergesort(ini, middle, fin);
}

template <typename T>
void mergesort(T beg,T end){
   mergesort(&*beg, &*end);
   return;
}

int main( ){
   char arr[] = {33, 35, 34};
   std::vector<double> v = {1, 4, 2};

   mergesort(std::begin(arr), std::end(arr));
   for(const auto& el : arr){
      std::cout << el << ' ';
   }

   std::cout << '\n';

   mergesort(std::begin(v), std::end(v));
   for(const auto& el : v){
      std::cout << el << ' ';
   }
}
