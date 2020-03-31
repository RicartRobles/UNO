#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <mysql.h>

int main(int argc, char *argv[])
{
	// Estructurs que se utilizan gracias a los includes
	int sock_conn, sock_listen, ret;
	struct sockaddr_in serv_adr;
	// vectores que almacenan la peticion que te hacen
	char buff[512];
	char respuesta[512];
	int resu;
	// Inicializamos
	// Abrimos el socket de escucha, va a estar esperando una peticion
	if ((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("Error creant socket\n");
	// Hacemos un bind al puerto
	
	
	memset(&serv_adr, 0, sizeof(serv_adr));// inicialitza a zero serv_addr
	serv_adr.sin_family = AF_INET;
	
	// asocia el socket a cualquiera de las IP de la m?quina. 
	//htonl formatea el numero que recibe al formato necesario
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);// cualquier direccion
	
	// escucharemos en el port 9070
	serv_adr.sin_port = htons(9030);
	// operacion de bind, especifica el tipo de protocolo y puerto
	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
		printf ("Error al bind\n");
	
	//La cola de peticiones pendientes no podr? ser superior a 4
	// socket pasivo, vamos a estar escuchando
	// pueden haber en cola de espera hasta 3 peticiones
	if (listen(sock_listen, 3) < 0)
		printf("Error en el Listen\n");
	int i;
	//bucle infinito
	for(;;)
	{
		printf("Escuchando...\n");
		
		
		// socket para conectarse
		sock_conn = accept(sock_listen, NULL, NULL);
		printf ("He recibido conexi?n\n");
		//sock_conn es el socket que usaremos para este cliente
		
		int terminar =0;
		while (terminar ==0)
		{
			
			// EL SERIVIDOR SE QUEDARA PARADO HASTA QUE ALGUIEN SE CONECTE
			// recoger la peticion, read = lectura, en ret me va a dar el numero de byts que he leido
			// en buff me va a guardar la peticion
			ret=read(sock_conn,buff, sizeof(buff));
			printf ("Recibido\n");
			
			// Añadimos una marca de fin de sting al mensaje que acabo de recivir
			// si el mensaje tiene 7 caract. estaran en las posiciones 0-6 del vector, y en al posicion 7
			//ponemos fin de linea "\0".
			buff[ret]='\0';
			
			//3. DETERMINAR QUE ES LO QUE ME PIDEN
			
			printf ("Se ha conectado: %s\n",buff);
			
			// vamos a ver que quiere
			
			//cogemos la peticion y cortamos por donde hay una barra, coges lo que hay desde el inicio hasta
			//la barra
			char *p = strtok(buff,"/");
			//coges lo que has cortado y lo combiertes a numero enter y lo metes en la variable codigo
			int codigo = atoi (p);
			// corta por la siguiente barra o hasta que encuentre final de string y te devuelve un puntero al inicio
			//de ese segundo trozo, en p tengo ya el segundo trozo, que es un nombre
			char nombre [90];
			// copias lo que hay en el punter p (string) en la variable nombre
			
			if (codigo !=0)
			{
				p = strtok (NULL,"/");
				strcpy (nombre, p);
			}
			if(codigo ==0)
				terminar=1;
			
			if (codigo == 1) // piden la longitud del nobre
			{
				printf ("codigo:%d\n",codigo);
				
				MYSQL *conn;
				int err;
				// Estructura especial para almacenar resultados de consultas 
				MYSQL_RES *resultado;
				MYSQL_ROW row;
				char consulta [800];
				//Creamos una conexion al servidor MYSQL 
				conn = mysql_init(NULL);
				if (conn==NULL) {
					printf ("Error al crear la conexi??n: %u %s\n", 
							mysql_errno(conn), mysql_error(conn));
					exit (1);
				}
				//inicializar la conexion
				conn = mysql_real_connect (conn, "localhost","root", "mysql", "unoBD",0, NULL, 0);
				if (conn==NULL) {
					printf ("Error al inicializar la conexi??n: %u %s\n", 
							mysql_errno(conn), mysql_error(conn));
					exit (1);
				}
				// consulta SQL para obtener una tabla con todos los datos
				// de la base de datos
				err=mysql_query (conn, "SELECT * FROM jugadores");
				if (err!=0) {
					printf ("Error al consultar datos de la base %u %s\n",
							mysql_errno(conn), mysql_error(conn));
					exit (1);
				}
				
				resultado = mysql_store_result (conn);
				
				strcpy (consulta,"SELECT MIN(tiempoPartida) FROM partidas,relacion,jugadores WHERE jugadores.numVictorias=(SELECT MAX(numVictorias) FROM jugadores) AND jugadores.id=relacion.idJugador AND relacion.idPartida=partidas.id;"
						); 
				
				// hacemos la consulta 
				err=mysql_query (conn, consulta); 
				if (err!=0) {
					printf ("Error al consultar datos de la base %u %s\n",
							mysql_errno(conn), mysql_error(conn));
					exit (1);
				}
				//recogemos el resultado de la consulta 
				resultado = mysql_store_result (conn); 
				row = mysql_fetch_row (resultado);
				if (row == NULL)
					printf ("No se han obtenido datos en la consulta\n");
				else
					// El resultado debe ser una matriz con una sola fila
					// y una columna que contiene el nombre
					resu= atoi(row[0]);
				sprintf(respuesta, "%d",resu);
				printf ("La partida más corta del jugador con más victorias es de %s segundos\n",row[0]);
				// cerrar la conexion con el servidor MYSQL 
				mysql_close (conn);
			}
			else if (codigo ==2)
			{
				MYSQL *conn;
				int err;
				// Estructura especial para almacenar resultados de consultas 
				MYSQL_RES *resultado;
				MYSQL_ROW row;
				char consulta [80];
				//Creamos una conexion al servidor MYSQL 
				conn = mysql_init(NULL);
				if (conn==NULL) {
					printf ("Error al crear la conexi??n: %u %s\n", 
							mysql_errno(conn), mysql_error(conn));
					exit (1);
				}
				//inicializar la conexion
				conn = mysql_real_connect (conn, "localhost","root", "mysql", "unoBD",0, NULL, 0);
				if (conn==NULL) {
					printf ("Error al inicializar la conexi??n: %u %s\n", 
							mysql_errno(conn), mysql_error(conn));
					exit (1);
				}
				// consulta SQL para obtener una tabla con todos los datos
				// de la base de datos
				err=mysql_query (conn, "SELECT * FROM jugadores");
				if (err!=0) {
					printf ("Error al consultar datos de la base %u %s\n",
							mysql_errno(conn), mysql_error(conn));
					exit (1);
				}
				//recogemos el resultado de la consulta. El resultado de la
				//consulta se devuelve en una variable del tipo puntero a
				//MYSQL_RES tal y como hemos declarado anteriormente.
				//Se trata de una tabla virtual en memoria que es la copia
				//de la tabla real en disco.
				resultado = mysql_store_result (conn);
				// El resultado es una estructura matricial en memoria
				// en la que cada fila contiene los datos de una persona.
				// Ahora vamos a buscar el nombre de la persona cuyo DNI es uno
				// dado por el usuario
				// construimos la consulta SQL
				err=mysql_query (conn, "SELECT ganador FROM partidas WHERE tiempoPartida =(SELECT MIN(tiempoPartida) FROM partidas) ;"); 
				if (err!=0) {
					printf ("Error al consultar datos de la base %u %s\n",
							mysql_errno(conn), mysql_error(conn));
					exit (1);
				}
				//recogemos el resultado de la consulta 
				resultado = mysql_store_result (conn); 
				row = mysql_fetch_row (resultado);
				if (row == NULL)
					printf ("No se han obtenido datos en la consulta\n");
				else
				{
					// El resultado debe ser una matriz con una sola fila
					// y una columna que contiene el nombre
					sprintf(respuesta, "%s",row[0]);
					printf ("Nombre del ganador de la partida mas corta es: %s\n", row[0] );
				}

				mysql_close (conn);
			}
			else if (codigo == 3)//dime si soy alto?
			{
				// volvemos a cortar y cogemos el nuemreo decimal y lo guardamos en la variable altur
				MYSQL *conn;
				int err;
				// Estructura especial para almacenar resultados de consultas 
				MYSQL_RES *resultado;
				MYSQL_ROW row;
				char consulta [1000];
				//Creamos una conexion al servidor MYSQL 
				conn = mysql_init(NULL);
				if (conn==NULL) {
					printf ("Error al crear la conexi??n: %u %s\n", 
							mysql_errno(conn), mysql_error(conn));
					exit (1);
				}
				//inicializar la conexion
				conn = mysql_real_connect (conn, "localhost","root", "mysql", "unoBD",0, NULL, 0);
				if (conn==NULL) {
					printf ("Error al inicializar la conexi??n: %u %s\n", 
							mysql_errno(conn), mysql_error(conn));
					exit (1);
				}
				// consulta SQL para obtener una tabla con todos los datos
				// de la base de datos
				err=mysql_query (conn, "SELECT * FROM jugadores");
				if (err!=0) {
					printf ("Error al consultar datos de la base %u %s\n",
							mysql_errno(conn), mysql_error(conn));
					exit (1);
				}
				//recogemos el resultado de la consulta. El resultado de la
				//consulta se devuelve en una variable del tipo puntero a
				//MYSQL_RES tal y como hemos declarado anteriormente.
				//Se trata de una tabla virtual en memoria que es la copia
				//de la tabla real en disco.
				resultado = mysql_store_result (conn);
				// El resultado es una estructura matricial en memoria
				// en la que cada fila contiene los datos de una persona.
				// Ahora vamos a buscar el nombre de la persona cuyo DNI es uno
				// dado por el usuario
				// construimos la consulta SQL
				strcpy(consulta,"SELECT relacion.posicion FROM jugadores, partidas, relacion WHERE relacion.mas4Recibido=(SELECT MAX(mas4recibido) FROM partidas, relacion, jugadores WHERE relacion.idJugador= (SELECT jugadores.id FROM jugadores WHERE jugadores.nickname='");
				strcat(consulta, nombre);
				strcat(consulta, "'));");
				
				// hacemos la consulta 
				err=mysql_query (conn, consulta); 
				if (err!=0) {
					printf ("Error al consultar datos de la base %u %s\n",
							mysql_errno(conn), mysql_error(conn));
					exit (1);
				}
				//recogemos el resultado de la consulta 
				resultado = mysql_store_result (conn); 
				row = mysql_fetch_row (resultado);
				if (row == NULL)
					printf ("No se han obtenido datos en la consulta\n");
				else
					// El resultado debe ser una matriz con una sola fila
					// y una columna que contiene el nombre
					printf ("La partida más corta del jugador con más victorias es de %s segundos\n",row[0]);
				resu= atoi(row[0]);
				sprintf(respuesta, "%d",resu);
				
				// cerrar la conexion con el servidor MYSQL 
				mysql_close (conn);
				// Y lo enviamos
				
				
				// Se acabo el servicio para este cliente
				
			}
			if (codigo != 0)
			{
				printf("La repuesta a tu pregunta es %s\n",respuesta);
				
				//y lo enviamos
				write (sock_conn,respuesta,strlen(respuesta));
			}
		}
		//y acabamos el servicio con el cliente
		close(sock_conn);
	}
}


