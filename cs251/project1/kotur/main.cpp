#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

int main(int argc, char const *argv[])
{
	if (argc != 3)
	{
		cerr << "Error: Number of Inputs is Incorrect. Exiting" << endl;
		exit(1);
	}
	ifstream in;
	ofstream out;
	in.open(argv[1]);
	out.open(argv[2]);
	if (in.is_open() && out.is_open()) {
		int n = -1;
		int x = -1;
		int num = 0;
		in >> n >> x;
		in >> num;
		out << "| " << num;
		int count = 0;
		if (num == 0) {
			count = 1;
		}
		while(num != 0) {
			num /= 10;
			count++;
		}
		for (int i = 0; i < n - count + 1; i++) {
			out << " ";
		}
		out << "|\n";
		int sum = 1;
		sum += x;
		int c = 0;
		while (in >> num) {
			out << "| " << num;
			c++;
			count = 0;
			if (num == 0) {
				count = 1;
			}
			while(num != 0) {
				num /= 10;
				count++;
			}
			for (int i = 0; i < n - count + 1; i++) {
				out << " ";
			}
			if (c == sum) {
				out << "|\n";
				sum += x;
				c = 0;
			}
		}
		if (c != 0) {
			out << "|\n";
		}
		in.close();
		out.close();
	}
	return 0;
}
