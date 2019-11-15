/**

    CSE-232, project.cpp
    Purpose: A Program to provide
	insight on passwords.

    @author Westly D Durkee

*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

/**
  Returns the number of characters different.

  @param a a string to compare.
  @param b a string to compare.
  @return The count of different characters.
*/
int char_diff(const string &a, const string &b){
  int a_size = a.size();
  int b_size = b.size();
  int result = abs(a_size-b_size); // count additional or missing chars
  int compare_length = (a_size > b_size) ? b_size : a_size;
  
  for (int i = 0; i < compare_length; ++i) {
     if (a[i] != b[i]) ++result; // count different chars
  }

  return result;
}

/**
  Reads a file by line into a vector.

  @param file_name the name of the file to read.
  @return A vector of each line in the file.
*/
vector<string> read_file_into_vector(const string &file_name){
  vector<string> result;
  string line;
  ifstream myfile (file_name);
  if (myfile.is_open()) {
    while ( getline (myfile,line) ) {
      result.push_back(line);
    }
    myfile.close();
  }
  else cout << "Unable to open file"; 

  return result;
}

/**
  Returns the lowest score and removes all strings
  with higher scores.

  @param v a vector to remove strings from.
  @param out a string to insert a concanated output.
  @return The count of different characters.
*/
int get_least_diff(vector<string> &v, const string &comparator, string &out) {
  vector<string> result;
  int best_score = 0;

  for(auto s : v) {
    int score = char_diff(s, comparator);
    if (result.size() == 0 || score < best_score) {
      out = "";
      result.clear();
      best_score = score;
    }
    if (score == best_score) {
      out = out + s.substr(0,s.size()) + ", ";
      result.push_back(s);
    }
  }

  v = result;
  return best_score;
}

int main () {
  vector<string> v = read_file_into_vector("sorted.txt");
  string comparator;
  cout << "Give me a password: ";
  cin >> comparator;
  cout << endl << "You provided a password of " << comparator << endl;
  cout << "The most similar passwords to " << comparator << " are:";
  cout << endl;
  transform(comparator.begin(), comparator.end(), comparator.begin(),
    [](unsigned char c){ return tolower(c); });
  string out = "";
  int best_score = get_least_diff(v, comparator, out);
  cout << out;
  cout << endl << "All of which are " << best_score << " character(s) different." << endl;
  return 0;
}