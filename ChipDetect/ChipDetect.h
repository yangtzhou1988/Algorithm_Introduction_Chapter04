#ifndef _CHIP_DETECT_H_
#define _CHIP_DETECT_H_

#include <cstdlib>
#include <ctime>

inline int random(int x)
{
	return rand() % x;
}

inline int random(int x, int y)
{
	return (x + random(y-x+1));
}

enum ChipPairResult {
	GHIP_PAIR_GOOD_GOOD,
	GHIP_PAIR_GOOD_BAD,
	GHIP_PAIR_BAD_GOOD,
	GHIP_PAIR_BAD_BAD
};

class Chip
{
public:
	enum Quality {CHIP_GOOD = 0, CHIP_BAD = 1};

	int get_id() const { return id; }

public:
	int id;
	Quality q;

	//friend ChipPairResult CompareChipPair(Chip &a, Chip &b);
};

ChipPairResult ChipPairCompare(Chip &a, Chip &b)
{
	srand((int)time(0));

	if (a.q == Chip::CHIP_GOOD && b.q == Chip::CHIP_GOOD)
		return GHIP_PAIR_GOOD_GOOD;
	else if (a.q == Chip::CHIP_BAD && b.q == Chip::CHIP_BAD) {
		int r = random(4);
		switch (r) {
		case 0:
			return GHIP_PAIR_GOOD_GOOD;
		case 1:
			return GHIP_PAIR_BAD_BAD;
		case 2:
			return GHIP_PAIR_GOOD_BAD;
		case 3:
			return GHIP_PAIR_BAD_GOOD;
		default:
			return GHIP_PAIR_GOOD_GOOD;
		}
	}
	else {
		int r = random(3);
		switch (r) {
		case 0:
			return GHIP_PAIR_BAD_BAD;
		case 1:
			return GHIP_PAIR_GOOD_BAD;
		case 2:
			return GHIP_PAIR_BAD_GOOD;
		default:
			return GHIP_PAIR_BAD_BAD;
		}
	}
}

int ChipDetect(Chip t1[], Chip t2[], int n)
{
	if (n == 1)
		return t1[0].get_id();

	int remain_num = 0;

	for (int i = 0; i < n - 1; i += 2) {
		if (ChipPairCompare(t1[i], t1[i+1]) == GHIP_PAIR_GOOD_GOOD)
			t2[remain_num++] = t1[i];
	}

	if (n % 2 != 0 && remain_num % 2 == 0)
		t2[remain_num++] = t1[n-1];

	return ChipDetect(t2, t1, remain_num);
}

int ChipDetect(Chip c[], int n)
{
	if (c == NULL || n < 1)
		return -1;

	Chip *t1 = new Chip[n];
	Chip *t2 = new Chip[n];

	for (int i = 0; i < n; ++i)
		t1[i] = c[i];

	int good_id = ChipDetect(t1, t2, n);

	delete[] t1;
	delete[] t2;
	return good_id;
}

#endif // _CHIP_DETECT_H_
