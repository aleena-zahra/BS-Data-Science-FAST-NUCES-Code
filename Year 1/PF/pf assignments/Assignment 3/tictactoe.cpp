 // Aleena Zahra BDS-1B 23i-2514
#include<iostream>
using namespace std; 
int main() {
int c, player = 1;
char r, ch; 
bool draw = false, game_over = false, assigned;
char a1 = '_', a2 = '_', a3 = '_', b1 = '_', b2 = '_', b3 = '_', c1 = '_', c2 = '_', c3 = '_';

  while (!game_over && !draw) { 
   assigned = false;
   if (player == 1) 
   ch = 'X'; 
   else 
   ch = 'O';

   cout << "  1 2 3\n";
   cout << "A " << a1 << ' ' << a2 << ' ' << a3 << endl;
   cout << "B " << b1 << ' ' << b2 << ' ' << b3 << endl;
   cout << "C " << c1 << ' ' << c2 << ' ' << c3 << endl;
   cout << endl;

   while (!assigned) {
			cout << "Player " << player << " (" << ch << "):\n";
			cout << "Enter your desired row (A,B,C): "; cin >> r;
			while (r < 'A' || r > 'C' && r < 'a' || r > 'c') {
				cout << "INVALID ENTRY! ";
				cout << "Enter your desired row (A,B,C): "; cin >> r;
			}
			cout << "Enter your desired column: "; cin >> c;
			while (c < 1 || c > 3) {
				cout << "INVALID ENTRY! ";
				cout << "Enter your desired column: "; cin >> c;
			}

			// character assignment
if (r == 'A' || r == 'a') {
if (c == 1) {
if (a1 == '_') {
a1 = ch; 
assigned = true;
}
					else 
					cout << "SLOT ALREADY TAKEN!\n";
				}
				else if (c == 2) {
					if (a2 == '_') {
					a2 = ch; 
					assigned = true;
					}
					else 
					cout << "SLOT ALREADY TAKEN!\n";
				}
				else {
					if (a3 == '_') {
						a3 = ch; assigned = true;
					}
					else cout << "SLOT ALREADY TAKEN!\n";
				}
			}

			if (r == 'B' || r == 'b') {
				if (c == 1) {
					if (b1 == '_') {
						b1 = ch; assigned = true;
					}
					else cout << "SLOT ALREADY TAKEN!\n";
				}
				else if (c == 2) {
					if (b2 == '_') {
						b2 = ch; assigned = true;
					}
					else cout << "SLOT ALREADY TAKEN!\n";
				}
				else {
					if (b3 == '_') {
						b3 = ch; assigned = true;
					}
					else cout << "SLOT ALREADY TAKEN!\n";
				}
			}

			if (r == 'C' || r == 'c') {
				if (c == 1) {
					if (c1 == '_') {
						c1 = ch; assigned = true;
					}
					else cout << "SLOT ALREADY TAKEN!\n";
				}
				else if (c == 2) {
					if (c2 == '_') {
						c2 = ch; assigned = true;
					}
					else cout << "SLOT ALREADY TAKEN!\n";
				}
				else {
					if (c3 == '_') {
						c3 = ch; assigned = true;
					}
					else cout << "SLOT ALREADY TAKEN!\n";
				}
			}
		}

		// row-wise iteration
		if (a1 == ch && a2 == ch && a3 == ch) game_over = true;
		if (b1 == ch && b2 == ch && b3 == ch) game_over = true;
		if (c1 == ch && c2 == ch && c3 == ch) game_over = true;

		// column-wise iteration
		if (a1 == ch && b1 == ch && c1 == ch) game_over = true;
		if (a2 == ch && b2 == ch && c2 == ch) game_over = true;
		if (a3 == ch && b3 == ch && c3 == ch) game_over = true;

		// cross iteration
		if (a1 == ch && b2 == ch && c3 == ch) game_over = true;
		if (a3 == ch && b2 == ch && c1 == ch) game_over = true;

		// draw iteration
		if (!game_over && a1 != '_' && a2 != '_' && a3 != '_' && b1 != '_' && b2 != '_' && b3 != '_' && c1 != '_' && c2 != '_' && c3 != '_') {
			draw = true;
		}
		
		if (game_over) cout << "\nPLAYER " << player << " IS THE WINNER!\n";
		else if (draw) cout << "\nDRAW!\n";
		else {
			if (player == 1) player++;
			else player--;
		}

cout << endl;
}

return 0;
}


