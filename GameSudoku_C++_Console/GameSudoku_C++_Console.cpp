#include<ctime> 
#include<iomanip> 
#include<string> 
#include<iostream> 
#include <conio.h>
#include <Windows.h>
#include<fstream>

using namespace std;
struct Pos
{
	int x;
	int y;
};
struct Ñorners
{
	int left_bottom;
	int left_top;
	int right_top;
	int right_bottom;
	int ht_line;
	int wl_line;
	int hb_line;
	int wr_line;
};
void SetPos(int x, int y) {
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_ERROR_HANDLE), c);
}
void SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
class Sqrt {
private:
	int height;
	int width;
	void print_line(int x, int y, int width, int start, int stop, int ind) {
		SetPos(x, y); cout << (char)start;
		for (int i = 0; i < width; i++)
		{
			cout << (char)ind;
		}
		cout << (char)stop;
	}
	void print_column(int x, int y, int height, int start, int stop, int ind) {
		SetPos(x, y); cout << (char)start << endl;
		for (int i = 1; i < height + 1; i++)
		{
			SetPos(x, y + i);
			cout << (char)ind << endl;
		}
		SetPos(x, y + height + 1); cout << (char)stop << endl;
	}
public:
	Sqrt(int height_, int width_) {
		height = height_;
		width = width_;
	}
	void print_sqrt(int x, int y, int left_bottom, int left_top, int right_top, int right_bottom, int ht_line, int wl_line, int hb_line, int wr_line, int color = 7) {
		SetColor(color);
		print_line(x, y, width, left_top, right_top, ht_line);
		print_column(x, y, height, left_top, left_bottom, wl_line);
		print_line(x, y + height + 1, width, left_bottom, right_bottom, hb_line);
		print_column(x + width + 1, y, height, right_top, right_bottom, wr_line);
		SetColor(10);
	}
};
class Sudoku_Table : protected Sqrt
{
private:
	Ñorners cor_top[9] = {
		{199,201,209,197,205,186,196,179},{197,209,209,197,205,179,196,179},{197,209,203,215,205,179,196,186},
		{215,203,209,197,205,186,196,179},{197,209,209,197,205,179,196,179},{197,209,203,215,205,179,196,186},
		{215,203,209,197,205,186,196,179},{197,209,209,197,205,179,196,179},{197,209,187,215,205,179,196,186}
	};
	Ñorners cor_green[9] = {
		{199,199,197,197,196,186,196,179},{197,197,197,197,196,179,196,179},{197,197,215,215,196,179,196,186},
		{215,215,197,197,196,186,196,179},{197,197,197,197,196,179,196,179},{197,197,215,215,196,179,196,186},
		{215,215,197,197,196,186,196,179},{197,197,197,197,196,179,196,179},{197,197,182,182,196,179,196,186}
	};
	Ñorners cor_yellow[9] = {
		{204,199,197,216,196,186,205,179},{216,197,197,216,196,179,205,179},{216,197,215,206,196,179,205,186},
		{206,215,197,216,196,186,205,179},{216,197,197,216,196,179,205,179},{216,197,215,206,196,179,205,186},
		{206,215,197,216,196,186,205,179},{216,197,197,216,196,179,205,179},{216,197,182,185,196,179,205,186}
	};
	Ñorners cor_red[9] = {
		{199,204,216,197,205,186,196,179},{197,216,216,197,205,179,196,179},{197,216,206,215,205,179,196,186},
		{215,206,216,197,205,186,196,179},{197,216,216,197,205,179,196,179},{197,216,206,215,205,179,196,186},
		{215,206,216,197,205,186,196,179},{197,216,216,197,205,179,196,179},{197,216,185,182,205,179,196,186}
	};
	Ñorners cor_bottom[9] = {
		{200,199,197,207,196,186,205,179},{207,197,197,207,196,179,205,179},{207,197,215,202,196,179,205,186},
		{202,215,197,207,196,186,205,179},{207,197,197,207,196,179,205,179},{207,197,215,202,196,179,205,186},
		{202,215,197,207,196,186,205,179},{207,197,197,207,196,179,205,179},{207,197,182,188,196,179,205,186}
	};
	Ñorners cor[9][9];
	Pos pos;
	Pos pos_cursor = { 4, 4 };
	int height;
	int width;
	void add_to() {
		for (int i = 0; i < 9; i++)
		{
			cor[0][i] = cor_top[i];
			cor[1][i] = cor_green[i];
			cor[2][i] = cor_yellow[i];
			cor[3][i] = cor_red[i];
			cor[4][i] = cor_green[i];
			cor[5][i] = cor_yellow[i];
			cor[6][i] = cor_red[i];
			cor[7][i] = cor_green[i];
			cor[8][i] = cor_bottom[i];
		}
	}
public:
	Sudoku_Table(Pos pos_, int height_, int width_) : Sqrt(height_, width_)
	{
		pos.x = pos_.x;
		pos.y = pos_.y;
		height = height_;
		width = width_;
		add_to();
	}
	void print() {
		for (int i = 0, stepy = 0; i < 9; i++, stepy += (height + 1))
		{
			for (int j = 0, stepx = 0; j < 9; j++, stepx += (width + 1))
			{
				print_sqrt(pos.x + stepx, pos.y + stepy,
					cor[i][j].left_bottom, cor[i][j].left_top, cor[i][j].right_top, cor[i][j].right_bottom,
					cor[i][j].ht_line, cor[i][j].wl_line, cor[i][j].hb_line, cor[i][j].wr_line);
			}
		}
	}
	void print_last() {
		const int x = pos_cursor.x;
		const int y = pos_cursor.y;
		print_sqrt(pos.x + ((width + 1) * x), pos.y + ((height + 1) * y),
			cor[y][x].left_bottom, cor[y][x].left_top, cor[y][x].right_top, cor[y][x].right_bottom,
			cor[y][x].ht_line, cor[y][x].wl_line, cor[y][x].hb_line, cor[y][x].wr_line);
	}
	void print_cursor() {
		print_sqrt(pos.x + ((width + 1) * pos_cursor.x), pos.y + ((height + 1) * pos_cursor.y),
			200, 201, 187, 188, 205, 186, 205, 186, 9);
	}
	void set_cursor(char s) {
		print_last();
		switch (s)
		{
		case 'a':
			if (pos_cursor.x > 0) {
				pos_cursor.x--;
			}
			break;
		case 'd':
			if (pos_cursor.x < 8) {
				pos_cursor.x++;
			}
			break;
		case 'w':
			if (pos_cursor.y > 0) {
				pos_cursor.y--;
			}
			break;
		case 's':
			if (pos_cursor.y < 8) {
				pos_cursor.y++;
			}
			break;
		}
		print_cursor();
	}
	Pos get_cursor() { return pos_cursor; }
};
class Sudoku {
private:
	int height;
	int width;
	int complexity = 2;
	int mistakes = 0;
	int number_available = 0;
	int number_not_available = 0;
	Pos pos;
	const char base[9][9] = {
		{'3','6','2','5','8','4','9','1','7'},{'5','4','7','2','1','9','3','6','8'},{'8','9','1','7','6','3','2','4','5'},
		{'2','7','8','6','4','5','1','3','9'},{'1','5','9','3','2','7','4','8','6'},{'6','3','4','8','9','1','5','7','2'},
		{'7','8','5','1','3','2','6','9','4'},{'4','1','6','9','5','8','7','2','3'},{'9','2','3','4','7','6','8','5','1'}
	};
	char real[9][9] = {};
	char out[9][9] = {};
	void copy_base_real() {
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				real[i][j] = base[i][j];
			}
		}
	}
	void SwapColumns(int col1, int col2) {
		if (col1 == col2) return;
		if (col1 < 0 || col2 < 0 || col1 >= 9 || col2 >= 9) return;

		for (int i = 0; i < 9; i++) {
			std::swap(real[i][col1], real[i][col2]);
		}
	}
	void SwapRows(int row1, int row2) {
		if (row1 == row2) return;
		if (row1 < 0 || row2 < 0 || row1 >= 9 || row2 >= 9) return;

		for (int i = 0; i < 9; i++) {
			std::swap(real[row1][i], real[row2][i]);
		}
	}
	void SwapColumnBlocks(int col1, int col2) {
		if (col1 == col2) return;
		if (col1 < 0 || col2 < 0 || col1 >= 3 || col2 >= 3) return;

		int icol1 = col1 * 3 + 2;
		for (int i = col1 * 3, j = col2 * 3; i <= icol1; i++, j++) {
			SwapColumns(i, j);
		}
	}
	void SwapRowBlocks(int row1, int row2) {
		if (row1 == row2) return;
		if (row1 < 0 || row2 < 0 || row1 >= 3 || row2 >= 3) return;

		int irow1 = row1 * 3 + 2;
		for (int i = row1 * 3, j = row2 * 3; i <= irow1; i++, j++) {
			SwapRows(i, j);
		}
	}
	int Rand(int start, int stop, int notVal) {
		int val;
		do {
			val = start + (rand() % (stop - start));
		} while (val == notVal);
		return val;
	}
	void mix_real() {
		for (int i = 0; i < 3; i++) 
		{
			int jr = Rand(0, 3, i);
			SwapRowBlocks(jr, i);
			int jc = Rand(0, 3, i);
			SwapColumnBlocks(jc, i);
		}
		for (int block = 0; block < 3; block++) 
		{
			int start = block * 3, stop = block * 3 + 3;
			for (int i = start; i < stop; i++) {
				int jr = Rand(start, stop, i);
				SwapRows(jr, i);
				int jc = Rand(start, stop, i);
				SwapColumns(jc, i);
			}
		}
	}
	void copy_real_out() {
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				out[i][j] = real[i][j];
			}
		}
	}
	void cut_out() {
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (!(rand() % (complexity + 1)))
				{
					out[i][j] = '0';
				}
			}
		}
	}
	void print_out(Pos pos_, int courrect_number = 0) {
		char temp = '0';
		this->number_available = 0;
		this->number_not_available = 0;
		if (out[pos_.y][pos_.x] != '0') {
			temp = out[pos_.y][pos_.x];
		}
		for (int i = 0, stepy = 0; i < 9; i++, stepy += (height + 1))
		{
			for (int j = 0, stepx = 0; j < 9; j++, stepx += (width + 1))
			{
				SetPos(pos.x + stepx, pos.y + stepy);
				if (out[i][j] != '0') {
					number_available++;
					if (temp == out[i][j]) {
						SetColor(9);
					}
					cout << out[i][j];
				}
				else {
					number_not_available++;
				}
				SetColor(10);
			}
		}
	}
	void print_statistics() {
		const int x = pos.x - (width / 2 + 1);
		const int y = pos.y + (height * 2 * 9);
		SetPos(x, y + 1); cout << "Complexity : " << complexity;
		SetPos(x, y + 2); cout << "Mistakes : " << mistakes;
		SetPos(x, y + 3); cout << "81/" << number_available << "/" << number_not_available;
	}
public:
	Sudoku(Pos sydoky, int height_, int width_) {
		height = height_;
		width = width_;
		pos.x = sydoky.x + (width / 2 + 1);
		pos.y = sydoky.y + (height / 2 + 1);
	}
	void generate() {
		copy_base_real();
		mix_real();
		copy_real_out();
		cut_out();
	}
	void update(Pos pos_) {
		print_out(pos_);
		print_statistics();
	}
	void set_value(char s, Pos pos_cursor) {
		const int x = pos_cursor.x;
		const int y = pos_cursor.y;
		SetPos(pos.x + ((width + 1) * x), pos.y + ((height + 1) * y));
		if (real[y][x] == s) {
			out[y][x] = s;
		}
		else {
			SetColor(4);
			if (!(out[y][x] == real[y][x])) {
				mistakes++;
			}
		}
		cout << s;
		SetColor(10);
	}
	bool verify_all() {
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (out[i][j] == '0')
				{
					return false;
				}
			}
		}
		return true;
	}
	void set_complexity() {
		cout << endl;
		while (true)
		{
			cout << "Enter complexity (1 - 5) >> ";
			cin >> complexity;
			if (complexity >= 1 && complexity <= 5)
			{
				break;
			}
		}
	}
	void clear_q(Pos cursor) {
		const int y = cursor.y;
		const int x = cursor.x;
		if (out[cursor.y][cursor.x] == '0')
		{
			SetPos(pos.x + ((width + 1) * x), pos.y + ((height + 1) * y));
			cout << " ";
		}
		else {

		}
	}
	int get_complexity() { return complexity; }
	int get_mistakes() { return mistakes; }
};
void game_loop() {
	const Pos GLOBAL_sydoky = { 0, 0 };
	const int height = 1;
	const int width = 3;
	// init
	Sudoku_Table sudoku_Table(GLOBAL_sydoky, height, width);
	Sudoku sudoku(GLOBAL_sydoky, height, width);
	char s;
	// 
	sudoku.set_complexity();
	// set
	system("cls");
	// start
	sudoku_Table.print();
	sudoku_Table.set_cursor('0');
	sudoku.generate();
	sudoku.update(sudoku_Table.get_cursor());
	// loop
	const int start = time(0);
	while (true)
	{
		SetPos(0, 0);
		s = _getch();
		switch (s)
		{
		case 'a':
		case 's':
		case 'd':
		case 'w':
			sudoku_Table.set_cursor(s);
			break;
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			sudoku.set_value(s, sudoku_Table.get_cursor());
			break;
		case 'q':
			sudoku.clear_q(sudoku_Table.get_cursor());
			break;
		case '0':
			return;
			break;
		}
		sudoku.update(sudoku_Table.get_cursor());
		if (sudoku.verify_all())
		{
			break;
		}
	}
	const int stop = time(0);
	const int total = stop - start;
	int complexity = sudoku.get_complexity();
	int mistakes = sudoku.get_mistakes();
	system("cls");
	int timem = total / 60;
	int timec = total % 60;
	cout << "Your results" << endl;
	cout << " complexity : " << complexity << " mistakes : " << mistakes << " total_time : " << timem << ":" << timec << endl;
	system("pause");
}
void menu_loop() {
	char s;
	while (true)
	{
		system("cls");
		cout << "r - Start game" << endl;
		cout << "0 - Out" << endl;
		cout << " >> ";
		s = _getch();
		switch (s)
		{
		case 'r':
			game_loop();
			break;
		case '0':
			return;
			break;
		}
	}
}
void main()
{
	srand(time(0));
	menu_loop();
	exit(0);
}
