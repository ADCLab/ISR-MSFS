using System;

namespace Test
{
    partial class Display
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Display));
            this.startButton = new System.Windows.Forms.Button();
            this.targetNumber = new System.Windows.Forms.ComboBox();
            this.numLabel = new System.Windows.Forms.Label();
            this.speedLabel = new System.Windows.Forms.Label();
            this.speed = new System.Windows.Forms.ComboBox();
            this.patternLabel = new System.Windows.Forms.Label();
            this.pattern = new System.Windows.Forms.ComboBox();
            this.colorLabel = new System.Windows.Forms.Label();
            this.gameColor = new System.Windows.Forms.ComboBox();
            this.seedLabel = new System.Windows.Forms.Label();
            this.userLabel = new System.Windows.Forms.Label();
            this.id = new System.Windows.Forms.TextBox();
            this.seed = new System.Windows.Forms.TextBox();
            this.parameters = new System.Windows.Forms.GroupBox();
            this.titleLabel = new System.Windows.Forms.Label();
            this.Alerts = new System.Windows.Forms.ListBox();
            this.parameters.SuspendLayout();
            this.SuspendLayout();
            // 
            // startButton
            // 
            this.startButton.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.startButton.BackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.startButton.Font = new System.Drawing.Font("Roboto", 15F, System.Drawing.FontStyle.Bold);
            this.startButton.Location = new System.Drawing.Point(144, 414);
            this.startButton.Margin = new System.Windows.Forms.Padding(4);
            this.startButton.Name = "startButton";
            this.startButton.Size = new System.Drawing.Size(91, 45);
            this.startButton.TabIndex = 6;
            this.startButton.Text = "Start";
            this.startButton.UseVisualStyleBackColor = false;
            this.startButton.Click += new System.EventHandler(this.Start_Click);
            // 
            // targetNumber
            // 
            this.targetNumber.DisplayMember = "(none)";
            this.targetNumber.FormattingEnabled = true;
            this.targetNumber.Items.AddRange(new object[] {
            10,
            20,
            30,
            50,
            100});
            this.targetNumber.Location = new System.Drawing.Point(285, 162);
            this.targetNumber.MaxLength = 1;
            this.targetNumber.Name = "targetNumber";
            this.targetNumber.Size = new System.Drawing.Size(91, 47);
            this.targetNumber.TabIndex = 2;
            this.targetNumber.SelectedIndexChanged += new System.EventHandler(this.targets_SelectedIndexChanged);
            // 
            // numLabel
            // 
            this.numLabel.AutoSize = true;
            this.numLabel.Font = new System.Drawing.Font("Roboto", 15F, System.Drawing.FontStyle.Bold);
            this.numLabel.Location = new System.Drawing.Point(6, 172);
            this.numLabel.Name = "numLabel";
            this.numLabel.Size = new System.Drawing.Size(245, 30);
            this.numLabel.TabIndex = 3;
            this.numLabel.Text = "Number of Targets:";
            // 
            // speedLabel
            // 
            this.speedLabel.AutoSize = true;
            this.speedLabel.Font = new System.Drawing.Font("Roboto", 15F, System.Drawing.FontStyle.Bold);
            this.speedLabel.Location = new System.Drawing.Point(6, 228);
            this.speedLabel.Name = "speedLabel";
            this.speedLabel.Size = new System.Drawing.Size(178, 30);
            this.speedLabel.TabIndex = 5;
            this.speedLabel.Text = "Target Speed:";
            // 
            // speed
            // 
            this.speed.DisplayMember = "(none)";
            this.speed.FormattingEnabled = true;
            this.speed.Items.AddRange(new object[] {
            0,
            5,
            10,
            15,
            "Random"});
            this.speed.Location = new System.Drawing.Point(285, 218);
            this.speed.MaxLength = 1;
            this.speed.Name = "speed";
            this.speed.Size = new System.Drawing.Size(91, 47);
            this.speed.TabIndex = 3;
            this.speed.SelectedIndexChanged += new System.EventHandler(this.motion_SelectedIndexChanged);
            // 
            // patternLabel
            // 
            this.patternLabel.AutoSize = true;
            this.patternLabel.Font = new System.Drawing.Font("Roboto", 15F, System.Drawing.FontStyle.Bold);
            this.patternLabel.Location = new System.Drawing.Point(6, 282);
            this.patternLabel.Name = "patternLabel";
            this.patternLabel.Size = new System.Drawing.Size(198, 30);
            this.patternLabel.TabIndex = 7;
            this.patternLabel.Text = "Search Pattern:";
            // 
            // pattern
            // 
            this.pattern.DisplayMember = "(none)";
            this.pattern.FormattingEnabled = true;
            this.pattern.Items.AddRange(new object[] {
            "Hold",
            "Ladder",
            "Square"});
            this.pattern.Location = new System.Drawing.Point(285, 272);
            this.pattern.Name = "pattern";
            this.pattern.Size = new System.Drawing.Size(91, 47);
            this.pattern.Sorted = true;
            this.pattern.TabIndex = 4;
            this.pattern.SelectedIndexChanged += new System.EventHandler(this.pattern_SelectedIndexChanged);
            // 
            // colorLabel
            // 
            this.colorLabel.AutoSize = true;
            this.colorLabel.Font = new System.Drawing.Font("Roboto", 15F, System.Drawing.FontStyle.Bold);
            this.colorLabel.Location = new System.Drawing.Point(6, 338);
            this.colorLabel.Name = "colorLabel";
            this.colorLabel.Size = new System.Drawing.Size(210, 30);
            this.colorLabel.TabIndex = 9;
            this.colorLabel.Text = "Gameplay Color:";
            // 
            // gameColor
            // 
            this.gameColor.DisplayMember = "(none)";
            this.gameColor.FormattingEnabled = true;
            this.gameColor.Items.AddRange(new object[] {
            "Red",
            "White",
            "Yellow"});
            this.gameColor.Location = new System.Drawing.Point(285, 328);
            this.gameColor.Name = "gameColor";
            this.gameColor.Size = new System.Drawing.Size(91, 47);
            this.gameColor.Sorted = true;
            this.gameColor.TabIndex = 5;
            this.gameColor.SelectedIndexChanged += new System.EventHandler(this.gameColor_SelectedIndexChanged);
            // 
            // seedLabel
            // 
            this.seedLabel.AutoSize = true;
            this.seedLabel.Font = new System.Drawing.Font("Roboto", 15F, System.Drawing.FontStyle.Bold);
            this.seedLabel.Location = new System.Drawing.Point(6, 116);
            this.seedLabel.Name = "seedLabel";
            this.seedLabel.Size = new System.Drawing.Size(79, 30);
            this.seedLabel.TabIndex = 11;
            this.seedLabel.Text = "Seed:";
            // 
            // userLabel
            // 
            this.userLabel.AutoSize = true;
            this.userLabel.Font = new System.Drawing.Font("Roboto", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.userLabel.Location = new System.Drawing.Point(6, 66);
            this.userLabel.Name = "userLabel";
            this.userLabel.Size = new System.Drawing.Size(106, 30);
            this.userLabel.TabIndex = 10;
            this.userLabel.Text = "User ID:";
            this.userLabel.Click += new System.EventHandler(this.label6_Click);
            // 
            // id
            // 
            this.id.Font = new System.Drawing.Font("Roboto", 15F, System.Drawing.FontStyle.Bold);
            this.id.Location = new System.Drawing.Point(205, 63);
            this.id.Name = "id";
            this.id.Size = new System.Drawing.Size(170, 38);
            this.id.TabIndex = 0;
            this.id.TextChanged += new System.EventHandler(this.id_TextChanged);
            // 
            // seed
            // 
            this.seed.Font = new System.Drawing.Font("Roboto", 15F, System.Drawing.FontStyle.Bold);
            this.seed.Location = new System.Drawing.Point(205, 112);
            this.seed.Name = "seed";
            this.seed.ReadOnly = true;
            this.seed.Size = new System.Drawing.Size(170, 38);
            this.seed.TabIndex = 6;
            this.seed.TabStop = false;
            this.seed.Text = "ONR-ISR";
            // 
            // parameters
            // 
            this.parameters.BackColor = System.Drawing.Color.White;
            this.parameters.Controls.Add(this.speedLabel);
            this.parameters.Controls.Add(this.gameColor);
            this.parameters.Controls.Add(this.seed);
            this.parameters.Controls.Add(this.pattern);
            this.parameters.Controls.Add(this.id);
            this.parameters.Controls.Add(this.speed);
            this.parameters.Controls.Add(this.startButton);
            this.parameters.Controls.Add(this.targetNumber);
            this.parameters.Controls.Add(this.seedLabel);
            this.parameters.Controls.Add(this.numLabel);
            this.parameters.Controls.Add(this.userLabel);
            this.parameters.Controls.Add(this.patternLabel);
            this.parameters.Controls.Add(this.colorLabel);
            this.parameters.Font = new System.Drawing.Font("Roboto", 20F, System.Drawing.FontStyle.Bold);
            this.parameters.Location = new System.Drawing.Point(12, 86);
            this.parameters.Name = "parameters";
            this.parameters.Size = new System.Drawing.Size(381, 473);
            this.parameters.TabIndex = 15;
            this.parameters.TabStop = false;
            this.parameters.Text = "Wargame Parameters";
            this.parameters.Enter += new System.EventHandler(this.parameters_Enter);
            // 
            // titleLabel
            // 
            this.titleLabel.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.titleLabel.AutoSize = true;
            this.titleLabel.Font = new System.Drawing.Font("Roboto", 25F, System.Drawing.FontStyle.Bold);
            this.titleLabel.Location = new System.Drawing.Point(433, 9);
            this.titleLabel.Name = "titleLabel";
            this.titleLabel.Size = new System.Drawing.Size(385, 51);
            this.titleLabel.TabIndex = 16;
            this.titleLabel.Text = "ONR-ISR Wargame";
            this.titleLabel.Click += new System.EventHandler(this.title_Click);
            // 
            // Alerts
            // 
            this.Alerts.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.Alerts.Font = new System.Drawing.Font("Roboto", 20F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Alerts.FormattingEnabled = true;
            this.Alerts.ItemHeight = 39;
            this.Alerts.Location = new System.Drawing.Point(908, 86);
            this.Alerts.Name = "Alerts";
            this.Alerts.Size = new System.Drawing.Size(388, 589);
            this.Alerts.TabIndex = 17;
            this.Alerts.TabStop = false;
            // 
            // Display
            // 
            this.AcceptButton = this.startButton;
            this.AutoScaleDimensions = new System.Drawing.SizeF(11F, 24F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1308, 728);
            this.Controls.Add(this.Alerts);
            this.Controls.Add(this.titleLabel);
            this.Controls.Add(this.parameters);
            this.Font = new System.Drawing.Font("Microsoft YaHei", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "Display";
            this.Text = "ONR-ISR Wargame";
            this.Load += new System.EventHandler(this.Display_Load);
            this.parameters.ResumeLayout(false);
            this.parameters.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button startButton;
        private System.Windows.Forms.ComboBox targetNumber;
        private System.Windows.Forms.Label numLabel;
        private System.Windows.Forms.Label speedLabel;
        private System.Windows.Forms.ComboBox speed;
        private System.Windows.Forms.Label patternLabel;
        private System.Windows.Forms.ComboBox pattern;
        private System.Windows.Forms.Label colorLabel;
        private System.Windows.Forms.ComboBox gameColor;
        private System.Windows.Forms.Label seedLabel;
        private System.Windows.Forms.Label userLabel;
        private System.Windows.Forms.TextBox id;
        private System.Windows.Forms.TextBox seed;
        private System.Windows.Forms.GroupBox parameters;
        private System.Windows.Forms.Label titleLabel;
        private System.Windows.Forms.ListBox Alerts;
    }
}

