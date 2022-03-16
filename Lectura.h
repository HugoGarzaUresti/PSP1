#include <iostream>
#include <fstream>
    using namespace std;

    class Lectura{
        private:
        int totalLDC;
        int baseLDC;
        int deletedLDC;
        int modifiedLDC;
        int addedLDC;
        int items;
        int num;
        string line;
        string type;
        bool commentFlag;
        bool stringFlag;

        public:
        Lectura();
        int getTotalLDC();
        int getBaseLDC();
        int getDeletedLDC();
        int getModifiedLDC();
        int getAddedLDC();
        int getItems();
        string getType();
        void Calcula(string);
    };

    Lectura::Lectura(){
        totalLDC = 0;
        baseLDC = 0;
        deletedLDC = 0;
        modifiedLDC = 0;
        addedLDC = 0;
        items = 0;
        num = 0;
        type = " ";
        commentFlag = false;
        stringFlag = false;
    }

    int Lectura::getTotalLDC(){
        return totalLDC;
    }

    int Lectura::getItems(){
        return items;
    }
    
    int Lectura::getBaseLDC(){
        return baseLDC;
    }

    int Lectura::getDeletedLDC(){
        return deletedLDC;
    }

    int Lectura::getModifiedLDC(){
        return modifiedLDC;
    }

    int Lectura::getAddedLDC(){
        return addedLDC;
    }

    string Lectura::getType(){
        if(baseLDC > 0 && (modifiedLDC > 0 || deletedLDC > 0 || addedLDC > 0 )){
            return "Base";
        }
        if(baseLDC == 0 && modifiedLDC == 0 && deletedLDC == 0 && addedLDC > 0 ){
            return "Nueva";
        }
        if(baseLDC > 0 && modifiedLDC == 0 && deletedLDC == 0 && addedLDC == 0 ){
            return "Reusada";
        }
        return "";   
    }

    void Lectura::Calcula(string file){
        ifstream read(file);
        commentFlag = false;
        stringFlag = false;
        while(getline(read,line)){
            totalLDC++;
            if(commentFlag){
                totalLDC--;
            }
            if(!commentFlag && line.find("/*") != string::npos){
	  			commentFlag = true;
                totalLDC--;
                cout<<file<<" Comentario multi empieza"<<num++<<endl;		
	  		}
            
            if(!stringFlag && line.find('"') != string::npos){
                stringFlag = true;
            }

            if(line.find("//.i") != string::npos){
                items++;
            }
            
            if(line.find("//.b") != string::npos){
                string number;
                for(int i = line.find("//.b") + 5; i<line.length(); i++){
                    number = number + line[i];
                }
                baseLDC = baseLDC + stoi(number);
            }

            if(line.find("//.d") != string::npos){
                string number;
                for(int i = line.find("//.d") + 5; i<line.length(); i++){
                    number = number + line[i];
                }
                deletedLDC = deletedLDC + stoi(number);
            }

            if(!stringFlag && !commentFlag && line.find("//.m") != string::npos){
                modifiedLDC++;
                totalLDC++;
            }
            
            if(line.find('}') != string::npos || line.find('{') != string::npos ){
                bool aux = false;
                for(int i = 0; i<line.length(); i++){
                    if(line[i] != '}' && line[i] != '{' && line[i] != '\t' && line[i] != '\r'){
                        aux = true;
                    }
                }
                if(!aux){
                    totalLDC--;
                    cout<<file<<" Unico "<<num++<<endl;
                }
	  		}

            if(line.find("};") != string::npos){
                bool aux = false;
                for(int i = 0; i<line.length(); i++){
                    if(line[i] != '}' && line[i] != ';' && line[i] != '\t' && line[i] != '\r' && line[i] != ' '){
                        aux = true;
                    }
                }
                if(!aux){
                    totalLDC--;
                    cout<<file<<" Unico "<<num++<<endl;
                }
            }

            if(line.find('\t') || line.find(' ')){
                bool aux = false;
	  			for(int i = 0; i<line.length(); i++){
	  				if(line[i] != '\t' && line[i] != ' ' && line[i] != '\r'){
	  					aux = true;
	  				}
	  			}
	  			if(!aux){
	  				totalLDC--;
                      cout<<file<<" Blanca "<<num++<<endl;
	  			}
	  		}
            if(!commentFlag && line.find("//") != string::npos){
                int help = line.find("//");
                if(line[help-1] == ':'){
                    continue;
                }
	  			totalLDC--;
                cout<<file<<" Comentario "<<num++<<endl;
	  		}
            
            if(commentFlag && line.find("*/") != string::npos){
	  			commentFlag = false;
                cout<<file<<" Comentario multi acaba"<<num++<<endl;
	  		}

            if(stringFlag && line.find('"') != string::npos){
                stringFlag = false;
            }

        }
        addedLDC = totalLDC - baseLDC + deletedLDC;
    }


