#include <iostream>
#include <locale>
#include <cstdio>
#include <clocale>
using namespace std;

//초성 
static const wchar_t wcF[] = {
	L'ㄱ', L'ㄲ', L'ㄴ', L'ㄷ', 
	L'ㄸ', L'ㄹ', L'ㅁ', L'ㅂ', 
	L'ㅃ', L'ㅅ', L'ㅆ', L'ㅇ', 
	L'ㅈ', L'ㅉ', L'ㅊ', L'ㅋ', 
	L'ㅌ', L'ㅍ', L'ㅎ'}; 

//중성 
static const wchar_t wcM[] = {
	L'ㅏ', L'ㅐ', L'ㅑ', L'ㅒ', 
	L'ㅓ', L'ㅔ', L'ㅕ', L'ㅖ', 
	L'ㅗ', L'ㅘ', L'ㅙ', L'ㅚ', 
	L'ㅛ', L'ㅜ', L'ㅝ', L'ㅞ', 
	L'ㅟ', L'ㅠ', L'ㅡ', L'ㅢ', L'ㅣ'}; 

//종성 
static const wchar_t wcL[] = {
	L' ', L'ㄱ', L'ㄲ', L'ㄳ', 
	L'ㄴ', L'ㄵ', L'ㄶ', L'ㄷ', 
	L'ㄹ', L'ㄺ', L'ㄻ', L'ㄼ', 
	L'ㄽ', L'ㄾ', L'ㄿ', L'ㅀ', 
	L'ㅁ', L'ㅂ', L'ㅄ', L'ㅅ', 
	L'ㅆ', L'ㅇ', L'ㅈ', L'ㅊ', 
	L'ㅋ', L'ㅌ', L'ㅍ', L'ㅎ'}; 

// ch 가 한글인지 아닌지를 판단
bool checkHangulForDBC(const char &ch); 				// for double byte code 
bool checkHangulForUniCode(const wchar_t &ch); // for unicode

// 초성 중성 종성 분리
bool wchar_FML(const wchar_t &wc, int &F, int &M, int &L);

// 초성 중성 종성 출력
void print_FML(const wchar_t &wc);

//===========================================================

int main()
{
	setlocale(LC_ALL, "korean"); // locale setting
	wcout.imbue(locale("")); // wcout stream setting

	wstring a = L"안녕하세요.";  // 분석할 문자열
//	wchar_t a[] = L"Hello 세계!";  // 분석할 문자열

	wcout<<a<<endl;								// 입력된 문자열 확인

	for(int i = 0 ; a[i] ; i++)
		print_FML(a[i]);

	return 0;
}

//===========================================================

// ch 가 한글인지 아닌지를 판단
bool checkHangulForDBC(const char &ch) 				// for double byte code 
{
	return (ch & 0x80) == 1;							// 최상위 비트 1 인지 검사
}

bool checkHangulForUniCode(const wchar_t &ch) // for unicode
{
	return !(ch < 44032 || ch > 55199); // 0xAC00(가) ~ 0xD7A3(힣)
}

// 초성 중성 종성 분리
bool wchar_FML(const wchar_t &wc, int &F, int &M, int &L)
{
	// 한글인지 구분
	if(checkHangulForUniCode(wc))
	{
		int wc2 = (int)wc-0xAC00;
		L = wc2%28;
		wc2/=28;
		M = wc2%21;
		F = wc2/21;
		return true;
	}
	return false; // 한글이 아니면 false
}

// 초성 중성 종성 출력
void print_FML(const wchar_t &wc)
{
	int f, m, l;
	bool ret = wchar_FML(wc, f, m, l);
	if(ret)
		wcout<<wc<<" = ( "<<wcF[f]<<", "<<wcM[m]<<", "<<wcL[l]<<" )"<<endl;
	else{
		wcout<<wc<<" is not Hangul."<<endl;
	}
}
