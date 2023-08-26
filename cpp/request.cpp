#include <string>
#include <sstream>
#include <iostream>
#include <list>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

#include <json/json.h>

using namespace std;

/** 
 * This example is made to show you how you can use the Options.
 */
Json::Value request(string url, string token)
{
	try
	{
		curlpp::Cleanup myCleanup;
		 
		// More elaborate example.
		{
		  // What the previous example done there was simply 
		  // to create a curlpp::Easy class, which is the basic
		  // object in cURLpp, and then set the Url option.
		  // curlpp::options classes are the primitives that allow to specify 
		  // values to the requests. 
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
		  

		  // Now that all the options we wanted to set are there, we need to
		  // actually do the request. the "perform" method does actually that.
		  // With that call, the request will be done and the content of that URL
		  // will be printed in cout (which is the default).
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