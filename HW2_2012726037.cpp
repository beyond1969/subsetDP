#include<iostream>
#include<string>
#include<vector>
#define ARRAYSIZE 12

using namespace std;

int sum_array(const vector<int>&, int);
void counting_case(vector<int>&, int);
void make_subSets(const vector<int>&, int, int, vector<vector<bool>>&, vector<bool>&);
void choose_element(const vector<int>&, int, int, const vector<vector<bool>>&, vector<bool>&);

bool B_ISZERO = false;

int main() {
	while (true) {
		int i_size = 0;
		int input_set = 0;

		/* �Է� �κ� */
		cin >> i_size;
		if (i_size == 0) {
			break;
		}
		vector<int> i_nums;
		i_nums.reserve(sizeof(int)*i_size);
		int tmp = 0;
		while (tmp < i_size) {
			cin >> input_set;
			i_nums.push_back(input_set);
			tmp++;
		}

		unsigned int i_sum = 0;			// ����
		unsigned int i_sumHalf = 0;		// ������ ����

		vector<bool> b_isSubsetExist(i_size, false);

		i_sum = sum_array(i_nums, i_size);	// ���� ���ϱ�
		// ������ ������ ¦���� �ƴҰ�� ����
		if (i_sum % 2 != 0) {
			cout << "Cannot divide two subset!" << endl;
			continue;
		}

		i_sumHalf = i_sum / 2;		// ������ ���� ���ϱ�

		counting_case(i_nums, i_sumHalf);	// �κ����� ����� �� ���ϱ�

		vector<vector<bool>> b_subSets(i_sumHalf + 1, vector<bool>(i_size + 1));
		make_subSets(i_nums, i_size, i_sumHalf, b_subSets, b_isSubsetExist);

		/* �κ����� ��� */
		if (B_ISZERO == true) {
			continue;
		}
		else {
			cout << "{ ";
			for (int i = 0; i < i_size; i++) {
				if (b_isSubsetExist[i] != false) {
					cout << i_nums[i] << " ";
				}
			}
			cout << " }";
			cout << " / ";
			cout << "{ ";
			for (int i = 0; i < i_size; i++) {
				if (b_isSubsetExist[i] != true) {
					cout << i_nums[i] << " ";
				}
			}
			cout << " }" << endl;
		}
	}

	return 0;
}

int sum_array(const vector<int>& nums, int size) {
	int result = 0;
	
	for (int i = 0; i < size; i++)
		result += nums.at(i);

	return result;
}

void counting_case(vector<int>& nums, int bound) {
	int result = 0;
	int sum = bound;
	int w = 0;
	int i, j;
	unsigned long caseCount = 0;

	vector<unsigned long> P(sum + 1, 0);	// 0 ���� �ʱ�ȭ�� sum+1 ũ�� ����

	P[0] = 1;	// ���� 0 �� ���� 1����

	for (i = 0; i < nums.size(); i++) {
		w += nums[i];						// w += wi
		if (sum <= w) {
			j = sum;
		}
		else {
			j = w;
		}
		while (j >= nums[i]) {
			if (ULONG_MAX - P[j - nums[i]]/2 < P[j]/2) {
				cout << "NUMOROUS!" << endl;
				return;
			}
			P[j] += P[j - nums[i]];		// P[i][j] += P[i][w-wi]
			j--;
		}
	}
	// ���� ����� ���δٸ� �κ������� �� ���� �̹Ƿ� ����� ���� �� �����̴�.
	result = P[sum] / 2;

	cout << result << endl;

	if (result == 0)
		B_ISZERO = true;

	return;
}

void make_subSets(const vector<int>& nums, int size, int bound, vector<vector<bool>>& subSets, vector<bool>& isSubsetExist) {
	for (int i = 0; i <= size; i += 1) {
		subSets[0][i] = true;
	}

	for (int i = 1; i <= bound; i += 1) {
		subSets[i][0] = false;
	}

	for (int i = 1; i <= bound; i += 1) {
		for (int j = 1; j <= size; j += 1) {
			subSets[i][j] = subSets[i][j - 1];
			if (i >= nums[j - 1]) {
				subSets[i][j] = subSets[i][j] || subSets[i - nums[j - 1]][j - 1];
			}
		}
	}

	if (subSets[bound][size]) {
		choose_element(nums, size, bound, subSets, isSubsetExist);
	}

	return;
}

void choose_element(const vector<int>& nums, int size, int bound, const vector<vector<bool>>& subSets, vector<bool>& isSubsetExist) {
	int i;
	if (bound == 0) {
		return;
	}
	for (i = 0; i < size; i++) {
		if (subSets[bound][i + 1]) {
			break;
		}
	}
	isSubsetExist[i] = true;
	choose_element(nums, size, bound - nums[i], subSets, isSubsetExist);
}