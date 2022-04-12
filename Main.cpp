#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;

#include "Matrix.hpp"
using namespace zich;

vector<string> split(string eq, const string & delim){
    
    size_t delim_idx = eq.find(delim);
    if(delim_idx != string::npos){
        string half1 = eq.substr(0,delim_idx);
        string half2 = eq.erase(0, delim_idx + delim.length());
        return vector<string>{half1,half2};
    }
    return vector<string>{eq};
    
}
void print(string key, Matrix value){
    cout << key << ": " << endl << value << endl << endl;
}
void print(Matrix value){
    cout << value << endl << endl;
}
Matrix process_eq(string eq, map<string,Matrix>& mats){
    if(mats.find(eq) != mats.end()){
        return mats.at(eq);
    }
    size_t delim_idx;
    vector<string> args;
    if((args = split(eq,"*=")).size()>1){
        return process_eq(args[0]+"="+args[0]+"*"+args[1],mats);
    }
    if((args = split(eq,"+=")).size()>1){
        return process_eq(args[0]+"="+args[0]+"+"+args[1],mats);
    }
    if((args = split(eq,"-=")).size()>1){
        
        mats[args[0]] = mats[args[0]]-process_eq(args[1],mats);
        return mats[args[0]];
    }

    if((args = split(eq,"=")).size()>1){
        mats[args[0]] = process_eq(args[1],mats);
        return process_eq(args[0],mats);
    }
    if((args = split(eq,"+")).size()>1){
        Matrix mat1 = process_eq(args[0],mats);
        Matrix mat2 = process_eq(args[1],mats);
        return mat1+mat2;
    }
    if((args = split(eq,"-")).size()>1){
        Matrix mat1 = process_eq(args[0],mats);
        Matrix mat2 = process_eq(args[1],mats);
        return mat1-mat2;
    }
    if((args = split(eq,"*")).size()>1){
        
        string var1;
        for(char const & c: args[0]){
            if(isdigit(c) == 0){
                break;
            }
            var1+=c;
        }
        string var2;
        for(char const & c: args[1]){
            if(isdigit(c) == 0){
                break;
            }
            var2+=c;
        }
        Matrix mat;
        //both var1 and var2 are numbers
        if(var1.length()>0 && var2.length()>0){
            double newVal = stod(var1)*stod(var2);
            //we get rid of the * sign infrot of var2, only a * is valid input after scalar
            //since we dont check for adition by some value
            string new_eq = args[1].substr(var2.length()+1);
            cout<<new_eq<<endl;
            return newVal*process_eq(new_eq,mats);
        }
        else if(var1.length()==0 && var2.length()>0){
            //could have a raw mat as input
            mat = process_eq(args[0],mats);
            string new_eq = args[1].substr(var2.length());
            return process_eq(var2 + "*" + args[0] + new_eq,mats);
            
        }
        else if(var2.length()==0 && var1.length()>0){
            for(char const & c: args[1]){
                if(c=='-' || c=='+' || c=='=' || c=='>' || c=='<' || c=='*'){
                    break;
                }
                var2+=c;
            }
            //get the following matrix
            //mat = process_eq(var2,mats);
            return stod(var1)*process_eq(args[1],mats);
        }
        mat = process_eq(args[0],mats);
        return mat*process_eq(args[1],mats);
    }
    
    cout<<eq<<endl;
    istringstream newMatStream{eq};
    Matrix mat;
    newMatStream>>mat;
    return mat;
}
void save(string f, map<string,Matrix> mats){
    fstream file(f,ios::trunc|ios::out);
    if(file.is_open()){
        for(auto const& entry: mats){
            string line = entry.first;
            line+=":";
            vector<string> lines;
            ostringstream osLines;
            osLines<<entry.second;
            string os_string = osLines.str();
            while((lines = split(os_string,"\n")).size()>1){
                os_string = lines[0];
                os_string += ", ";
                os_string += lines[1];
            }
            line += os_string;
            
            file<<line<<endl;
        }
    }
}
map<string,Matrix> load(string f){
    map<string,Matrix> mats;
    fstream file(f,ios::in);
    if(file.is_open()){
        string key;
        while(getline(file,key,':')){
            Matrix mat;
            string mat_in;
            getline(file,mat_in);
            
            istringstream mat_stream{mat_in};
            mat_stream>>mat;
            mats[key] = mat;
        }
    }
    return mats;
}
int main(){
    map<string,Matrix> matrices = load("mats.txt");
    //always run
    while(true){
        string inp;
        if(getline(cin,inp)){
            size_t delim;
            if(inp == "list" || inp == "List"){
                for(auto const& entry: matrices){
                    print(entry.first,entry.second);
                }
            }
            else{
                print(process_eq(inp,matrices));
                save("mats.txt",matrices);
            }
        }
    }
    return 0;
}







