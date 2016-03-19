#include <iostream>

using std::cout;
using std::endl;

/****** Naive Max Subarray ******/

int NaiveMaxSubarray(int d[], int n, int &max_left, int &max_right)
{
	if (n < 1 || d == NULL) {
		max_left = max_right = -1;
		return 0;
	}

	int max_sum = d[0];
	max_left = 0;
	max_right = 0;
	int sum;

	for (int i = 0; i < n; ++i) {
		sum = 0;
		for (int j = i; j < n; ++j) {
			sum += d[j];
			if (sum > max_sum) {
				max_sum = sum;
				max_left = i;
				max_right = j;
			}
		}
	}

	return max_sum;
}

/****** Divide and Conquer Max Subarray ******/

int MaxCrossSubarray(int d[], int low, int mid, int high, int &max_left, int &max_right)
{
	int left_max_sum = d[mid];
	max_left = mid;
	int sum = 0;

	for (int i = mid; i >= low; --i) {
		sum += d[i];
		if (sum > left_max_sum) {
			left_max_sum = sum;
			max_left = i;
		}
	}

	int right_max_sum = d[mid+1];
	max_right = mid + 1;
	sum = 0;

	for (int i = mid + 1; i <= high; ++i) {
		sum += d[i];
		if (sum > right_max_sum) {
			right_max_sum = sum;
			max_right = i;
		}
	}

	return (left_max_sum + right_max_sum);
}

int DivideMaxSubarray(int d[], int n, int &max_left, int &max_right)
{
	if (n < 1 || d == NULL) {
		max_left = max_right = -1;
		return 0;
	}

	if (n == 1) {
		max_left = 0;
		max_right = 0;
		return d[0];
	}
	else {
		int mid = (n - 1) / 2;
		int left_left, left_right, right_left, right_right, cross_left, cross_right;

		int left_max_sum = DivideMaxSubarray(d, mid + 1, left_left, left_right);
		int right_max_sum = DivideMaxSubarray(d + mid + 1, n - mid - 1, right_left, right_right);
		int cross_max_sum = MaxCrossSubarray(d, 0, mid, n - 1, cross_left, cross_right);

		if (left_max_sum >= right_max_sum && left_max_sum >= cross_max_sum) {
			max_left = left_left;
			max_right = left_right;
			return left_max_sum;
		}
		else if (right_max_sum >= left_max_sum && right_max_sum >= cross_max_sum) {
			max_left = right_left;
			max_right = right_right;
			return right_max_sum;
		}
		else {
			max_left = cross_left;
			max_right = cross_right;
			return cross_max_sum;
		}
	}
}

/****** Linear Max Subarray ******/

int LinearMaxSubarray(int d[], int n, int &max_left, int &max_right)
{
	if (n < 1 || d == NULL) {
		max_left = max_right = -1;
		return 0;
	}

	int cur_sum = d[0];
	int cur_left = 0;
	int max_sum = d[0];
	max_left = 0;
	max_right = 0;

	for (int i = 1; i < n; ++i) {
		if (cur_sum < 0) {
			cur_sum = d[i];
			cur_left = i;
		}
		else
			cur_sum += d[i];

		if (cur_sum > max_sum) {
			max_sum = cur_sum;
			max_left = cur_left;
			max_right = i;
		}
	}

	return max_sum;
}

int main()
{
	int a[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
	int max_left, max_right, max_sum;

	//max_sum = NaiveMaxSubarray(a, sizeof(a)/sizeof(int), max_left, max_right);
	//max_sum = DivideMaxSubarray(a, sizeof(a)/sizeof(int), max_left, max_right);
	max_sum = LinearMaxSubarray(a, sizeof(a)/sizeof(int), max_left, max_right);

	cout << max_left << " ~ " << max_right << ": (";
	for (int i = max_left; i <= max_right; ++i) {
		cout << a[i];
		if (i < max_right) cout << ", ";
	}
	cout << ") sum = " << max_sum << endl;

	return 0;
}
