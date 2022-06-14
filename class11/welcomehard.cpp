#include <iostream>
#include <vector>
#include <string>

using namespace std;
typedef long long ll;
typedef vector<ll> vll;


string four_digit_num(ll num) {
    int mod_num = num % 10000;
    string final_res = std::to_string(mod_num);
    int temp = final_res.size();
    for (int i = 1; i <= 4 - temp; i++) {
        final_res = "0" + final_res;
    }
    return final_res;

}

int main() {
    string que_string = "welcome to code jam";
    string test_num_str;
    getline(std::cin, test_num_str);
    int test_num = stoi(test_num_str);
    vll rec_mat(30,
                0); // long long due to large results mentioned in the question
    string input_sen;
    for (int t_case = 0; t_case < test_num; t_case++) {
        getline(std::cin, input_sen);
        rec_mat = vll(30, 0);
        rec_mat[0] = 1;//base case
        for (int i = 0; i < input_sen.size(); i++) {
            for (int j = 0; j < que_string.size(); j++) {
                if (input_sen[i] == que_string[j]) {
                    rec_mat[j + 1] = rec_mat[j] +
                                     rec_mat[j + 1]; // al the before options
                    if (rec_mat[j + 1] > 9999) {
                        rec_mat[j + 1] = rec_mat[j + 1] %
                                         10000; // last four, without it, could be long long overflow
                    }
                }
            }
        }
        printf("Case #%d: %s\n", t_case + 1,
               four_digit_num(rec_mat[19]).c_str());
    }

    return 0;
}