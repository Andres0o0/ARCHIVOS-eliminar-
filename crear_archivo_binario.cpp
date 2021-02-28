#include <iostream>
#include <stdio.h>  
#include <string.h> 
#include <windows.h>


using namespace std;
const char *nombe_archivo = "archivo.dat";

struct Estudiante{
	int codigo;
	char nombre[50];
	char apellido[50];
	int telefono;
	int borrar=0;
};

void ingresar_estudiante();
void abrir_estudiante();
void modificar_estudiante();
void eliminar_estudiante();
void borrardatos();

int main (){
abrir_estudiante();
ingresar_estudiante();
modificar_estudiante();
eliminar_estudiante();
borrardatos();
abrir_estudiante();
	return 0;	
}
void buscar_codigo(){
	
	FILE* archivo = fopen(nombe_archivo, "rb");
	
	int indice=0,pos=0,cod=0;
	cout<<"BUSCAR CODIGO: ";
	cin>>cod;
	Estudiante estudiante;
	
	fread ( &estudiante, sizeof(Estudiante), 1, archivo );
		
		do{
			
			if (estudiante.codigo == cod){
			pos = indice;
			}
	
		fread ( &estudiante, sizeof(Estudiante), 1, archivo );
		indice += 1;
		} while (feof( archivo ) == 0);
		
	cout<<"------------------ "<<pos<<" ------------------"<<endl;
	fseek ( archivo,pos * sizeof(Estudiante), SEEK_SET );

    fread ( &estudiante, sizeof( Estudiante ), 1, archivo );

    	cout << "Codigo: " << estudiante.codigo << endl;
        cout << "Nombre: " << estudiante.nombre << endl;
        cout << "Apellido: " << estudiante.apellido << endl;
        cout << "Telefono: " << estudiante.telefono << endl;
        cout << endl;
	
	fclose(archivo);
	system("PAUSE");
}


void buscar_indice(){
	FILE* archivo = fopen(nombe_archivo, "rb");
	
	int pos=0;
	cout<<"Que registro desea ver: ";
	cin>>pos;
	cout<<"------------------ "<<pos<<" ------------------"<<endl;
	fseek ( archivo,pos * sizeof(Estudiante), SEEK_SET );
	
	Estudiante estudiante;
	
    fread ( &estudiante, sizeof( Estudiante ), 1, archivo );

    	cout << "Codigo: " << estudiante.codigo << endl;
        cout << "Nombre: " << estudiante.nombre << endl;
        cout << "Apellido: " << estudiante.apellido << endl;
        cout << "Telefono: " << estudiante.telefono << endl;
        cout << endl;
	
	fclose(archivo);

	
}


void abrir_estudiante(){

	system("cls");
	FILE* archivo = fopen(nombe_archivo, "rb");
	if(!archivo) {
		archivo = fopen(nombe_archivo, "w+b");
	}
	Estudiante estudiante;
	int registro=0;
	fread ( &estudiante, sizeof(Estudiante), 1, archivo );
	cout<<"____________________________________________________________________"<<endl;
	cout << "id" <<"\t|"<< "CODIGO" <<"\t|"<< "NOMBRE"<<" \t"<<"APELLIDO"<<"\t"<<"\t "<<"TELEFONO"<<" "<<endl;	
		do{
			if(estudiante.borrar==0){
		cout<<"____________________________________________________________________"<<endl;
		cout << registro <<" \t|  "<< estudiante.codigo <<" \t| "<< estudiante.nombre<<" \t"<<estudiante.apellido<<"\t"<<"\t "<<estudiante.telefono<<endl;
			registro += 1;	
    }
		fread ( &estudiante, sizeof(Estudiante), 1, archivo );
		} while (feof( archivo ) == 0);
		
    cout<<endl;
    
		fclose(archivo);
	}
void ingresar_estudiante(){
	
	char continuar;
	FILE* archivo = fopen(nombe_archivo, "ab"); // ab
	
	
		Estudiante estudiante;
		 string nombre,apellido;
		do{
			fflush(stdin);
			
		cout<<"Ingrese el Codigo:";
		cin>>estudiante.codigo;
        cin.ignore();
        
		cout<<"Ingrese el Nombre:";
		getline(cin,nombre);
    	strcpy(estudiante.nombre, nombre.c_str()); 
			
		cout<<"Ingrese el Apellido:";
		getline(cin,apellido);
		strcpy(estudiante.apellido, apellido.c_str()); 
		
		cout<<"Ingrese el Telefono:";
		cin>>estudiante.telefono;
		cin.ignore();
		estudiante.borrar==0;
		fwrite( &estudiante, sizeof(Estudiante), 1, archivo );
		
		cout<<"Desea Agregar otro Nombre s/n : ";
		cin>>continuar;
		} while((continuar=='s') || (continuar=='S') );
		
	
	fclose(archivo);
	abrir_estudiante();
	//buscar_indice();	
	buscar_codigo();
}
void modificar_estudiante(){
	
	FILE* archivo = fopen(nombe_archivo, "r+b");
	
		int id;
		string nombre,apellido;	
    	Estudiante estudiante;
    
		cout << "Ingrese el ID (primera columna) que desea Modificar: ";
    		cin >> id;
    		fseek ( archivo, id * sizeof(Estudiante), SEEK_SET );  // esto es lo que permite modificar en la pocision
	
		cout<<"Ingrese el Codigo:";
		cin>>estudiante.codigo;
        cin.ignore();
        
		cout<<"Ingrese el Nombre:";
		getline(cin,nombre);
    	strcpy(estudiante.nombre, nombre.c_str()); 
			
		cout<<"Ingrese el Apellido:";
		getline(cin,apellido);
		strcpy(estudiante.apellido, apellido.c_str()); 
		
		cout<<"Ingrese el Telefono:";
		cin>>estudiante.telefono;
		cin.ignore();
		
		fwrite( &estudiante, sizeof(Estudiante), 1, archivo );
		
	fclose(archivo);
	abrir_estudiante();
		system("PAUSE");
}

void eliminar_estudiante(){
	
		FILE* archivo = fopen(nombe_archivo, "r+b");
	
	int indice=0,pos=0,cod=0;
	cout<<"INGRESE CODIGO DE DATO A BORRAR: ";
	cin>>cod;
	Estudiante estudiante;
	
	fread ( &estudiante, sizeof(Estudiante), 1, archivo );
		
		do{
			
			if (estudiante.codigo == cod){
			pos = indice;
			}
	
		fread ( &estudiante, sizeof(Estudiante), 1, archivo );
		indice += 1;
		} while (feof( archivo ) == 0);
		
	fseek ( archivo,pos * sizeof(Estudiante), SEEK_SET );
    estudiante.borrar=1;
    fwrite ( &estudiante, sizeof( Estudiante ), 1, archivo );

	
	fclose(archivo);
	system("PAUSE");
}

void borrardatos(){
	FILE* archivo = fopen(nombe_archivo, "rb");
	FILE* temporal= fopen("temporal.dat","w+b");
	
	Estudiante estudiante;
	int registro=0;
	fread ( &estudiante, sizeof(Estudiante), 1, archivo );
    while (feof( archivo ) == 0){
			if(estudiante.borrar==0){
				fwrite(&estudiante,sizeof(Estudiante),1,temporal);
    }
		fread ( &estudiante, sizeof(Estudiante), 1, archivo );
		} 
		
    cout<<endl;
		fclose(archivo);
		fclose(temporal);
		remove ("archivo.dat");
		rename("temporal.dat","archivo.dat");
	
	
}
