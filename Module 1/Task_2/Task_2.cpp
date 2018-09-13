/*
Задача B2. Строка по Z-функции.

Найти лексикографически-минимальную строку, построенную по z-функции, в алфавите a-z.
*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
using namespace std;
char get_min_permitted( const set<char> &banned ) {
	// возвращает минимальный символ, не продолжающий подстроки,
	// которые заканчиваются прямо перед ним (st - набор забрещённых символов продолжения)
	char res = 'b'; // не может быть 'a', иначе Zf[]!=0, предполагается именно 0
	while( banned.find( res ) != banned.end( ) && res < 'z' ) res ++; // выше 'z' букв нет
	return res;
}
string BuildString( const vector<int> &Zf ) {
	int index = 1, base = 1, size = Zf.size( ); // index - текущий генерируемый символ,
	// base - индекс текущей копируемой области - Zf[base] префикса (с самым дальним концом base+Zf[base]-1)
	string res = "a";
	vector<set<char>> Banned( size ); // запрещённые символы в позиции - предотвращение
	// изменения Z-функции результирующей строки
	while( index < size ) {
		if( Zf[ index ] + index - base >= Zf[ base ] ) { // расширение при возможности копируемой области
			base = index;
			// запрещение префиксного-продолжения подстроки (добавление запрещённого символа)
			if( base + Zf[ base ] < size ) Banned[ base + Zf[ base ] ].insert( res[ Zf[ base ] ] );
		}
		if( index - base + 1 <= Zf[ base ] ) res += res[ index-base ]; // продолжение копирования префикса
		else res += get_min_permitted( Banned[ index ] ); // Zf[]=0 лежит в некопируемой в данный момент области
		index ++;
	}
	return res;
}
int main( ) {
	vector<int> Zf;
	int temp;
	for( ; ; ) {
		cin >> temp;
		if( cin.fail( ) ) break;
		Zf.push_back( temp );
	}
	cout << BuildString( Zf ) << endl;
	system("pause");
	return 0;
}
