// homework3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int multiline_annotation_flag = 0;
ofstream token("token.txt");
ofstream symbol("symbol.txt");
ofstream err("err.txt");

bool string_end(char before_end) {
	if (before_end != ' ' && before_end != '+' && before_end != '-' && before_end != '*' && before_end != '/' && before_end != '>' && before_end != '<' && before_end != '=' && before_end != ';' && before_end != '(' && before_end != ')' && before_end != '#' && before_end != ':' && before_end != '[' && before_end != ']' && before_end != '.' && before_end != ',' && before_end != '{') {
		return true;
	}
	else
	{
		return false;
	}
}

void handle_alphabet_and_digit(string str, int line_count) {
	int decimal_flag = 0;
	//cout << "handle:------------------------" << str << endl;
	string keyword[21] = { "and","begin","const","div","do","else","end","function","if","integer","not","or","procedure","program","read","real","then","type","var","while","write" };
	for (int i = 0; i < 21; i++)
	{
		if (str == keyword[i]) {
			cout << "<" << i << "," << keyword[i] << ">" << endl;
			token << "<" << i << "," << keyword[i] << ">" << "\n";
			return;
		}
	}
	if (str == "")
	{
		cout << "err" << endl;
	}
	if ((str[0] >= 'a'&&str[0] <= ' z') || (str[0] >= 'A'&&str[0] <= 'Z'))
	{
		cout << "<21," << str << ">" << endl;
		token << "<21," << str << ">" << "\n";
		symbol << "<21," << str << ">" << "\n";
		return;
	}
	else
	{
		for (int i = 0; i < (int)str.length(); i++)
		{
			if ((str[i] >= '0'&&str[i] <= '9'))
			{

			}
			else
			{
				cout << "第" << line_count << "行错误----不符合标识符或整数的定义" << endl;
				err << "第" << line_count << "行错误----不符合标识符或整数的定义" << "\n";
				getchar();
				exit(1);
			}
		}
		cout << "<22," << str << ">" << endl;
		token << "<22," << str << ">" << "\n";
		symbol << "<22," << str << ">" << "\n";
	}
}

void handle_line(string str, int line_count) {
	cout << "input:" << str << endl;
	int begin = 0, end = 0;

	//cout << "length" << (int)str.length() << endl;

	while (begin < (int)str.length())
	{
		//cout << "---------------------" << begin << ":" << str[begin] << endl;
		if (multiline_annotation_flag == 1)
		{
			if (str[begin] == '*' && str[begin + 1] == '}')
			{
				cout << "<36,*>" << endl;
				cout << "<46,}>" << endl;
				token << "<36,*>" << "\n";
				token << "<46,}>" << "\n";
				multiline_annotation_flag = 0;
				begin++;
				begin++;
				continue;
			}
			else
			{
				begin++;
				continue;
			}
			end = begin;
		}
		//cout << end << "---" << str[ end] << endl;

		if ((str[end] >= 'a'&&str[end] <= 'z') || (str[end] >= 'A'&&str[end] <= 'Z') || (str[end] >= '0'&&str[end] <= '9'))
		{
			end++;
			continue;
		}
		else
		{
			if (str[end] == ' ')
			{
				if (end == 0)
				{
					end++;
					begin = end;
					continue;
				}
				else
				{
					if ((str[end - 1] >= 'a'&&str[end - 1] <= 'z') || (str[end - 1] >= 'A'&&str[end - 1] <= 'Z') || (str[end - 1] >= '0'&&str[end - 1] <= '9'))
					{
						handle_alphabet_and_digit(str.substr(begin, end - begin), line_count);
						end++;
						begin = end;
						continue;
					}
					else
					{
						end++;
						begin = end;
						continue;
					}
				}
			}
			else
			{
				if (str[end] == '+' || str[end] == '-' || str[end] == '*' || str[end] == '/' || str[end] == '>' || str[end] == '<' || str[end] == '=' || str[end] == ';' || str[end] == '(' || str[end] == ')' || str[end] == '#' || str[end] == ':' || str[end] == '[' || str[end] == ']' || str[end] == '.' || str[end] == ',' || str[end] == '{' || str[end] == '}')
				{
					switch (str[end])
					{
					case '{':
						if (end != 0)
						{
							if (string_end(str[end - 1]))
							{
								handle_alphabet_and_digit(str.substr(begin, end - begin), line_count);
							}
						}
						cout << "<45,{>" << endl;
						token << "<45,{>" << "\n";
						if (str[end + 1] != '*')
						{
							while (end <= (int)str.length())
							{
								if (str[end] == '}')
								{
									cout << "<46,}>" << endl;
									token << "<46,}>" << "\n";
									end++;
									begin = end;
								}
								else
								{
									end++;
								}
							}
						}
						else
						{
							cout << "<36,*>" << endl;
							token << "<36,*>" << "\n";
							end++;
							begin = end;
							multiline_annotation_flag = 1;
						}
						break;
					case ',':
						if (string_end(str[end - 1]))
						{
							handle_alphabet_and_digit(str.substr(begin, end - begin), line_count);
						}
						cout << "<23,,>" << endl;
						token << "<23,,>" << "\n";
						end++;
						begin = end;
						break;
					case ';':
						if (string_end(str[end - 1]))
						{
							handle_alphabet_and_digit(str.substr(begin, end - begin), line_count);
						}
						cout << "<24,;>" << endl;
						token << "<24,;>" << "\n";
						end++;
						begin = end;
						break;
					case '(':
						if (string_end(str[end - 1]))
						{
							handle_alphabet_and_digit(str.substr(begin, end - begin), line_count);
						}
						cout << "<27,(>" << endl;
						token << "<27,(>" << "\n";
						end++;
						begin = end;
						break;
					case ')':
						if (string_end(str[end - 1]))
						{
							handle_alphabet_and_digit(str.substr(begin, end - begin), line_count);
						}
						cout << "<28,)>" << endl;
						token << "<28,)>" << "\n";
						end++;
						begin = end;
						break;
					case '[':
						if (string_end(str[end - 1]))
						{
							handle_alphabet_and_digit(str.substr(begin, end - begin), line_count);
						}
						cout << "<29,[>" << endl;
						token << "<29,[>" << "\n";
						end++;
						begin = end;
						break;
					case ']':
						if (string_end(str[end - 1]))
						{
							handle_alphabet_and_digit(str.substr(begin, end - begin), line_count);
						}
						cout << "<30,]>" << endl;
						token << "<30,]>" << "\n";
						end++;
						begin = end;
						break;
					case '+':
						if (string_end(str[end - 1]))
						{
							handle_alphabet_and_digit(str.substr(begin, end - begin), line_count);
						}
						cout << "<34,+>" << endl;
						token << "<34,+>" << "\n";
						end++;
						begin = end;
						break;
					case '-':
						if (string_end(str[end - 1]))
						{
							handle_alphabet_and_digit(str.substr(begin, end - begin), line_count);
						}
						cout << "<35,->" << endl;
						token << "<35,->" << "\n";
						end++;
						begin = end;
						break;
					case '*':
						if (string_end(str[end - 1]))
						{
							handle_alphabet_and_digit(str.substr(begin, end - begin), line_count);
						}
						cout << "<36,*>" << endl;
						token << "<36,*>" << "\n";
						end++;
						begin = end;
						break;
					case '/':
						if (string_end(str[end - 1]))
						{
							handle_alphabet_and_digit(str.substr(begin, end - begin), line_count);
						}
						cout << "<37,/>" << endl;
						token << "<37,/>" << "\n";
						end++;
						begin = end;
						break;
					case '=':
						if (string_end(str[end - 1]))
						{
							handle_alphabet_and_digit(str.substr(begin, end - begin), line_count);
						}
						cout << "<38,=>" << endl;
						token << "<38, =>" << "\n";
						end++;
						begin = end;
						break;
					case '#':
						if (string_end(str[end - 1]))
						{
							handle_alphabet_and_digit(str.substr(begin, end - begin), line_count);
						}
						cout << "<47,#>" << endl;
						token << "<47,#>" << "\n";
						end++;
						begin = end;
						break;
					case ':':
						if (str[end + 1] == '=')
						{
							if (string_end(str[end - 1]))
							{
								handle_alphabet_and_digit(str.substr(begin, end - begin), line_count);
							}
							cout << "<44,:=>" << endl;
							token << "<44,:=>" << "\n";
							end++;
							end++;
							begin = end;
						}
						else
						{
							if (string_end(str[end - 1]))
							{
								handle_alphabet_and_digit(str.substr(begin, end - begin), line_count);
							}
							cout << "<25,:>" << endl;
							token << "<25,:>" << "\n";
							end++;
							begin = end;
						}
						break;
					case '.':
						if (str[end + 1] == '.')
						{
							if (string_end(str[end - 1]))
							{
								handle_alphabet_and_digit(str.substr(begin, end - begin), line_count);
							}
							cout << "<31,..>" << endl;
							token << "<31,..>" << "\n";
							end++;
							end++;
							begin = end;
						}
						else
						{
							if (string_end(str[end - 1]))
							{
								handle_alphabet_and_digit(str.substr(begin, end - begin), line_count);
							}
							cout << "<26,.>" << endl;
							token << "<26,.>" << "\n";
							end++;
							begin = end;
						}
						break;
					case '<':
						if (str[end + 1] == '=')
						{
							if (string_end(str[end - 1]))
							{
								handle_alphabet_and_digit(str.substr(begin, end - begin), line_count);
							}
							cout << "<42,<=>" << endl;
							token << "<42,<=>" << "\n";
							end++;
							end++;
							begin = end;
						}
						else
						{
							if (str[end + 1] == '>')
							{
								if (string_end(str[end - 1]))
								{
									handle_alphabet_and_digit(str.substr(begin, end - begin), line_count);
								}
								cout << "<41,<>>" << endl;
								token << "<41,<>>" << "\n";
								end++;
								end++;
								begin = end;
							}
							else
							{
								if (string_end(str[end - 1]))
								{
									handle_alphabet_and_digit(str.substr(begin, end - begin), line_count);
								}
								cout << "<39,<>" << endl;
								token << "<39,<>" << "\n";
								end++;
								begin = end;
							}
						}
						break;
					case '>':
						if (str[end + 1] == '=')
						{
							if (string_end(str[end - 1]))
							{
								handle_alphabet_and_digit(str.substr(begin, end - begin), line_count);
							}
							cout << "<43,>=>" << endl;
							token << "<43,>=>" << "\n";
							end++;
							end++;
							begin = end;
						}
						else
						{
							if (string_end(str[end - 1]))
							{
								handle_alphabet_and_digit(str.substr(begin, end - begin), line_count);
							}
							cout << "<40,>>" << endl;
							token << "<40,>>" << "\n";
							end++;
							begin = end;
						}
						break;
					default:
						break;
					}
				}
				else
				{
					if (end >= (int)str.length()) {
						handle_alphabet_and_digit(str.substr(begin, end - begin), line_count);
						begin = end;
						//cout << "--------------------" << endl;
					}
					else
					{
						cout << "第" << line_count << "行错误----出现无法识别的字符" << endl;
						err << "第" << line_count << "行错误----出现无法识别的字符" << "\n";
						getchar();
						exit(1);
					}
				}
			}
		}
	}
}

int main()
{
	char line[100] = { 0 };
	string str, substr;



	string filename;
	cout << "请输入文件名:";
	cin >> filename;
	ifstream input(filename);
	int line_count = 1;
	while (!input.eof())
	{
		input.getline(line, 100);
		str = line;
		handle_line(str, line_count);
		line_count++;
	}


	getchar();
	system("pause");

	return 0;
}
