namespace WindowsFormsApplication1
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.Longitud = new System.Windows.Forms.RadioButton();
            this.Bonito = new System.Windows.Forms.RadioButton();
            this.button1 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.nombre = new System.Windows.Forms.TextBox();
            this.altura = new System.Windows.Forms.RadioButton();
            this.label2 = new System.Windows.Forms.Label();
            this.alturaBox = new System.Windows.Forms.TextBox();
            this.conectar = new System.Windows.Forms.Button();
            this.desconectar = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // Longitud
            // 
            this.Longitud.AutoSize = true;
            this.Longitud.Checked = true;
            this.Longitud.Location = new System.Drawing.Point(15, 121);
            this.Longitud.Name = "Longitud";
            this.Longitud.Size = new System.Drawing.Size(327, 21);
            this.Longitud.TabIndex = 0;
            this.Longitud.TabStop = true;
            this.Longitud.Text = "partida mas corta del jugador con mas victorias\r\n";
            this.Longitud.UseVisualStyleBackColor = true;
            this.Longitud.CheckedChanged += new System.EventHandler(this.Longitud_CheckedChanged);
            // 
            // Bonito
            // 
            this.Bonito.AutoSize = true;
            this.Bonito.Location = new System.Drawing.Point(15, 158);
            this.Bonito.Name = "Bonito";
            this.Bonito.Size = new System.Drawing.Size(246, 21);
            this.Bonito.TabIndex = 1;
            this.Bonito.Text = "el ganador de la partida más corta";
            this.Bonito.UseVisualStyleBackColor = true;
            this.Bonito.CheckedChanged += new System.EventHandler(this.radioButton2_CheckedChanged);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(-9, 252);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(378, 44);
            this.button1.TabIndex = 3;
            this.button1.Text = "ENVIAR\r\n";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 42);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(68, 17);
            this.label1.TabIndex = 4;
            this.label1.Text = "NOMBRE";
            // 
            // nombre
            // 
            this.nombre.Location = new System.Drawing.Point(86, 42);
            this.nombre.Name = "nombre";
            this.nombre.Size = new System.Drawing.Size(168, 22);
            this.nombre.TabIndex = 5;
            this.nombre.TextChanged += new System.EventHandler(this.nombre_TextChanged);
            // 
            // altura
            // 
            this.altura.AutoSize = true;
            this.altura.Location = new System.Drawing.Point(15, 197);
            this.altura.Name = "altura";
            this.altura.Size = new System.Drawing.Size(354, 21);
            this.altura.TabIndex = 6;
            this.altura.TabStop = true;
            this.altura.Text = "posicion final de la persona que ha recibido mas +4";
            this.altura.UseVisualStyleBackColor = true;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 83);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(63, 17);
            this.label2.TabIndex = 7;
            this.label2.Text = "ALTURA";
            // 
            // alturaBox
            // 
            this.alturaBox.Location = new System.Drawing.Point(86, 80);
            this.alturaBox.Name = "alturaBox";
            this.alturaBox.Size = new System.Drawing.Size(50, 22);
            this.alturaBox.TabIndex = 8;
            this.alturaBox.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // conectar
            // 
            this.conectar.Location = new System.Drawing.Point(-9, 1);
            this.conectar.Name = "conectar";
            this.conectar.Size = new System.Drawing.Size(206, 23);
            this.conectar.TabIndex = 9;
            this.conectar.Text = "CONECTAR";
            this.conectar.UseVisualStyleBackColor = true;
            this.conectar.Click += new System.EventHandler(this.button2_Click);
            // 
            // desconectar
            // 
            this.desconectar.Location = new System.Drawing.Point(196, 1);
            this.desconectar.Name = "desconectar";
            this.desconectar.Size = new System.Drawing.Size(173, 23);
            this.desconectar.TabIndex = 10;
            this.desconectar.Text = "DESCONECTAR";
            this.desconectar.UseVisualStyleBackColor = true;
            this.desconectar.Click += new System.EventHandler(this.button3_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(364, 286);
            this.Controls.Add(this.desconectar);
            this.Controls.Add(this.conectar);
            this.Controls.Add(this.alturaBox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.altura);
            this.Controls.Add(this.nombre);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.Bonito);
            this.Controls.Add(this.Longitud);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RadioButton Longitud;
        private System.Windows.Forms.RadioButton Bonito;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox nombre;
        private System.Windows.Forms.RadioButton altura;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox alturaBox;
        private System.Windows.Forms.Button conectar;
        private System.Windows.Forms.Button desconectar;
    }
}

