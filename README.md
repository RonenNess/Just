# JUST

A simple headers-only micro library with misc utilities and functions to make your life easier. 

The library was mostly made for Windows, so many of the functions won't work on posix. 
Make sure `_WIN32` is not set to exclude everything that is windows-specific when building for linux.

## How To Use

This is a headers-only library, meaning you don't need to build anything to use it. 
Simply include the specific files you want from `Just/Source/` if you only need specific parts, or include `JustAll.h` if you want everything.

## API Overview

Lets take a look at a quick example. 
The following code will send an Http GET request to google and write the returned HTML to a text file:

```C
auto html = Just::Http::Get("google.com", 80).Text;
Just::Files::WriteText("google.html", html);
```

Pretty easy eh? Lets take a quick look at the different APIs JUST provides. 
From every API set we'll only include one or two examples, to see more methods check out the source files.

### Files

Utilities to read, write and manage files.

```cpp
// create recursive path of folders
Just::Files::CreatePath(testFolder + "output/foo/bar");

// check if file exists
bool exists = Just::Files::Exists("some_file");

// write text file
Just::Files::WriteText(testFolder + "temp.txt", "hello world!"));
```

### DLLs

Dynamically load a dll file.

```cpp
Just::DLLs::Load("some_lib.dll");
```

### Execute

Execute commands, files and scripts.

```cpp
auto ret = Just::Execute::Command("TestEcho.exe");
bool success = ret.IsSuccess();
```

### Http

Send Http requests.

```cpp
auto html = Just::Http::Get("google.com", 80);
if (html.good()) {
	auto htmlText = html.Text;
}
```

### Strings::From

Parse different types to strings.

```cpp
std::list<int> _list; _list.push_back(1); _list.push_back(2); _list.push_back(3);
auto listAsString = Just::String::From::Iterable(_list, ",");

std::map<int, const char*> _dict; _dict[1] = "a"; _dict[2] = "b"; _dict[3] = "c";
auto dictAsString = Just::String::From::Map(_dict, ":", ",");
```

### Strings::To

Convert between different types of strings.

```cpp
LPCWSTR converted;
Just::String::To::LpcwStr(originText, converted);
// do stuff...
delete[] converted;
```

### SharedMemory

Create and use shared memory.

```cpp
Just::SharedMemory::Client sm1;
Just::SharedMemory::Client sm2;

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

JUST is distributed with the MIT license. Use it for whatever.
