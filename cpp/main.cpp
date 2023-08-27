#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <filesystem>

#include <json/json.h>
#include "request.hpp"
#include "utils.hpp"
#include "multiLang.hpp"

using namespace std;
string selectModule(Json::Value modules);
vector<int> selectItem(Json::Value items);
int getKey();
void print(string str);

int LANG_IDX = 2;

int main(int argc, char **argv, char **envp)
{
	multiLang::init();
	print(multiLang::get(LANG_IDX, "_cls")+multiLang::get(LANG_IDX, "_title"));
	print(multiLang::get(LANG_IDX, "step0"));
	print(multiLang::get(LANG_IDX, "_dash"));
	string home = getenv("HOME");
	ifstream tokenF(home + "/.canvas_token");
	string token;
	if (tokenF.fail())
	{
		print(multiLang::get(LANG_IDX, "tokenFail"));
		token = createTokenFile();
	} else
	{
		tokenF >> token;
	}
	tokenF.close();
	Json::Value res = request("https://ucsb.instructure.com/api/v1/courses/12433/modules", token);
	string url = selectModule(res);
	if (url.length() < 5)
	{
		cerr << multiLang::get(LANG_IDX, "moduleUrlFail") << endl;
		exit(1);
	}
	res = request(url, token);
	vector<int> items = selectItem(res);
	print(multiLang::get(LANG_IDX, "_cls")+multiLang::get(LANG_IDX, "_title"));
	print(multiLang::get(LANG_IDX, "step3"));
	print(multiLang::get(LANG_IDX, "filesDownloaded"));
	print(multiLang::get(LANG_IDX, "_dash"));
	for (int i = 0; i < items.size(); i++)
	{
		Json::Value r = request(res[items[i]].get("url", "").asString(), token);
		// cout << r << endl;
		download(r, token);
	}
	print(multiLang::get(LANG_IDX, "_dash"));
	print(multiLang::get(LANG_IDX, "fileLocation"));
	print(std::filesystem::current_path());
	return 0;
}

string selectModule(Json::Value modules)
{
	int key = 0, sel = 0;
	while (key != '\r')
	{
		if (key == 0x1b)
		{
			print(multiLang::get(LANG_IDX, "aborted"));
			exit(0);
		}
		if (key == 'w')
		{
			if (sel > 0)
				sel -= 1;
			else
				sel = modules.size() - 1;
		}
		else if (key == 's')
		{
			if (sel >= modules.size() - 1)
				sel = 0;
			else
				sel += 1;
		}
		print(multiLang::get(LANG_IDX, "_cls")+multiLang::get(LANG_IDX, "_title"));
		print(multiLang::get(LANG_IDX, "step1"));
		print(multiLang::get(LANG_IDX, "_dash"));
		for (int idx = 0; idx < modules.size(); idx++)
		{
			if (idx == sel)
				cout << multiLang::get(LANG_IDX, "_sel") << modules[idx].get("name", "").asString() << multiLang::get(LANG_IDX, "_noStyle") << endl;

			else
				cout << modules[idx].get("name", "").asString() << endl;
		}

		print(multiLang::get(LANG_IDX, "_dash"));
		print(multiLang::get(LANG_IDX, "moduleSel"));
		print(multiLang::get(LANG_IDX, "_ddsh"));
		key = getKey();
	}
	return modules[sel].get("items_url", "").asString();
}

vector<int> selectItem(Json::Value items)
{
	int key = 0, sel = 0;
	vector<int> selArr;
	while (items[sel].get("type", "").asString() != "File")
	{
		if (sel >= items.size() - 1)
		{
			print(multiLang::get(LANG_IDX, "noFileInModule"));
			exit(1);
		}
		else
			sel += 1;
	}

	while (key != '\r')
	{
		if (key == 0x1b)
		{
			print(multiLang::get(LANG_IDX, "aborted"));
			exit(0);
		}
		if (key == 'w')
		{
			if (sel > 0)
				sel -= 1;
			else
				sel = items.size() - 1;
			while (items[sel].get("type", "").asString() != "File")
			{
				if (sel > 0)
					sel -= 1;
				else
					sel = items.size() - 1;
			}
		}
		else if (key == 's')
		{
			if (sel >= items.size() - 1)
				sel = 0;
			else
				sel += 1;
			while (items[sel].get("type", "").asString() != "File")
				if (sel >= items.size() - 1)
					sel = 0;
				else
					sel += 1;
		}
		else if (key == 'a')
		{
			vector<int>::iterator it = find(selArr.begin(), selArr.end(), sel);
			if (it == selArr.end())
				selArr.push_back(sel);
		}
		else if (key == 'd')
		{
			vector<int>::iterator it = find(selArr.begin(), selArr.end(), sel);
			if (it != selArr.end())
			{
			}
			selArr.erase(it);
		}
		print(multiLang::get(LANG_IDX, "_cls")+multiLang::get(LANG_IDX, "_title"));
		print(multiLang::get(LANG_IDX, "step2"));
		print(multiLang::get(LANG_IDX, "_dash"));
		// for (int i: selArr)
		// 	cout << i << ' ';
		for (int idx = 0; idx < items.size(); idx++)
		{
			Json::Value item = items[idx];
			if (item.get("type", "").asString() == "SubHeader")
				print(multiLang::get(LANG_IDX, "_subColor") + item.get("title", "").asString() + multiLang::get(LANG_IDX, "_noStyle"));
			else if (item.get("type", "").asString() == "File")
			{
				vector<int>::iterator it = find(selArr.begin(), selArr.end(), idx);
				if (it != selArr.end())
					print(multiLang::get(LANG_IDX, "_down") + (idx == sel ? "-> " : "     ") + item.get("title", "").asString() + multiLang::get(LANG_IDX, "_noStyle"));
				else
					print((idx == sel ? "-> " : "     ") + item.get("title", "").asString());
			}
		}

		print(multiLang::get(LANG_IDX, "_dash"));
		print(multiLang::get(LANG_IDX, "itemSel"));
		print(multiLang::get(LANG_IDX, "_ddsh"));
		key = getKey();
	}
	return selArr;
}

int getKey()
{
	system("stty raw");
	char c = getchar();
	// terminate when "." is pressed
	system("stty cooked");
	cout << "\r" << endl;
	// system("clear");
	return c;
}

void print(string str)
{
	cout << str << endl;
}