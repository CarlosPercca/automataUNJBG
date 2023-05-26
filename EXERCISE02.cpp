#include<bits/stdc++.h>

using namespace std;

struct estado{
	vector<char> transicion;
	vector<string> destine;
	char origen;
	int category;
};

void imprimir(vector<estado> array, int estados){
	for ( int i = 0 ; i <estados ; i++){
		cout<<array[i].origen<<" ";
	}
}

void imprimir2(vector<estado> array , int estados , int transiciones){
	for (int i = 0 ; i < estados ; i++){
		cout << array[i].origen << endl;
		cout << "contiene: "<<endl;
		for ( int j = 0 ; j< transiciones;j++){
			cout<<array[i].transicion[j]<<" : "<<endl;
			cout<<" DESTINOS:  "<<array[i].destine[j]<<endl;
		}
		cout <<endl;
	}
}

int errorLexico(vector<estado> automata , string cadena , string transicionLexico){
	for (int i = 0 ; i < cadena.length() ; i++){
		// COMPROBACION SI EL PRIMER CARACTER DE LA CADENA COINCIDE CON UNO DE LAS TRANSICIONES QUE ES USADA POR EL AUTOMATA
		if ( i == 0){
			for ( int k = 0 ; k < transicionLexico.length(); k++){
				if (cadena[i] == automata[0].transicion[k] && automata[0].destine[k] == "-"){
					cout<<"Cadena de transiciones invalida"<<endl;
					return 0;					
				}			
			}
		}
		if(transicionLexico.find(cadena[i]) == string :: npos){
			cout<<"Cadena de transiciones invalida"<<endl;
			return 0;
		}
	}
	return 1;
}
 
int validateCadena2(vector<estado> automata , int posCadena, char estado, string cadena , string transicionLexico , string cadenaEstados){
	if (posCadena == cadena.length()) return -2;
	auto iteradorTransicion = transicionLexico.find(cadena[posCadena]);
	auto iteradorEstadoAutomata = cadenaEstados.find(estado);
	string destinos = automata[iteradorEstadoAutomata].destine[iteradorTransicion];
	if (destinos == "-") return -1;
	else{
		for ( int i = 0 ; i < destinos.length() ; i++){
			if(validateCadena2(automata,posCadena +1,destinos[i],cadena,transicionLexico,cadenaEstados) == -2){
				return -2;
			}
		}
		return -1;
	}
}

int validateCadena(vector <estado> automata , string cadena, string transicionLexico, string cadenaEstados){
	if (!errorLexico(automata , cadena , transicionLexico)) return -1;
	return validateCadena2(automata,0,cadenaEstados[0],cadena,transicionLexico,cadenaEstados);
}

int main(){
	// INGRESO DE DATOS DE NUM DE ESTADOS Y TRANSICIONES
	cout<<"--------------------------ESTADOS---------------------------"<<endl;
	int estados , transiciones ;
	cout << "Ingrese numero de estados : ";
	cin >> estados;
	cout << " Ingrese los nombres de cada estado separados por un ESPACIO : ";
	vector <estado> automata(estados);
	string cadenaEstados = "";
	for ( int i = 0 ; i < estados ; i++ ){
		cin>>automata[i].origen;
		cadenaEstados += automata[i].origen;
		automata[i].category = 2;
		if(i == 0) automata[i].category = 1;
		if(i == estados-1) automata[i].category = 3;
		
	}
	cout<<"-------------------------TRANSICIONES-----------------------"<<endl;
	cout << "Ingrese numero de transiciones :";
	cin >> transiciones ;

	string transicionLexico = "";

	char lexico;
	cout << "Ingrese los nombres de  las transiciones separados por un ESPACIO: ";
	for ( int i = 0 ; i < transiciones ; i++ ){
		cin>>lexico;
		transicionLexico += lexico;
		for ( int i = 0 ; i < estados ; i++ ){
			automata[i].transicion.push_back(lexico);
		}	
	}
	
	int cant;
	char destineTransicion;
	string destinos = "";

	cout<<endl<<"-----------------ESTABLECER CONEXIONES DE CADA ESTADO---------------------"<<endl;
	for ( int i = 0 ; i < estados ; i++ ){
		cout<<"CONEXIONES DEL ESTADO ( "<<automata[i].origen<< " ) : "<<endl;
		for ( int j = 0 ; j < transiciones ; j++){
			cout<<"Cantidad de estados enlanzados con la transicion || "<<automata[i].origen<<" -- "<<automata[i].transicion[j]<<" -> : ";
			cin>>destinos;
			automata[i].destine.push_back(destinos);
			destinos = "";
			cout<<"-----"<<endl;
		}
		cout<<"--------------------------------------"<<endl;
	}
	imprimir2(automata,estados,transiciones);	
	int cantCadena;
	cout<<" CANTIDAD DE CADENAS A PROBAR : ";cin>>cantCadena;
	string cadena;
	for ( int i = 0 ; i < cantCadena ; i++){
		cin >> cadena;
		if(validateCadena(automata,cadena ,transicionLexico,cadenaEstados) == -2) cout<<"CADENA PERMITIDA"<<endl;
		else cout <<"CADENA NO PERMITIDA"<<endl;
	}
}
