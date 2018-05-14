#include <iostream>
#include <cstring>

// ADD #include's HERE FOR ANY OTHER LIBRARIES YOU USE

using namespace std;

// ADD ANY GLOBAL CONSTANT HERE
const int MAX_STR = 80;

// PLACE DECLARATION (A.K.A. "PROTOTYPE") FOR YOUR FUNCTION HERE
double ComputeVowelFrequency(char line[MAX_STR], int length);

int main() {

  double vowelFreq;

  // For following to work you must be sure to define MAX_STR above
  // as a global constant (it must be global because it is used again
  // elsewhere).

  char buffer[MAX_STR];

  // Prompt the user to enter a string and read input into
  // buffer[] using getline()


  // CODE GOES HERE
  cout << "Enter a string (< 80 characters)" << endl;
  cin.getline(buffer, sizeof(buffer));

  // Now, compute the vowel frequency of the input string
  // You must provide the arguments to the function

  vowelFreq = ComputeVowelFrequency(buffer, strlen(buffer));

  // Lastly, output the frequency to the screen in a user-
  // friendly way.


  // CODE GOES HERE
  cout << "The relative frequency of vowels in your string is "
       << vowelFreq << " (" << vowelFreq*100 << "%)."<< endl;

  return 0;
}

//
// IMPLEMENT ComputeVowelFrequency() HERE
//   (Do not put it ABOVE main()! )
//
double ComputeVowelFrequency(char line[MAX_STR], int length){
  double vowelCount = 0;
  double charCount = 0;

  for (int i = 0; i < length; i++){
    char c = line[i];
    switch (c) {
    case 'a': case 'A': case 'e': case 'E': case 'i': case 'I': 
    case 'o': case 'O': case 'u': case 'U':
      vowelCount++;
      charCount++;
      break;
    case ' ': case '!': case '?': case ',': case '.': case ';': case ':':
      break;
    default:
      charCount++;
    }
  }
  return (vowelCount/charCount);
}
