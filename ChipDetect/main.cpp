#include <iostream>
#include <cstdlib>
#include <ctime>
#include "ChipDetect.h"

using std::cout;
using std::endl;

int main()
{
	const int n = 101;
	Chip c[n];

	srand((int)time(0));

	for (int i = 0; i < 51; ++i) {
		c[i].id = i;
		c[i].q = Chip::CHIP_GOOD;
	}

	for (int i = 51; i < n; ++i) {
		c[i].id = i;
		c[i].q = Chip::CHIP_BAD;
	}

	for (int i = 0; i < n-1; ++i) {
		int j = random(i, n-1);
		if (j < i || j > n - 1) cout << "random fail" << endl;
		Chip t = c[i];
		c[i] = c[j];
		c[j] = t;
		cout << c[i].id << "\t" << c[i].q << endl;
	}

	int good_id = ChipDetect(c, n);

	cout << good_id << endl;

	return 0;
}
