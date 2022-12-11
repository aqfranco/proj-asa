#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <cmath>

using std::ostringstream;
using std::min;
using std::vector;
using std::string;

vector<int> index;
vector<string> pos;

bool check_block_already_exists(string s){
    if(pos.size() == 0){
        return false;
    }
    for(long unsigned int i = 0; i < pos.size(); i++){
        if(pos[i] == s){
            return true;
        }
    }
    return false;
}

int check_individual_squares(int m, int max_size){
    int counter = 0;
    if(max_size<2){
        return 0;
    }
    for(int i=1; i<=m;i++){
        for(int j=max_size; j >= 2; j--){
            if(index[i-1] < max_size){
                continue;
            }
            for(int k=(i+j-1); k <= m; k++){
                for(int l = j; l <= index[i-1]; l++){
                    ostringstream oss;
                    oss << k << "," << l << "," << j;
                    string var = oss.str();
                    if(check_block_already_exists(var) == false){
                        pos.insert(pos.end(),var);
                        counter++;
                    }
                }
            }
        }
    }
    return counter;
}

vector<string> check_squares(int k, int l, int m){
    vector<string> pos_within_square;
    for(int i = k; i > k - m; i--){
        for(int j = l; j > l - m; j--){
            ostringstream oss;
            oss << i << "," << j;
            string var = oss.str();
            pos_within_square.insert(pos_within_square.end(),var);
        }
    }
    return pos_within_square;
}

bool check_contained_squares(vector<string> a, vector<string> b){
    for(long unsigned int i = 0; i < a.size(); i++){
        for(long unsigned int j = 0; j < b.size(); j++){
            if(a[i] == b[j]){
                return true;
            }
        }
    }
    return false;
}

int check_all_squares(vector<string> b){
    int n = 0;
    int counter = 0;
    for(long unsigned int i = 0; i < b.size(); i++){
        for(long unsigned int j = i + 1; j < b.size(); j++){
            if(check_contained_squares(check_squares(b[i][0], b[i][2], b[i][4]), check_squares(b[j][0], b[j][2], b[j][4]))){
                counter += 1;
            }
        }
    }
    if(counter != 0){
        n = ((1 - sqrt(1 + 4*(2 * counter)))/2);
    }
    return pow(2, n) - 1;
}

int check_simultaneous_squares(){
    int counter = 0;
    for(long unsigned int i = 0; i < pos.size(); i++){
        int k = pos[i][0] -'0';
        int l = pos[i][2] -'0';
        int m = pos[i][4] -'0';
        vector<string> pos_within_square_a = check_squares(k, l, m);
        vector<string> non_overlapping_squares;
        for(long unsigned int j = i + 1; j < pos.size(); j++){ 
            int n = pos[j][0] -'0';
            int o = pos[j][2] -'0';
            int q = pos[j][4] -'0';
            if((k == n && l == o) || ((k - m) == (n - q) && (l - m) == (o - q))){
                continue;
            }
            vector<string> pos_within_square_b = check_squares(n, o, q);
            if(check_contained_squares(pos_within_square_a, pos_within_square_b) == true){
                continue;
            }
            ostringstream oss;
            oss << n << "," << o << "," << q;
            string var = oss.str();
            non_overlapping_squares.insert(non_overlapping_squares.end(), var);
            counter++;
        }
        counter += check_all_squares(non_overlapping_squares);
    }
    return counter;
}

int get_max_size(int m){
    int size = 0;
    for(int i = 1; i <= m; i++){
        int temp;
        temp = min((m-i+1), index[i-1]);
        if(temp > size){
            size = temp;
        }
    }
    return size;
}

int main(){
    int m;
    int n;
    int max_size;
    int n_config = 0;
    if(scanf("%d", &m)!=1){
        exit(1);
    }
    if(scanf("%d", &n)!=1){
        exit(1);
    }
    for(int i = 1; i <= m; i++){
        int d;
        if(scanf("%d", &d) != 1){
            exit(1);
        }
        if(d != 0){
            n_config = 1;
        }
        index.push_back(d);
    }
    max_size = get_max_size(m);
    n_config += check_individual_squares(m, max_size);
    n_config += check_simultaneous_squares();
    printf("%d\n", n_config);
}