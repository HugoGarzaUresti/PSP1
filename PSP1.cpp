#include <iostream>
#include "Lectura.h"
#include <vector>

using namespace std;

string getClassName(string file){
    file.erase(file.find('.'), (file.find('.') - file.length()));
    return file;
}

int main(){
    vector<string> file;
    string nameFile = "adada";
    int count = -1;
    int totalSum = 0;
    int numberOfClasses = 0;
    while(nameFile.length() != 0){
        getline(cin, nameFile);
        file.push_back(nameFile);
        count++;
    }
    numberOfClasses = count;
    for(int i = 0; i<count; i++){
        for(int j = i + 1; j<count; j++){
            if(getClassName(file[i]) == getClassName(file[j])){
                numberOfClasses--;  
            }
        }
    }
    Lectura lectura[numberOfClasses];
    for(int i = 0, j = 0; i<count; i++, j++){
        if(i != 0 && getClassName(file[i]) == getClassName(file[i-1])){
            j--;
        }
        lectura[j].Calcula(file[i]);
    }

    cout<<"CLASES BASE:"<<endl;
    for(int i = 0; i<numberOfClasses; i++){
        if(lectura[i].getType() == "Base"){
            cout<<"   "<<getClassName(file[i])<<": T="<<lectura[i].getTotalLDC()<<", I="<<lectura[i].getItems()<<", B="<<lectura[i].getBaseLDC()<<
            ", D="<<lectura[i].getDeletedLDC()<<", M="<<lectura[i].getModifiedLDC()<<", A="<<lectura[i].getAddedLDC()<<endl;
            totalSum = totalSum + lectura[i].getTotalLDC();
        }
    }
    cout<<"--------------------------------------"<<endl;
    cout<<"CLASES NUEVAS:"<<endl;
    for(int i = 0; i<numberOfClasses; i++){
        if(lectura[i].getType() == "Nueva"){
            cout<<"   "<<getClassName(file[i])<<": T="<<lectura[i].getTotalLDC()<<", I="<<lectura[i].getItems()<<endl;
            totalSum = totalSum + lectura[i].getTotalLDC();
        }
    }
    cout<<"--------------------------------------"<<endl;
    cout<<"CLASES REUSADAS"<<endl;
    for(int i = 0; i<numberOfClasses; i++){
        if(lectura[i].getType() == "Reusada"){
            cout<<"   "<<getClassName(file[i])<<": T="<<lectura[i].getTotalLDC()<<", I="<<lectura[i].getItems()<<", B="<<lectura[i].getBaseLDC()<<endl;
            totalSum = totalSum + lectura[i].getTotalLDC();
        }
    }
    cout<<"--------------------------------------"<<endl;
    cout<<"Total de LDC= "<<totalSum<<endl;
    
    

    return 0;
}