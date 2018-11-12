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

### DLLs

Dynamically load dlls and methods.

### Execute

Functions to execute files and scripts.

### Http

Functions to send different Http requests.

### Strings/ToString

Convert different types to string.

### Strings/Convert

Convert different type of strings.

### SharedMemory

Create and use shared memory.


## License

JUST is distributed with the MIT license, use it for whatever purpose you like.
