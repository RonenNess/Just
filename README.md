# JUST

A simple headers-only library with misc utilities and super-simple functions to make your life easier.

There's nothing too sophisticated about this lib; Its just a set of useful functions for prototyping and tests which are usually tedious to write. JUST help you just do it.

* Note: made for Windows, many of the functions won't work on posix.

## How To Use

This is a headers-only library, meaning you don't need to build any dlls or lib to use. Simply include the files from `Just/Source/` in your project and you're set to go.

## API Overview

Lets take a look at a quick example, the following code will invoke Http GET and write the returned HTML to file:

```C
auto html = Just::Http::HttpGet("google.com", 80).Text;
Just::Files::WriteTextFile("google.html", html);
```

Pretty easy eh? Lets take a quick look at the different APIs JUST provide:

### Files

Utilities to read, write and manage files.

```cpp
Just::Files::CreatePath(testFolder + "output/foo/bar");

bool exists = Just::Files::FileExists("some_file");

Just::Files::WriteTextFile(testFolder + "temp.txt", "hello world!"));
```

### DLLs

Dynamically load dlls and methods.

```cpp
Just::DLLs::LoadDLL("some_lib.dll");
```

### Execute

Functions to execute files and scripts.

```cpp
auto ret = Just::Execute::ExecuteCommand("TestEcho.exe");
bool success = ret.IsSuccess();
```

### Http

Functions to send different Http requests.

```cpp
auto html = Just::Http::HttpGet("google.com", 80);
if (html.good()) {
	auto htmlText = html.Text;
}
```

### Strings/ToString

Convert different types to string.

```cpp
std::list<int> _list; _list.push_back(1); _list.push_back(2); _list.push_back(3);
auto listAsString = Just::ToString::ListToString(_list, ",");

std::map<int, const char*> _dict; _dict[1] = "a"; _dict[2] = "b"; _dict[3] = "c";
auto dictAsString = Just::ToString::MapToString(_dict, ":", ",");
```

### Strings/Convert

Convert different type of strings.

```cpp
LPCWSTR converted;
StringConvert::StringToLPCWSTR(originText, converted);
// do stuff...
delete[] converted;
```

### SharedMemory

Create and use shared memory.

```cpp
Just::SharedMemory::SharedMemoryClient sm1;
Just::SharedMemory::SharedMemoryClient sm2;

sm1.CreateNew("test", 100);
sm2.Connect("test", 100);

sm1.WriteInt(10132);
int temp = 0;
sm2.ReadInt(temp);

sm1.WriteChar(10);
char temp = 0;
sm2.ReadChar(temp);

sm1.WriteBool(true);
bool temp = false;
sm2.ReadBool(temp);

sm1.WriteStr(LPCWSTR(L"hello world"));
TCHAR* temp = new TCHAR[50];
sm2.ReadStr(temp, 12);
```

## License

JUST is distributed with the MIT license, use it for whatever purpose you like.
