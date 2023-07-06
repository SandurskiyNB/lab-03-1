#include<iostream>
#include<vector>
//#include<algorithm>
using namespace std;
const double FREAK_LIMIT = 70;
const int MAX_MINUS_COUNT = 78;
const int SYMB_COUNT = 5;
const int END_INDENT_COUNT = 3;

// ������� ���������� ������� ��������� �������
vector<double> input_numbers(int numbers_count) {
	vector<double> numbers(numbers_count);
	for (int i = 0; i < numbers_count; i++) {
		cin >> numbers[i];
	}
	return numbers;
}

// ������� ������ �������� � ��������� ����� �����
void find_minmax(vector<double> numbers, const int numbers_count, double& min, double& max) {
	min = numbers[0];
	max = numbers[0];
	for (int i = 1; i < numbers_count; i++)
		if (numbers[i] < min)
			min = numbers[i];
		else
			if (numbers[i] > max)
				max = numbers[i];
}

// ������� ���������� ������ ������
vector<int> make_histogram(vector<double> numbers, const int numbers_count, const int sections_count) {

	// ����� ������������� � ������������ �����
	double min_value, max_value;
	find_minmax(numbers, numbers_count, min_value, max_value);

	// ���������� �������������� ��������� ����� ��������� � ���������� ������� ��� ���������� ���-�� ����� � ��������
	double separate_interval = (max_value - min_value) / sections_count;
	vector<int> freak_sections(sections_count);
	for (int i = 0; i < sections_count; i++)
		freak_sections[i] = 0;

	// ������� ���-�� ����� � ��������
	for (int i = 0; i < numbers_count; i++) { // ������ �� ���� ������
		double left_bord = min_value; // ������� ��������� ����� ������� ���������
		double right_bord = min_value + separate_interval; // ������� ��������� ������ ������� ���������
		bool odds_max_value = true; // ����������, �����������, ����� �� ����� ���� ������������ �� ������ ����� ����������
		for (int j = 0; j < sections_count; j++) { // ������ �� ��������
			if (numbers[i] >= left_bord && numbers[i] < right_bord) { // ���� ����� �������� � �������
				freak_sections[j]++; // �������� ������� �������
				odds_max_value = false; // ����� ����� �� ������������, ��� ��� ������ � ������� ������ ���������
				break; // ����� �� ����� ������� �� ��������
			}
			left_bord += separate_interval; // ��������� ����� ������� ���������
			right_bord += separate_interval; // ��������� ������ ������� ���������
		}
		if (odds_max_value) // ���� ����� �� ������ �� � ���� ������� �����, �������������, ��� �������� ������������
			freak_sections[sections_count - 1]++; // ��������� ������� ������� �������
	}
	return freak_sections; // ������� ������� ������ ������
}

// ������� ����������� ������������
void show_histogram(vector<int> freak_sections, const int sections_count) {

	// ����� ����������� �������
	int max_freak = freak_sections[0];
	for (int i = 1; i < sections_count; i++)
		if (freak_sections[i] > max_freak)
			max_freak = freak_sections[i];

	// ���������, ����� �� ���������������
	bool scaling;
	if (max_freak > FREAK_LIMIT)
		scaling = true;
	else
		scaling = false;

	// ������ ������� ����� �����
	cout << "\n+";
	int minus_count;
	if (scaling)
		minus_count = MAX_MINUS_COUNT;
	else
		minus_count = max_freak + SYMB_COUNT + END_INDENT_COUNT;
	for (int i = 0; i < minus_count; i++)
		cout << "-";
	cout << "+\n";

	// ������ �����������
	for (int i = 0; i < sections_count; i++) {

		cout << "|";

		// ������ ������ �������
		if (freak_sections[i] < 10)
			cout << "   ";
		else
			if (freak_sections[i] < 100)
				cout << "  ";
			else
				cout << " ";
		cout << freak_sections[i] << "|";

		// ������ ��������
		int stars_count;
		if (scaling)
			stars_count = freak_sections[i] / (max_freak / FREAK_LIMIT);
		else
			stars_count = freak_sections[i];
		for (int j = 0; j < stars_count; j++)
			cout << "*";

		// ������ �������� ����� ��������
		int spaces_count = minus_count - stars_count - SYMB_COUNT;
		for (int i = 0; i < spaces_count; i++)
			cout << " ";

		cout << "|\n";
	}

	// ������ ������ ����� �����
	cout << "+";
	for (int i = 0; i < minus_count; i++)
		cout << "-";
	cout << "+\n";
}

int main() {

	setlocale(LC_ALL, "Russian");

	// ���� ���������� �����
	int numbers_count;
	cout << "������� ���-�� �����: ";
	cin >> numbers_count;

	// ���������� ������� �������
	cout << "������� �����:\n";
	const auto numbers = input_numbers(numbers_count);

	// ���� ���������� ������ � �������� ������� ������ �� ������ ���������
	double sections_count;
	cout << "������� ��-�� ������: ";
	cin >> sections_count;
		
	vector<int> freak_sections = make_histogram(numbers, numbers_count, sections_count);

	show_histogram(freak_sections, sections_count);
}