/*
������ B2. ������ �� Z-�������.

����� �����������������-����������� ������, ����������� �� z-�������, � �������� a-z.
*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
using namespace std;
char get_min_permitted( const set<char> &banned ) {
	// ���������� ����������� ������, �� ������������ ���������,
	// ������� ������������� ����� ����� ��� (st - ����� ����������� �������� �����������)
	char res = 'b'; // �� ����� ���� 'a', ����� Zf[]!=0, �������������� ������ 0
	while( banned.find( res ) != banned.end( ) && res < 'z' ) res ++; // ���� 'z' ���� ���
	return res;
}
string BuildString( const vector<int> &Zf ) {
	int index = 1, base = 1, size = Zf.size( ); // index - ������� ������������ ������,
	// base - ������ ������� ���������� ������� - Zf[base] �������� (� ����� ������� ������ base+Zf[base]-1)
	string res = "a";
	vector<set<char>> Banned( size ); // ����������� ������� � ������� - ��������������
	// ��������� Z-������� �������������� ������
	while( index < size ) {
		if( Zf[ index ] + index - base >= Zf[ base ] ) { // ���������� ��� ����������� ���������� �������
			base = index;
			// ���������� �����������-����������� ��������� (���������� ������������ �������)
			if( base + Zf[ base ] < size ) Banned[ base + Zf[ base ] ].insert( res[ Zf[ base ] ] );
		}
		if( index - base + 1 <= Zf[ base ] ) res += res[ index-base ]; // ����������� ����������� ��������
		else res += get_min_permitted( Banned[ index ] ); // Zf[]=0 ����� � ������������ � ������ ������ �������
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
