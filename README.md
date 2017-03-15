# chppl-tool

[![MIT License](http://img.shields.io/badge/license-MIT-blue.svg?style=flat)](LICENSE)
[![Website](https://img.shields.io/website-up-down-green-red/http/shields.io.svg?maxAge=2592000)](http://chppl.herokuapp.com/)
[![GitHub issues](https://img.shields.io/github/issues/nocotan/chppl-tool.svg)](https://github.com/nocotan/chppl-tool/issues) [![GitHub stars](https://img.shields.io/github/stars/nocotan/chppl-tool.svg)](https://github.com/nocotan/chppl-tool/stargazers) 
[![GitHub release](https://img.shields.io/github/release/qubyte/rubidium.svg?maxAge=2592000)](https://github.com/nocotan/chppl-tool) 
[![GitHub commits](https://img.shields.io/github/commits-since/SubtitleEdit/subtitleedit/3.4.7.svg?maxAge=2592000)](https://github.com/nocotan/chppl-tool)

[![Twitter](https://img.shields.io/twitter/url/https/github.com/nocotan/chppl-tool.svg?style=social)](https://twitter.com/intent/tweet?text=Wow:&url=%5Bobject%20Object%5D)

C/C++ package manager for header only, single file library  
like Python pip or Ruby gems  
[chppL](https://chppl.herokuapp.com/)  


## Install

```
$ cd  
$ git clone https://github.com/nocotan/chppl-tool  
$ cd chppl-tool/chppl-tool/src
$ make
$ echo "export PATH=$PATH:~/chppl-tool/chppl-tool/bin" >> ~/.bashrc
```  


## Usage   

### Show help commands
```$ chppl help```

### Search package  
```$ chppl search <package name>```  

### Install package  
```$ chppl install <package name>```  

### Download package
```$ chppl download <package name>```

### Compile
```$ g++ -I$HOME/.chppl/libs test.cpp```  

## Require
### Linux
```$ sudo apt-get install subversion subversion-tools postgresql postgresql-server-dev-9.3```
