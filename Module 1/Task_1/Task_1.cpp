/*
Задача А. Поиск подстроки.

Найдите все вхождения шаблона в строку.
Найдите все вхождения шаблона в строку. Длина шаблона – p, длина строки – n. Время O(n + p), доп. память – O(p).
p <= 30000, n <= 300000.

Формат ввода
Шаблон, символ перевода строки, строка.

Формат вывода
Позиции вхождения шаблона в строке.
*/
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;
void CountZ( vector<int> &Zf, const string &p, const string &s, int &left, int &right ) {
	// в случае идентичности местоположения p и s в памяти (одна строка послана дважды)
	// просто считается Z-функция на строке p, в противном случае используется Zf для поиска
	// вхождений шаблона p в s и вывода соответствующих индексов
	int slen = s.length( ), plen = p.length( );
	bool ident = ( &p == &s );
	if( ident ) Zf[ 0 ] = plen;
	for( int i = ( ident ? 1 : 0 ); i < slen; i ++ ) {
		if( i > right ) {
			int j;
			for( j = 0; ; j ++ ) if( j >= plen || s[ i + j ] != p[ j ] ) break;
			if( ident ) Zf[ i ] = j;
			else if( j >= plen ) cout << i << " ";
			left = i;
			right = i + j - 1;
		}
		else {
			if( right < Zf[ i - left ] + i ) {
				int j = right - i + 1;
				for( ; ; j ++ ) if( j >= plen || s[ i + j ] != p[ j ] ) break;
				if( ident ) Zf[ i ] = j;
				else if( j >= plen ) cout << i << " ";
				left = i;
				right = i + j - 1;
			}
			else{
				if( ident ) Zf[ i ] = Zf[ i - left ];
				else if( Zf[ i - left ] >= plen ) cout << i << " ";
			}
		}
	}
	if( !ident ) cout << endl;
}
void FindPattern( const string &p, const string &s ) {
	// Поиск и вывод всех вхождений шаблона в строке за O(p+s)
	int slen = s.length( ), plen = p.length( );
	if( plen > slen ) return;
	int left = 0, right = 0;
	vector<int> Zf( plen ); // рассчёт Z-функции для префикса p строки p+s (p и s разделены мнимым разделяющим символом) - память O(p)
	CountZ( Zf, p, p, left, right ); // рассчёт Z-функции для p
	left -= plen; // переход к новому "массиву символов"
	right -= plen; // старый остался позади
	CountZ( Zf, p, s, left, right ); // поиск вхождений шаблона p в строку s
}
int main( ) {
	string p, s;
	cin >> p >> s;
	FindPattern( p, s );
	return 0;
}
