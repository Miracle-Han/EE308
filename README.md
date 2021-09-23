## EE308



| The Link Your Class                            | https://bbs.csdn.net/forums/MUEE308FZ?category=0 |
| ---------------------------------------------- | :----------------------------------------------- |
| **The Link of Requirement of This Assignment** | https://bbs.csdn.net/topics/600798588            |
| **The Aim of This Assignment**                 |                                                  |
| **MU STU ID and FZU STU ID**                   | 19104375 & 831902106                             |

[TOC]

### 0. Prerequisites 

#### 0.1 Git

Before we learn to use Git, what do we need to know about **Reversion control**.

##### 0.1.1 What is Revision Control ?

**Definition:** Revision control is a software engineering technique used during development **to manage the history of changes** **made to *files***, ***directories***, ***or projects***. It can be easily viewed and backed up to restore previous versions.

**It can help us:** 

- ###### Realize cross-region multi-person collaborative development

- ###### To track and record the history of one or more files

- ###### Organize and protect your source code and documentation

- ###### Statistical workload

- ###### Parallel development, improve development efficiency

- ###### Track and record the entire software development process

- ###### Reduce developer burden, save time, and reduce human error



#### 0.2 basic operations

```
git add . # add the babababab
```
```
git commit -m"comment" # put the comment such as time, author in the comment block
```
```
git push origin main
```

download Git on https://git-scm.com/



### 1. PSP From of this LAB

| Personal Software Process Stages | Estimated Time/minutes | Completed Time/minutes |
| :------------------------------- | ---------------------: | ---------------------: |
| Planning                         |                     30 |                     45 |
| Estimate                         |                     20 |                     30 |
| Development                      |                        |                        |
| Analysis                         |                     60 |                    120 |
| Design Spec                      |                     20 |                     60 |
| Design Review                    |                      5 |                     10 |
| Coding Standard                  |                     40 |                     60 |
| Design                           |                     30 |                    120 |
| Coding                           |                    240 |                    600 |
| Code ReviewPlanning              |                     30 |                     60 |
| Test                             |                     30 |                     60 |
| Reporting                        |                     60 |                    100 |
| Test Report                      |                     60 |                     40 |
| Size Measurement                 |                     15 |                     30 |
| Postmortem&Process Improvement   |                     60 |                     30 |
| total                            |                    670 |                   1265 |

### 2. Problem-solving Ideas

#### 2.1 Program Requirements

- ###### Basic requirement: output "keyword" statistics

- ###### Advanced requirement: output the number of "switch case" structures, and output the number of "case" corresponding to each group

- ###### Uplifting requirement: output the number of "if else" structures

- ###### Ultimate requirement: output the number of "if, else if, else" structures

**Before completing the more difficult requirements, you need to complete the Lower requirements.**

#### 2.2 Personal Idea

- ##### Based on this LAB, I decided to divide it into **three parts**

1. IO
2. Split the text into keywords 
3. Find and output

![image-20210923103814967](C:\Users\admin\AppData\Roaming\Typora\typora-user-images\image-20210923103814967.png)

### 3. Implementation process

#### 3.0 Preparatory work

**Before we type "int main", we need to prepare the following things.**

- **Head file**

```c++
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
```

- **Some of the parameters**

```c++
/*for switch*/
struct CaseNum{ 
	bool activate_switch=false; 
	bool activate_brace=false; 
};

/*for case*/
CaseNum c[100];      
static int structNum =0; 
int caseArr[100] = {0};
static int casePos=0;

/*for if*/
struct The_if{
    bool hasIf = false;
	bool elseIf = false;
	bool hasElse= false;
};

The_if ifArr[100];
int ifArrPos = -1;
static int IE=0, IEE=0;
```



- ##### File Input

- The entire file needs to be read first. Use c++ file input output stream, through the Internet access to the relevant information to master the relevant usage of ***ifstream***. 


![image-20210923182629137](C:\Users\admin\AppData\Roaming\Typora\typora-user-images\image-20210923182629137.png)

- **Here is the code:**

```c++
char file_add[100];
cout << "File_name: ";
cin >> file_add;
ifstream cpp_file(file_add);  
```

- ##### Processing comments and other information

The second is to read the contents of the file. Here ***getLine*** is used to read the contents of the file **line by line** and **transpose unused strings to Spaces**.  However, before we start, **we need to determine if there is a next row.**

```c++
getline(fstream, str); // Make the content of the file into a string.
```

![image-20210923192645735](C:\Users\admin\AppData\Roaming\Typora\typora-user-images\image-20210923192645735.png)

- **Here is the code:**

```c++
while(!cpp_file.eof()){ 		
    getline(cpp_file, line); 
		for(int i=0;i<line.length();i++){
			if( ! (line[i]>='a' && line[i]<='z' || line[i]>='A'&&line[i]<='Z' || line[i]>='0' && line[i]<='9' || line[i] == '{'  				|| line[i]=='}' ||  line[i]=='_' ||line[i]=='/' || line[i]=='"'))
  			line[i]=' ';	
  	} 
    // For later convenience, we firstly transpose unused strings to Spaces. 
    
    string str;
	istringstream is(line); // Read a separate string in each line
}
```

#### 3.1 Requirements 1 - Keywords

**3.1.1 Keywords list  and Store code**

| **auto**   | **break**  | **case**     | **char**   | **const**    | **continue** | **default**  | **do**     |
| :--------- | :--------- | :----------- | :--------- | :----------- | ------------ | :----------- | :--------- |
| **double** | **else**   | **enum**     | **extern** | **float**    | **for**      | **goto**     | **if**     |
| **int**    | **long**   | **register** | **return** | **short**    | **signed**   | **sizeof**   | **static** |
| **struct** | **switch** | **typedef**  | **union**  | **unsigned** | **void**     | **volatile** | **while**  |

```c++
const string Keywords_list[32] = {"auto", "break",	"case",	"char",	"const", "continue","default",	"do",
                            "double",	"else",	"enum",	"extern", "float", "for", "goto" , "if",
                            "int",	"long",	"register",	"return", "short", "signed", "sizeof", "static",
                            "struct",	"switch",	"typedef",	"union", "unsigned", "void", "volatile", "while"};
```

**3.1.2 The number of Keywords**

- **In this section, we need to consider the interference of invalid information, i.e. <u>the non-keyword part contains keyword fragments</u>**
- So I tested the length of each string, **and only if the length and information were the same as the list keyword**, **Keywords_num++**.

![image-20210923193203793](C:\Users\admin\AppData\Roaming\Typora\typora-user-images\image-20210923193203793.png)

- **Here is the code:**

```c++
while(is >> str){
	    if(str[0]=='"'||str[0] == '/') continue; 
    	//Exclude comments and "double-quoted" text from the result
		for(int i=0; i < 32; i++){ 
			if( str.length() == keylen[i] ){
				if( str.compare(Keywords_list[i])==0 )
					Keywords_num++;
		} 
        //In this forLoop, if the length and information were the same as the list keyword, Keywords_num++, and we can get the total number of the keywords.
}
```

#### 3.2 Requirements 2 - switch and case  

- **Since the nesting of switches is not considered, the processing mechanism is simpler. The group number is determined by looking for the number of switches, and the number of cases before the next switch appears is counted as the number of cases in the group.**

![image-20210923193802137](C:\Users\admin\AppData\Roaming\Typora\typora-user-images\image-20210923193802137.png)

- **Here is the code:**

```c++
while(is >> str){
	if(str[0]=='"'||str[0] == '/') continue;
    //Exclude comments and "double-quoted" text from the result
    
	if( str.compare(Keywords_list[i])== 0 && i==25)
		c[structNum].activate_switch=true;
    
	if( str.compare("{")==0 && c[structNum].activate_switch==true)
		c[structNum].activate_brace=true;
	
 	if(c[structNum].activate_switch && c[structNum].activate_brace ){
		if( str.compare(Keywords_list[i])==0 && i==2) // Only when both are active can the count begin
			caseArr[casePos]++;
	}
 
	if(c[structNum].activate_switch && c[structNum].activate_brace && str.compare("}")==0){
		structNum++;
		casePos++;	
	}
}
```

#### 3.3 Requirements 3 & 4 - if else and if else_if else

- **Get information for each "if" group using find and array of structs**

- **Because "else if" has "else" and "if", so "else if" must be tested first.**

  ![image-20210923201631555](C:\Users\admin\AppData\Roaming\Typora\typora-user-images\image-20210923201631555.png)

- **Here is the code:**

```c++
while(is >> str){
	if(str[0]=='"' || str[0]=='/')   continue;
    //Exclude comments and "double-quoted" text from the result
    
	if( line.find("else if")>=0 && line.find("else if")<line.length()){
		ifArr[ifArrPos].elseIf = true;
	} else if( line.find("if")>=0 && line.find("if")<line.length()){
	ifArrPos++;
	
	while(ifArr[ifArrPos].hasElse && ifArrPos<100）
		ifArrPos++;
		
	ifArr[ifArrPos].hasIf = true;
   	} else if ( line.find("else")>=0 && line.find("else")<line.length()) {
		ifArr[ifArrPos].hasElse = true;
		ifArrPos--;
		while(ifArr[ifArrPos].hasElse==true && ifArrPos>=0)
			ifArrPos--;
	 	}
}
```

- **Identify different if types, such as "if else" "if else_if else", The respective numbers of the two types of IF structures are iterated through the for loop** 

```c++
The_if ifArr[100];
int ifArrPos = -1;
static int IE=0, IEE=0; 
```

```c++
for(int i=0;i<100;i++){
		if(ifArr[i].hasIf){
			if(ifArr[i].elseIf) IEE++;
			else{   IE++;
		    }
		}
} 
```

### 4. Program running result

- **Read the sample file and set the extraction level to a maximum of 4, resulting in the following output.**

![image-20210923190946956](C:\Users\admin\AppData\Roaming\Typora\typora-user-images\image-20210923190946956.png)

### 5. Unit test screenshots and description.

### 6. Summary

I haven't used c++ programming for a long time, and it was a bit intermittent at the beginning of writing, so this experiment was very challenging for me. This assignment is relatively simple if it judges the more standard code like the sample, but it is very difficult if it meets a special case and requires many special cases. Therefore, some special if else_if else structure judgment still exists some problems by the deadline of assignment. Through this assignment, I learned a lot of things that I had never used before, such as Git, Typora, Github... All in all, the experiment was very rewarding and rewarding.

**And I want the next experiment to be easier!**
