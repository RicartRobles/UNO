using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        Socket server;
        public Form1()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            //Creamos un IPEndPoint con el ip del servidor y puerto del servidor 
            //al que deseamos conectarnos
            IPAddress direc = IPAddress.Parse("192.168.1.138");
            IPEndPoint ipep = new IPEndPoint(direc, 9030);


            //Creamos el socket 
            server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try
            {
                server.Connect(ipep);//Intentamos conectar el socket
                this.BackColor = Color.Green;
                //MessageBox.Show("Conectado");

            }
            catch (SocketException)
            {
                //Si hay excepcion imprimimos error y salimos del programa con return 
                MessageBox.Show("No he podido conectar con el servidor");
                return;
            }


        }

        private void Bonito_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {

            if (Longitud.Checked)
            {
                //enviamos al servidor el nombre tecleado
                string mensaje = "1/-";
                byte[] msge = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msge);


                //Ahora recivimos la respuesta del servidor

                byte[] msgr = new byte[30];
                server.Receive(msgr);
                mensaje = Encoding.ASCII.GetString(msgr).Split('\0')[0];
                MessageBox.Show("La partida mas corta del jugador con mas vistorias es " + mensaje + " minutos");
            }
            else if (Bonito.Checked)
            {
                //enviamos al servidor el nombre tecleado
                string mensaje = "2/-";
                byte[] msge = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msge);


                //Ahora recivimos la respuesta del servidor

                byte[] msgr = new byte[80];
                server.Receive(msgr);
                mensaje = Encoding.ASCII.GetString(msgr).Split('\0')[0];

                MessageBox.Show("El ganador de la partida mas corta es "+ mensaje);
            
            

            }
            else
            {
                string mensaje = "3/" + nombre.Text;
                byte[] msge = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msge);


                //Ahora recivimos la respuesta del servidor

                byte[] msgr = new byte[30];
                server.Receive(msgr);
                mensaje = Encoding.ASCII.GetString(msgr).Split('\0')[0];
                MessageBox.Show("La posicion final en la que el jugador a recividio mas +4 es "+ mensaje + "º");
              
            }
        }
         
            
            

        private void nombre_TextChanged(object sender, EventArgs e)
        {

        }

        private void Longitud_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

       


        private void button3_Click(object sender, EventArgs e)
        {
            //Mensaje de desconexión
            string mensaje = "0/";

            byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            server.Send(msg);

            // Nos desconectamos
            this.BackColor = Color.Gray;
            server.Shutdown(SocketShutdown.Both);
            server.Close();


        }

        
        }
    }

