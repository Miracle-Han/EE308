#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

const string Keywords_list[32] = {"auto", "break",	"case",	"char",	"const", "continue","default",	"do", "double",	"else",	"enum",	"extern", "float", "for", "goto" , "if",
                            "int",	"long",	"register",	"return", "short", "signed", "sizeof", "static", "struct",	"switch",	"typedef",	"union", "unsigned", "void", "volatile", "while"};
static int table2[32] = {0};

/*for switch*/
struct CaseNum{ 
    bool activate_switch = false; 
    bool activate_brace = false; 
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

int main(){
	char file_add[100];
	cout << "File_name: ";
    cin >> file_add;
	fstream cpp_file(file_add);
	
	int table3[32] = {0};
	for(int i=0;i<32;i++){
		table3[i]=Keywords_list[i].length();
	}
	string line;
	while(!cpp_file.eof()){ 		
   		 getline(cpp_file, line); 
			for(int i=0;i<line.length();i++){
				if( ! (line[i]>='a' && line[i]<='z' || line[i]>='A'&&line[i]<='Z' || line[i]>='0' && line[i]<='9' || line[i] == '{'  				|| line[i]=='}' ||  line[i]=='_' ||line[i]=='/' || line[i]=='"'))
  				line[i]=' ';	 
  			}
    		// For later convenience, we firstly transpose unused strings to Spaces. 
    	string str;
		istringstream is(line); // Read a separate string in each line
		
		while(is>>str){
			if(str[0]=='"' || str[0]=='/')   continue;
			
			for(int i=0;i<32;i++){
				if( str.length()==table3[i] ){
					if( str.compare(Keywords_list[i])==0 )
					table2[i]++;
				}
				
				
				if( str.compare(Keywords_list[i])==0 && i==25){
					c[structNum].activate_switch=true;
				}
				if( str.compare("{")==0 && c[structNum].activate_switch==true){
					c[structNum].activate_brace=true;
				}
				
				if(c[structNum].activate_switch && c[structNum].activate_brace ){
					if( str.compare(Keywords_list[i])==0 && i==2){
						caseArr[casePos]++;
					}
				}
				
				if(c[structNum].activate_switch && c[structNum].activate_brace && str.compare("}")==0){
					structNum++;
					casePos++;	
				}	
			} 
		}		
		
		if( line.find("else if")>=0 && line.find("else if")<line.length()){
			ifArr[ifArrPos].elseIf = true;
		} else if( line.find("if")>=0 && line.find("if")<line.length()){
		
		    ifArrPos++;
			while(ifArr[ifArrPos].hasElse && ifArrPos<100){ 
				ifArrPos++;
			} 
			ifArr[ifArrPos].hasIf = true;
					
		} else if ( line.find("else")>=0 && line.find("else")<line.length()) {
			ifArr[ifArrPos].hasElse = true;
			ifArrPos--;
			while(ifArr[ifArrPos].hasElse==true && ifArrPos>=0){
				ifArrPos--;
			}
		}
	}
	int total;
	for(int j=0;j<32;j++){
		total+=table2[j]; 
	} 
	cout << "keywords_num: " << total << endl;
	cout << "switch structure's num: " << table2[25] << endl;
	cout << "case's num: ";         
	for(int i=0;i<100;i++){
		if(caseArr[i]!=0){
			cout <<caseArr[i] << " ";  
		}
	}
	cout << endl; 
	for(int i=0;i<100;i++){
		if(ifArr[i].hasIf){
			if(ifArr[i].elseIf) IEE++;
			else{   IE++;
		    }
		}
	} 
	cout << "if-else structure's num': " << IE <<endl;
	cout << "if-elseif-else structure's num: " << IEE << endl;
	return 0;
}
