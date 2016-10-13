#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

string symbol(int a) {
  string left = " → ";
  string up = " ↓ ";
  string left_up = " ↘ ";
  if (a == 1) return left;
  if (a == 2) return up;
  if (a == 3) return left_up;
  return " * ";
}
int main(int argc, char* argv[]) {
  // read two text file name
  string text1 = argv[1];
  string text2 = argv[2];
  
  // read each text file into a vector<string>
  ifstream fin1(text1);
  ifstream fin2(text2);
  vector<string> str1, str2;
  string line;
  while (getline(fin1, line)) {
    str1.emplace_back(line);
  }
  while (getline(fin2, line)) {
    str2.emplace_back(line);
  }

  int len1 = str1.size();
  int len2 = str2.size();

  vector<int> dp_tmp(len2+1, 0);
  vector<vector<int>> dp(len1+1, dp_tmp);

  // 1: left 2: up 3: left up
  vector<int> state_tmp(len2+1, 0);
  vector<vector<int>> state(len1+1, state_tmp);

  for (int i = 1; i <= len1; i++) {
    for (int j = 1; j <= len2; j++) {
      if (str1[i-1] == str2[j-1]) {
	dp[i][j] = dp[i-1][j-1] + 1;
	state[i][j] = 3;
      }
      else {
        if (dp[i-1][j] > dp[i][j-1]) {
	  dp[i][j] = dp[i-1][j];
	  state[i][j] = 1;
	}
	else {
	  dp[i][j] = dp[i][j-1];
	  state[i][j] = 2;
	}
      }
    }
  }

  // generate result
  vector<string> result;

  int idx1 = len1;
  int idx2 = len2;

  while (idx1 != 0 || idx2 != 0) {
    if (idx1 == 0 && idx2 == 0) {
      break;
    }
    if (idx1 == 0) {
      while (idx2 != 0) {
        string result_line = "+" + str2[idx2-1];
        result.emplace_back(result_line);
	idx2--;
      }
      break;
    }
    if (idx2 == 0) {
      while (idx1 != 0) {
        string result_line = "-" + str1[idx1-1];
        result.emplace_back(result_line);
	idx1--;
      }
      break;
    }
    if (state[idx1][idx2] == 3) {
      string result_line = " " + str1[idx1-1];
      idx1--; idx2--;
      result.emplace_back(result_line);
    }
    else if (state[idx1][idx2] == 2) {
      string result_line = "+" + str2[idx2-1];
      result.emplace_back(result_line);
      idx2--;
    }
    else {
      string result_line = "-" + str1[idx1-1];
      result.emplace_back(result_line);
      idx1--;
    }
  }
  reverse(result.begin(), result.end());
  for (auto& str : result) {
    cout << str << endl;
  }
  for (int i = 0; i <= len2; i++) {
    for (int j = 0; j <= len1; j++) {
      cout << symbol(state[j][i]);
    }
    cout << endl;
  }
  return 0;
}
