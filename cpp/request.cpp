#include <string>
#include <sstream>
#include <iostream>
#include <list>
#include <fstream>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Infos.hpp>

#include <json/json.h>

using namespace std;
string getLocation(string header);

std::string g_headers;

size_t HeaderCallback(char* ptr, size_t size, size_t nmemb)
{
    int totalSize = size * nmemb;
    g_headers += string(ptr, totalSize);
    return totalSize;
}

/** 
 * This example is made to show you how you can use the Options.
 */
Json::Value request(string url, string token)
{
	try
	{
		curlpp::Cleanup myCleanup;
		{
          ostringstream os;
          list<string> headers;
		  headers.push_back("Authorization: Bearer "+token); 
		  curlpp::options::Url myUrl(url+"?per_page=100");
		  curlpp::options::HttpHeader myHeaders(headers);
		  curlpp::options::WriteStream ws(&os);
		  curlpp::Easy myRequest;
		  myRequest.setOpt(myUrl);
		  myRequest.setOpt(myHeaders);
		  myRequest.setOpt(ws);
		  
		  myRequest.perform();

		  os << myRequest;
           Json::Value root;
		   Json::Reader reader;
		   bool parsingSuccessful = reader.parse( os.str(), root );
			if ( !parsingSuccessful )
			{
				cout << "Error parsing the string" << endl;
			}
            return root;
		}
	}

	catch( curlpp::RuntimeError &e )
	{
		cout << e.what() << endl;
	}

	catch( curlpp::LogicError &e )
	{
		cout << e.what() << endl;
	}
    return Json::Value();
}

bool download(Json::Value item, std::string token)
{
	try
	{
		curlpp::Cleanup myCleanup;
		{
		//   cout << item << endl;
          ofstream os(item.get("filename","").asString());
		  ostringstream ss;
		  if(os.fail()){
			return false;
		  }
          list<string> headers;
		  headers.push_back("Authorization: Bearer "+token); 
		  curlpp::options::Url myUrl(item.get("url","").asString());
		  curlpp::options::HttpHeader myHeaders(headers);
		  curlpp::options::WriteStream ws(&ss);
		  curlpp::Easy myRequest;
		  myRequest.setOpt(myUrl);
		  myRequest.setOpt(myHeaders);
		  myRequest.setOpt(ws);
		  myRequest.setOpt(new curlpp::options::Header(1));

		  myRequest.perform();
		  int code = curlpp::infos::ResponseCode::get(myRequest);
		  ss << myRequest;
		  string header = ss.str();
		  curlpp::Easy myRequest2;
		  while(code == 302){
			string location = getLocation(header);
			// cout <<"Following redirect " << location<<endl;
			curlpp::options::WriteStream ws1(&ss);
		  	
		  	myRequest2.setOpt(curlpp::options::Url(location));
		  	myRequest2.setOpt(myHeaders);
		  	myRequest2.setOpt(ws1);
		    myRequest2.setOpt(new curlpp::options::HeaderFunction(HeaderCallback));

		  	myRequest2.perform();
			code = curlpp::infos::ResponseCode::get(myRequest2);
			if(code!=302){
				// cout << "-----------------------"<< code << endl;
				break;
			}
			header = g_headers;
		  }
		  
			os << myRequest2;
			cout << item.get("filename","").asString() << endl;
          return true;
		}
	}

	catch( curlpp::RuntimeError &e )
	{
		cout << e.what() << endl;
	}

	catch( curlpp::LogicError &e )
	{
		cout << e.what() << endl;
	}
    return false;
}

string getLocation(string header){
	istringstream sss(header);
	string s;
	while(sss >> s){
		// cout << "HH - - "<< s << endl;
		if(s.find("location:")==0)
		break;
	}
	sss >> s;
	return s;
}