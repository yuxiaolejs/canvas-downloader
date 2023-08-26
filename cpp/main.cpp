#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>

#include <json/json.h>
#include "request.hpp"
#include "stringConst.hpp"

using namespace std;
string selectModule(Json::Value modules);
vector<int> selectItem(Json::Value items);
int getKey();
void print(string str);

int main(int argc, char **argv, char **envp)
{   
	string home = getenv("HOME");
	ifstream tokenF(home+"/.canvas_token");
	if(tokenF.fail()){
		cerr << "[fatal] failed to load token" << endl;
		return 1;
	}
	string token;
	tokenF >> token;
	Json::Value res = request("https://ucsb.instructure.com/api/v1/courses/12433/modules", token);
	string url = selectModule(res);
	if(url.length()<5){
		cerr << "[fatal] failed to get url of module" << endl;
		exit(1);
	}
	res = request(url, token);
	vector<int> items = selectItem(res);
	return 0;
}

string selectModule(Json::Value modules){
	int key = 0, sel = 0;
	while(key!='\r'){
		if(key==0x1b){
			print("Aborted");
			exit(0);
		}
		if(key == 'w'){
			if(sel>0)
				sel-=1;
			else
				sel = modules.size()-1;
		}
		else if(key=='s'){
			if(sel>=modules.size()-1)
				sel = 0;
			else
				sel+=1;
		}
		print(_cls+_titl);
		print("Step 1/3: Select a module");
		print(_dash);
		for(int idx = 0; idx < modules.size(); idx++){
			if(idx==sel)
				cout <<_sel<< modules[idx].get("name","").asString()<<_noStyle<< endl;
			
			else
				cout << modules[idx].get("name","").asString() << endl;
		}
			
		print(_dash);
		print("Press W/S to select, and Enter to confirm");
		print(_ddsh);
		key = getKey();
	}
	return modules[sel].get("items_url","").asString();
}

vector<int> selectItem(Json::Value items){
	int key = 0, sel = 0;
	vector<int> selArr;
	while(items[sel].get("type","").asString()!="File"){
		if(sel>=items.size()-1){
			print("No file found in this module");
			exit(1);
		}
		else
			sel+=1;
	}
    
	while(key!='\r'){
		if(key==0x1b){
			print("Aborted");
			exit(0);
		}		
		if(key == 'w'){
			if(sel>0)
				sel-=1;
			else
				sel = items.size()-1;
			while(items[sel].get("type","").asString()!="File"){
				if(sel>0)
					sel-=1;
				else
					sel = items.size()-1;
			}
		}
		else if(key=='s'){
			if(sel>=items.size()-1)
				sel = 0;
			else
				sel+=1;
			while(items[sel].get("type","").asString()!="File")
				if(sel>=items.size()-1)
					sel = 0;
				else
					sel+=1;
		}
		else if(key=='a'){
			vector<int>::iterator it = find(selArr.begin(), selArr.end(), sel);
			if(it==selArr.end())
				selArr.push_back(sel);
		}
		else if(key=='d'){
			vector<int>::iterator it = find(selArr.begin(), selArr.end(), sel);
			if(it!=selArr.end()){}
				selArr.erase(it);
		}
		print(_cls+_titl);
		print("Step 2/3: Select a file");
		print(_dash);
		// for (int i: selArr)
    	// 	cout << i << ' ';
		for(int idx = 0; idx < items.size(); idx++){
			Json::Value item = items[idx];
			if(item.get("type","").asString()=="SubHeader")
				print(_subColor + item.get("title","").asString() + _noStyle);
			else if(item.get("type","").asString() == "File"){
				vector<int>::iterator it = find(selArr.begin(), selArr.end(), idx);
				if(it!=selArr.end())
					print( _down + (idx==sel?"-> " : "     ") + item.get("title","").asString() + _noStyle);
				else
					print((idx==sel ? "-> " : "     ") + item.get("title","").asString());
			}
				
		}
			
		print(_dash);
		print("   W/S: Move  A: Add  D: Remove  ESC: Abort\n      Enter: Download files "+_down+"HIGHLIGHTED"+_noStyle+"");
		print(_ddsh);
		key = getKey();
	}
	return selArr;
}

int getKey(){
	system("stty raw");
	char c = getchar(); 
	// terminate when "." is pressed
	system("stty cooked");
	cout << "\r"<< endl;
	// system("clear");
	return c;
}

void print(string str){
	cout << str << endl;
}