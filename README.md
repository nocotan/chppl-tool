# chppl-tool
[![MIT License](http://img.shields.io/badge/license-MIT-blue.svg?style=flat)](LICENSE)  
C/C++ package manager for header only, single file library  
like Python pip or Ruby gems  
[chppL](https://chppl.herokuapp.com/)  


##Install

```
$ cd  
$ git clone https://github.com/nocotan/chppl-tool  
$ echo "export PATH=\$PATH:~/chppl-tool/chppl-tool/bin" >> ~/.bashrc
```  


##Usage   

###Show help commands
```$ chppl help```

###Search package  
```$ chppl search```  

###Install package  
```$ chppl install <package name>```  

###Compile
```$ g++ -I$HOME/.chppl/libs test.cpp```  

##Require
```$ sudo apt-get install subversion subversion-tools```
