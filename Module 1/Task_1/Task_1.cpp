/*
������ �. ����� ���������.

������� ��� ��������� ������� � ������.
������� ��� ��������� ������� � ������. ����� ������� � p, ����� ������ � n. ����� O(n + p), ���. ������ � O(p).
p <= 30000, n <= 300000.

������ �����
������, ������ �������� ������, ������.

������ ������
������� ��������� ������� � ������.
*/
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;
void CountZ( vector<int> &Zf, const string &p, const string &s, int &left, int &right ) {
	// � ������ ������������ �������������� p � s � ������ (���� ������ ������� ������)
	// ������ ��������� Z-������� �� ������ p, � ��������� ������ ������������ Zf ��� ������
	// ��������� ������� p � s � ������ ��������������� ��������
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
	// ����� � ����� ���� ��������� ������� � ������ �� O(p+s)
	int slen = s.length( ), plen = p.length( );
	if( plen > slen ) return;
	int left = 0, right = 0;
	vector<int> Zf( plen ); // ������� Z-������� ��� �������� p ������ p+s (p � s ��������� ������ ����������� ��������) - ������ O(p)
	CountZ( Zf, p, p, left, right ); // ������� Z-������� ��� p
	left -= plen; // ������� � ������ "������� ��������"
	right -= plen; // ������ ������� ������
	CountZ( Zf, p, s, left, right ); // ����� ��������� ������� p � ������ s
}
int main( ) {
	string p, s;
	cin >> p >> s;
	FindPattern( p, s );
	return 0;
}
