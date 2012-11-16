#include <iostream>

using namespace std;

int main(){
	float s;
	while ( cin >> s ){
		if ( s == 0.0f ){
			system("pause");
			return 0;
		}
		float totalCardLength = 0.0f;
		int cardCount = 0;
		while( totalCardLength < s ){
			++cardCount;
			totalCardLength += 1.0f / (cardCount + 1);
		}
		cout << cardCount << " " << "card(s)" << endl;
	}
}