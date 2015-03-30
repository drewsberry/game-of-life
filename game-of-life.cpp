#include <iostream>
#include <vector>
using namespace std;

class GameOfLife {
public:
	int width, height;
	vector<vector<int> > values;
	GameOfLife(int, int);
	~GameOfLife();

	void print();
	void set_alive(int, int);
	void set_dead(int, int);
	int num_neighbours(int, int);
	void step();
};

GameOfLife::GameOfLife(int w, int h)
{
	width = w;
	height = h;

	vector<int> subvec;

	for (int j = 0; j < h; j++) {
		subvec.push_back(0);
	}

	for (int i = 0; i < w; i++) {
		values.push_back(subvec);
	}

	cout << "Game created." << endl;
}

GameOfLife::~GameOfLife()
{
	cout << "Game deleted." << endl;
}

void GameOfLife::print()
{
	cout << "Game grid values: " << endl;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (values[i][j] == 1) {
				cout << "1";
			}
			else {
				cout << " ";
			}
			if (j != height - 1) {
				cout << ",";
			}
		}
		cout << endl;
	}
}

void GameOfLife::set_dead(int i, int j)
{
	values[i][j] = 0;
}

void GameOfLife::set_alive(int i, int j)
{
	values[i][j] = 1;
}

int GameOfLife::num_neighbours(int i, int j)
{
	int num_neighbours = 0;

	int i_from_ind = i - 1;
	int i_to_ind = i + 1;
	int j_from_ind = j - 1;
	int j_to_ind = j + 1;

	if (i == 0) {
		i_from_ind = i;
	}
	if (i == width) {
		i_to_ind = i;
	}
	if (j == 0) {
		j_from_ind = j;
	}
	if (j == height) {
		j_to_ind = j;
	}

	for (int ind_one = i_from_ind; ind_one < i_to_ind; ind_one++) {
		for (int ind_two = j_from_ind; ind_two < j_to_ind; ind_two++) {
			if (values[i][j] == 1) {
				num_neighbours++;
			}
		}
	}

	return num_neighbours;
}

void GameOfLife::step()
{
	GameOfLife gameclone = GameOfLife(*this);

	for (int i = 0; i < gameclone.width; i++) {
		for (int j = 0; j < gameclone.height; j++) {
			int num_neigh_alive = num_neighbours(i, j);

			if (num_neigh_alive < 2 || num_neigh_alive > 3) {
				gameclone.values[i][j] = 0;
			}
			else if (num_neigh_alive == 3) {
				gameclone.values[i][j] = 1;
			}
		}
	}

	values = gameclone.values;
}

int main()
{
	int myheight, mywidth;
	cout << "Enter grid height: "; cin >> myheight;
	cout << "Enter grid width: "; cin >> mywidth;

	GameOfLife mygame = GameOfLife(mywidth, myheight);

	cout << "Please select a cell to bring alive: ";
	int cell_x, cell_y;
	cin >> cell_x;
	cin >> cell_y;
	mygame.set_alive(cell_x, cell_y);

	cout << "Please select another cell to bring alive: ";
	cin >> cell_x;
	cin >> cell_y;
	mygame.set_alive(cell_x, cell_y);

	mygame.print();

	cout << "Game successfully initialised." << endl;

	cout << "Moving onto next step..." << endl;
	mygame.step();
	mygame.print();

	cout << "Moving onto next step..." << endl;
	mygame.step();
	mygame.print();

	cout << "Moving onto next step..." << endl;
	mygame.step();
	mygame.print();
}
