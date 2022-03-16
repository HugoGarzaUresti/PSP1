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
        string className;
        bool commentFlag;

        public:
        Lectura();
        int getTotalLDC();
        int getBaseLDC();
        int getDeletedLDC();
        int getModifiedLDC();
        int getAddedLDC();
        int getItems();
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
        className = " ";
        commentFlag = false;
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
        return (this->totalLDC - this->baseLDC + this->deletedLDC);
    }

    void Lectura::Calcula(string file){
        ifstream read(file);
        while(getline(read,line)){
            totalLDC++;

            if(commentFlag){
                totalLDC--;
                cout<<"Enmedio"<<endl;
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

            if(!commentFlag && line.find("//.m") != string::npos){
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
                    //cout<<"hola"<<endl;
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
	  			}
	  		}

            if(line.empty()){
	  			totalLDC--;
	  		}  

            if(line.find("//") != string::npos){
                int help = line.find("//");
                if(line[help-1] == ':'){
                    continue;
                }
	  			totalLDC--;
	  		}
            if(!commentFlag && line.find("/*") != string::npos){
	  			commentFlag = true;
                cout<<"Empieza"<<endl;
                totalLDC--;		
	  		}
            if(commentFlag && line.find("*/") != string::npos){
	  			commentFlag = false;
                cout<<"Termina"<<endl;
	  		}

        }
    }


