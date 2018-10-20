// Just.cpp : Defines the entry point for the console application.
// This file is used as a quick-test of *most* of JUST features.

#include "stdafx.h"
#include "Source/Just.h"
#include <map>
#include <iostream>
using namespace std;

int main()
{
	cout << "About to do some tests on JUST. Note: these tests does not cover 100% of API. Its just basic stuff." << endl;

	string testFolder = "__testing/";
	cout << "Test files API..." << endl;

	// test creating folders
	if (!Just::Files::CreatePath(testFolder + "output/foo/bar"))
		cout << "	Error in creating folder!" << endl;

	// test basic files API
	if (Just::Files::FileExists("__testing/aaaaaaaaa")) 
		cout << "	Error in testing if file exists - got false positive!" << endl;
	if (Just::Files::FileExists(testFolder)) 
		cout << "	Error in testing if file exists - detected directory as file!" << endl;
	if (!Just::Files::WriteTextFile(testFolder + "temp.txt", "aaa")) 
		cout << "	Error in writing text file!" << endl;
	if (!Just::Files::FileExists(testFolder + "temp.txt")) 
		cout << "	Error in testing if file exists - failed to detect an existing file!" << endl;

	// test HTTP API
	cout << "Test HTTP API..." << endl;
	auto html = Just::Http::HttpGet("google.com", 80);
	if (!html.good())
		cout << "	Error in Http GET from google: " << html.Error << " - are you connected to internet?" << endl;

	// test executing API
	cout << "Test Executing API..." << endl;
	Just::Execute::ProcessOutput ret = Just::Execute::ExecuteCommand("TestEcho.exe");
	if (!ret.DidFinish || ret.ReturnCode != 0) 
		cout << "	Error in executing command. Code: " << ret.ReturnCode << endl;

	ret = Just::Execute::ExecuteCommand("TestEcho.exe foo");
	if (!ret.DidFinish || ret.ReturnCode != 0) 
		cout << "	Error in executing command with params. Code: " << ret.ReturnCode << endl;
	if (ret.Output != "Echo: foo\n") 
		cout << "	Error in getting output from executed command!" << endl;

	// test To String API
	cout << "Test ToString API..." << endl;
	std::list<int> _list; _list.push_back(1); _list.push_back(2); _list.push_back(3);
	if (Just::ToString::ListToString(_list, ",") != "1,2,3")  
		cout << "	Error in converting list to string!" << endl;

	std::vector<int> _vec; _vec.push_back(1); _vec.push_back(2); _vec.push_back(3);
	if (Just::ToString::ListToString(_vec, ",") != "1,2,3")  
		cout << "	Error in converting vector to string!" << endl;

	int _arr[3]{ 1,2,3 };
	if (Just::ToString::ArrayToString(_arr, 3, ",") != "1,2,3")
		cout << "	Error in converting array to string!" << endl;

	std::map<int, const char*> _dict; _dict[1] = "a"; _dict[2] = "b"; _dict[3] = "c";
	if (Just::ToString::MapToString(_dict, ":", ",") != "1:a,2:b,3:c")
		cout << "	Error in converting map to string!" << endl;

	// done testing
	cout << "Done!" << endl;
}
