// Just.cpp : Defines the entry point for the console application.
// This file is used as a quick-test of *most* of JUST features.

#include "stdafx.h"
#include "JustAll.h"
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
	if (Just::Files::Exists("__testing/aaaaaaaaa")) 
		cout << "	Error in testing if file exists - got false positive!" << endl;
	if (Just::Files::Exists(testFolder)) 
		cout << "	Error in testing if file exists - detected directory as file!" << endl;
	if (!Just::Files::WriteText(testFolder + "temp.txt", "aaa")) 
		cout << "	Error in writing text file!" << endl;
	if (!Just::Files::Exists(testFolder + "temp.txt")) 
		cout << "	Error in testing if file exists - failed to detect an existing file!" << endl;

	// test HTTP API
	cout << "Test HTTP API..." << endl;
	auto html = Just::Http::Get("google.com", 80);
	if (!html.good())
		cout << "	Error in Http GET from google: " << html.Error << " - are you connected to internet?" << endl;

	// test executing API
	cout << "Test Executing API..." << endl;
	Just::Execute::ProcessOutput ret = Just::Execute::Command("Tests\\TestEcho.exe");
	if (!ret.DidFinish || ret.ReturnCode != 0) 
		cout << "	Error in executing command. Code: " << ret.ReturnCode << endl;

	ret = Just::Execute::Command("Tests\\TestEcho.exe foo");
	if (!ret.DidFinish || ret.ReturnCode != 0) 
		cout << "	Error in executing command with params. Code: " << ret.ReturnCode << endl;
	if (ret.Output != "Echo: foo\n") 
		cout << "	Error in getting output from executed command!" << endl;

	// test To String API
	cout << "Test String Parse API..." << endl;
	std::list<int> _list; _list.push_back(1); _list.push_back(2); _list.push_back(3);
	if (Just::String::From::Iterable(_list, ",") != "1,2,3")
		cout << "	Error in converting list to string!" << endl;

	std::vector<int> _vec; _vec.push_back(1); _vec.push_back(2); _vec.push_back(3);
	if (Just::String::From::Iterable(_vec, ",") != "1,2,3")
		cout << "	Error in converting vector to string!" << endl;

	int _arr[3]{ 1,2,3 };
	if (Just::String::From::Array(_arr, 3, ",") != "1,2,3")
		cout << "	Error in converting array to string!" << endl;

	std::map<int, const char*> _dict; _dict[1] = "a"; _dict[2] = "b"; _dict[3] = "c";
	if (Just::String::From::Map(_dict, ":", ",") != "1:a,2:b,3:c")
		cout << "	Error in converting map to string!" << endl;

	// test Shared Memory API
	cout << "Test SharedMemory API..." << endl;
	Just::SharedMemory::Client sm1;
	Just::SharedMemory::Client sm2;
	Just::SharedMemory::Client sm3;
	Just::SharedMemory::Client sm4;
	Just::SharedMemory::Client sm5;

	if (!sm1.CreateNew("test", 100))
		cout << "	Error in creating new shared memory!" << endl;
	if (!sm1.IsValid())
		cout << "	Error in creating new shared memory (not valid)!" << endl;

	if (!sm2.Connect("test", 100))
		cout << "	Error in connecting to existing shared memory!" << endl;
	if (!sm2.IsValid())
		cout << "	Error in connecting to existing shared memory (not valid)!" << endl;

	if (!sm3.ConnectOrCreate("test", 100))
		cout << "	Error in ConnectOrCreate to existing shared memory!" << endl;

	if (!sm4.ConnectOrCreate("test2", 100))
		cout << "	Error in ConnectOrCreate to non-existing shared memory!" << endl;

	if (sm5.Connect("test3", 100))
		cout << "	Error in connecting to non-existing shared memory - returned true while should have failed!" << endl;
	if (sm5.IsValid())
		cout << "	Error in connecting to non-existing shared memory - returned valid while should be invalid!" << endl;

	// write into one memory and read in the other - int
	{
		int temp = 0;
		sm1.WriteInt(10132);
		sm2.ReadInt(temp);
		if (temp != 10132)
			cout << "	Error in reading integer form shared memory! Got value: " << temp << ", expected: 10132." << endl;
	}
	// write into one memory and read in the other - char
	{
		char temp = 0;
		sm1.WriteChar((char)10);
		sm2.ReadChar(temp);
		if (temp != 10)
			cout << "	Error in reading char form shared memory! Got value: " << temp << ", expected: 10." << endl;
	}
	// write into one memory and read in the other - bool
	{
		bool temp = false;
		sm1.WriteBool(true);
		sm2.ReadBool(temp);
		if (!temp)
			cout << "	Error in reading bool form shared memory! Got value: " << temp << ", expected: true." << endl;
	}
	// write into one memory and read in the other - str
	{
		TCHAR* temp = new TCHAR[50];
		sm1.WriteStr(LPCWSTR(L"hello world"));
		sm2.ReadStr(temp, 12);
		if (wcscmp(temp, L"hello world") != 0)
			cout << "	Error in reading str form shared memory!" << endl;
	}

	// done testing
	cout << "Done!" << endl;
}
