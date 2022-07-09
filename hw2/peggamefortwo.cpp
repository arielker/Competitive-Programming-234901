#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <cmath>

using namespace std;

typedef long long ll;

// bool
typedef pair<bool, bool> bb;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<bb> vbb;
typedef vector<vbb> vvbb;

// int
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;

// double
typedef pair<double, double> dd;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef vector<dd> vdd;
typedef vector<vdd> vvdd;

// ll
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<pll> vpll;
typedef vector<vpll> vvpll;

// set
typedef set<int> si;
typedef set<ll> sll;
typedef set<vii> svii;
typedef vector<si> vsi;


vector<string> string_tokenizer(const string &sentence) {
    vector<string> words;
    stringstream ss(sentence);
    string word;
    while (ss >> word) {
        words.push_back(word);
    }

    return words;
}

vector<ll> int_tokenizer(const string &sentence) {
    vector<ll> words;
    stringstream ss(sentence);
    ll word;
    while (ss >> word) {
        words.push_back(word);
    }

    return words;
}


const long long INF = 1e9;
#define LINES 5


bool check_legal(const vvll &board, ll cur_row, ll cur_col, ll next_row, ll next_col) {
    // outside board
    if ((next_row >= LINES || next_col >= LINES) ||
        (next_col < 0 || next_row < 0) ||
        (next_row < next_col))
        return false;

    // place is taken
    if (board[next_row][next_col] > 0)
        return false;

    // jumps above an empty place
    if (board[(cur_row + next_row) / 2][(cur_col + next_col) / 2] == 0)
        return false;

    // Jumps must be in straight lines (horizontally or diagonally)
    if (next_row - cur_row + next_col - cur_col == 0)
        return false;

    return true;
}

map<vvll, ll> cache; // board -> val

ll solve_game(vvll &board) {
    ll OPT = -INF;

    // memorization
    if (cache.count(board) > 0) {
        return cache[board];
    }

    for (int row = 0; row < LINES; ++row) {
        for (int col = 0; col <= row; ++col) {
            // this place is empty
            if (board[row][col] == 0) continue;

            for (int delta_row = -2; delta_row <= 2; delta_row += 2) {
                for (int delta_col = -2; delta_col <= 2; delta_col += 2) {
                    int next_row = row + delta_row;
                    int next_col = col + delta_col;
                    if (!check_legal(board, row, col, next_row, next_col))
                        continue;

                    int row_jumped_above = row + delta_row / 2;
                    int col_jumped_above = col + delta_col / 2;

                    // save old values
                    ll curr_place_value = board[row][col];
                    ll jumped_above_value = board[row_jumped_above][col_jumped_above];
                    ll jump_value = curr_place_value * jumped_above_value;

                    // update new board
                    board[row][col] = 0;
                    board[row_jumped_above][col_jumped_above] = 0;
                    board[next_row][next_col] = curr_place_value;

                    // calc next move value
                    ll solved_value = solve_game(board);
                    OPT = (solved_value == -INF) ? max(OPT, jump_value) : max(OPT, jump_value - solved_value); // -INF means no more possible moves

                    // return old values
                    board[row][col] = curr_place_value;
                    board[row_jumped_above][col_jumped_above] = jumped_above_value;
                    board[next_row][next_col] = 0;
                }
            }
        }
    }

    cache[board] = (OPT == -INF) ? 0 : OPT;

//    return cache[board];
    return OPT;
}


int main() {
    vvll board(LINES);
    for (int i = 1; i <= LINES; ++i) {
        vll row(i);
        for (int j = 0; j < i; ++j) {
            cin >> row[j];
        }
        board[i - 1] = row;
    }
    cout << solve_game(board) << endl;

    return 0;
}
