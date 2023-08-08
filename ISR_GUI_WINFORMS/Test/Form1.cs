using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Text;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.AxHost;
using System.Numerics;

namespace Test
{
    public partial class Display : Form
    {
        // Default Values
        public int numTargets = 10;
        public int targetMotion = 5;
        public double nogoOffset = 0;
        public string searchPattern = "Hold";
        public string color = "Red";
        Random rnd = new Random();
        UserAircraft aircraft;
        private Size dotSize = new Size(10, 10);  // Size of the dot
        private Timer timer;
        public List<TargetShip> targetShips = new List<TargetShip>();
        // Define the boundary
        private Rectangle boundary = new Rectangle(400, 100, 500, 500);
        public Display()
        {
            InitializeComponent();
            startButton.Click += async (sender, args) => await DoMathAsync();
            timer = new Timer();
            timer.Interval = 50; // Higher = slower movement (50 = 20ms)
            timer.Tick += Timer_Tick;
            timer.Start();
        }

        // Game Start & Game Loop
        private async Task DoMathAsync()
        {
            // Make targets. Set Id, waypoint, threat level
            targetShips.Clear();
            HashSet<int> usedTargetIds = new HashSet<int>();
            for (int i = 0; i < numTargets; i++)
            {
                int targetId;
                int targetClass = 0;
                int threatClass = 0;
       
                while (true)
                {
                      targetId = rnd.Next() * (10000 - 1000) + 1000;

                      // Ensure that multiple targets do not have the same id
                      if (!usedTargetIds.Contains(targetId))
                      {
                          usedTargetIds.Add(targetId);
                          break;
                      }
                      targetClass = rnd.Next(0, 2);
                      if (targetClass == 0) threatClass = 0;
                      else threatClass = rnd.Next(1, 4); 
                }
                targetShips.Add(new TargetShip(rnd.Next(500), rnd.Next(500), targetMotion, 
                        targetId, targetClass, threatClass, targetShips));
                targetShips[i].SetRandomWaypoint(i);
            }
            DoubleBuffered = true; // Stops the flickering!
            // Make user aircraft. Set path, offset
            if (color == "yellow" || color == "red")
            {
                nogoOffset = 0.2;
            }
            List<Vector> waypoints = new List<Vector>();
            switch (searchPattern.ToLower())
            {
                case "ladder":
                waypoints = new List<Vector>()
                {
                ToSurv(1 - nogoOffset, 0.0/3),
                ToSurv(1 - nogoOffset, 1.0/3),
                ToSurv(0, 1.0/3),
                ToSurv(0, 2.0/3),
                ToSurv(1 - nogoOffset, 2.0/3),
                ToSurv(1 - nogoOffset, 3.0/3),
                ToSurv(0, 3.0/3)
                };
                break;

                case "hold":
                    waypoints = new List<Vector>()
                {
                ToSurv(3.0/4, 0),
                ToSurv(3.0/4, 1),
                ToSurv(1.0/4, 1),
                ToSurv(1.0/4, 0)
                };
                    break;

                case "square":
                    waypoints = new List<Vector>()
                {
                ToSurv(2.0/3, 2.0/4),
                ToSurv(2.0/3, 3.0/4),
                ToSurv(1.0/3, 3.0/4),
                ToSurv(1.0/3, 1.0/4),
                ToSurv(1 - nogoOffset, 1.0/4),
                ToSurv(1 - nogoOffset, 4.0/4),
                ToSurv(0, 4.0/4),
                ToSurv(0, 0),
                ToSurv(1 - nogoOffset, 0)
                };
                break;
            }
            WaypointPath userAircraftPath = new WaypointPath(waypoints);
            Vector userAircraftStart = ToSurv(0, 1);
            aircraft = new UserAircraft(userAircraftStart.X, 
                                                userAircraftStart.Y, userAircraftPath);
            Vector ToSurv(double percentX, double percentY)
            {
                return new Vector(
                    0 + 500 * 0.1 + 500 * 0.8 * percentX, // 0 = zeroX
                    0 + 500 * 0.1 + 500 * 0.8 * percentY // 0 = zeroY
                );
            }

            // Game Loop 
            while (true)
            {
                // Allow for things to happen
                await Task.Delay(TimeSpan.FromMilliseconds(50));
          
                // Do Math
                await Task.Run(() =>
                {
                    
                });

                // Update UI
             /*   Invoke((MethodInvoker)delegate
                {

                });*/
            }
        }
        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            // Draw the boundary
            e.Graphics.DrawRectangle(Pens.Black, boundary);
            if (aircraft != null)
                e.Graphics.DrawEllipse(Pens.Black, new Rectangle(new Point(boundary.Left + 
                    (int)aircraft.X, boundary.Top + (int)aircraft.Y), dotSize)); ;
            // Draw the Ships
            for (int i = 0; i < targetShips.Count; i++) 
            {
                e.Graphics.DrawEllipse(Pens.Blue, new Rectangle(new Point(boundary.Left + 
                    (int)targetShips[i].X, boundary.Top + (int)targetShips[i].Y), dotSize));
            }
            
        }
        private void Timer_Tick(object sender, EventArgs e)
        {
            if (aircraft != null)
                aircraft.Move();
            // Redraw the form
            for (int i = 0; i < targetShips.Count; i++)
            {
                targetShips[i].Move();
            }
            Invalidate();
        }
        private void Display_Load(object sender, EventArgs e)
        {
        }
        private void title_Click(object sender, EventArgs e) { }
        private void parameters_Enter(object sender, EventArgs e)
        {

        }
        private void id_TextChanged(object sender, EventArgs e)
        {

        }
        private void label6_Click(object sender, EventArgs e)
        {

        }
        private void Start_Click(object sender, EventArgs e)
        {
        
        }
        private void seed_KeyDown(object sender, KeyEventArgs e)
        {
        }

        // Update Gameplay Initialization Values
        private void targets_SelectedIndexChanged(object sender, EventArgs e)
        {
            numTargets = (int)targetNumber.SelectedItem;

        }
        private void motion_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (speed.SelectedItem == "Random")
            {
                double r = rnd.NextDouble();
                if (r <= 0.5)
                {
                    targetMotion = 0;
                }
                else if (r <= 0.8)
                {
                    targetMotion = 5;
                }
                else if (r <= 0.95)
                {
                    targetMotion = 5;
                }
                else if (r <= 1)
                {
                    targetMotion = 15;
                }
            }
            else targetMotion = (int)speed.SelectedItem;
        }
        private void pattern_SelectedIndexChanged(object sender, EventArgs e)
        {
            searchPattern = (string)pattern.SelectedItem;
        }
        private void gameColor_SelectedIndexChanged(object sender, EventArgs e)
        {
            color = (string)gameColor.SelectedItem;
        }
    }
    public class TargetShip
    {
        // Motion
        public double X { get; set; }
        public double Y { get; set; }
        public double Speed { get; set; }
        public double DirTheta { get; set; }
        public double WaypointX { get; set; }
        public double WaypointY { get; set; }
        public double RunningDistanceFromWaypoint { get; set; }

        // Information
        public int Id { get; set; }
        public int TargetClass { get; set; }
        public int ThreatClass { get; set; }
        public bool SeenTargetClass { get; set; }
        public bool MousedOver { get; set; }
        public bool CurrentlyMousedOver { get; set; }
        public List<string> TextLines { get; set; }

        // Alerting
        public bool IsVisible { get; set; }

        public TargetShip(double startX, double startY, double speed, int id, int targetClass, int threatClass, List<TargetShip> list)
        {
            // Motion
            X = startX;
            Y = startY;
            Speed = speed;
            DirTheta = -1;
            SetRandomWaypoint((int)Y);
            RunningDistanceFromWaypoint = double.PositiveInfinity;

            // Information
            Id = id;
            TargetClass = targetClass;
            ThreatClass = threatClass;
            SeenTargetClass = false;
            MousedOver = false;
            CurrentlyMousedOver = false;
            TextLines = new List<string>();
            UpdateText();

            // Alerting
            IsVisible = false;
        }

        
        public void RenderText(object ctx)
        {
            // Implement text rendering 
        }
        
        public void UpdateText()
        {
            TextLines.Clear();
            TextLines.Add("Track" + Id);
            TextLines.Add("Position:");
            TextLines.Add("(" + X + "," + Y + ")");
            int rangeType = 1; // userAircraft.getRangeType(this);
            if (rangeType == 1 || rangeType == 2 || SeenTargetClass)
            {
                TextLines.Add("Speed: " + Speed + " knts");
                TextLines.Add("Target Class: " + TargetClass);
            // Visual
            if (rangeType == 1)
            {
                TextLines.Add("Threat Class: UKN");
            }
            else if (rangeType == 2)
            {
                TextLines.Add("Threat Class: " + ThreatClass);
            }
            }
        } 
        public double distance(double x1, double x2, double y1, double y2)
        {
            return Math.Sqrt(Math.Pow(x2 - x1, 2) + Math.Pow(y2 - y1, 2));
        }
        public void Move()
        {
            int dist = (int)distance(X, WaypointX, Y, WaypointY);
            if (dist > RunningDistanceFromWaypoint)
            {
                SetRandomWaypoint((int)X);
                return;
            }
            else
            {
                RunningDistanceFromWaypoint = dist;
            }

            if (DirTheta == -1)
            {
                DirTheta = Math.Atan2(WaypointY - Y, WaypointX - X);
            }

            X += 5.0 * (Speed / 10.0) * Math.Cos(DirTheta) * 50.0 / 1000.0;
            Y += 5.0 * (Speed / 10.0) * Math.Sin(DirTheta) * 50.0 / 1000.0;
            UpdateText();
        }
        public void SetRandomWaypoint(int index)
        {
            Random rnd = new Random(index);
            WaypointX = 0 + rnd.Next(500); // 0 was 50, don't know if it makes a difference
            WaypointY = 0 + rnd.Next(500);
            RunningDistanceFromWaypoint = double.PositiveInfinity;
        }
    }
    public class Vector
    {
        public double X { get; set; }
        public double Y { get; set; }

        public Vector(double x, double y)
        {
            X = x;
            Y = y;
        }

        public static double Distance(Vector a, Vector b)
        {
            return Math.Sqrt(Math.Pow(b.X - a.X, 2) + Math.Pow(b.Y - a.Y, 2));
        }

        public double DistanceTo(Vector other)
        {
            return Distance(this, other);
        }

        public double AngleTo(Vector other)
        {
            double theta = Math.Atan2(other.Y - this.Y, other.X - this.X);
            if (theta < 0)
            {
                theta += 2 * Math.PI;
            }
            theta += Math.PI / 2;
            theta %= 2 * Math.PI;
            return theta;
        }
    }
    public class Waypoint
    {
        public Vector Position { get; set; }
        public WaypointPath Path { get; set; }
        public int TimesCompleted { get; set; }

        public Waypoint(double x, double y, WaypointPath path)
        {
            Position = new Vector((float)x, (float)y);
            Path = path;
            TimesCompleted = 0;
        }
    }
    public class WaypointPath
    {
        public List<Waypoint> Waypoints { get; set; }
        public int CurrentWaypointIndex { get; set; }
        public Waypoint CurrentWaypoint { get; set; }

        public WaypointPath(List<Vector> points)
        {
            Waypoints = new List<Waypoint>();
            foreach (var point in points)
            {
                Waypoints.Add(new Waypoint(point.X, point.Y, this));
            }
            CurrentWaypointIndex = 0;
            CurrentWaypoint = Waypoints[0];
        }

        public double GetDirection(double x, double y)
        {
            // Check if the object has arrived at the current waypoint target
            var distance = Vector.Distance(CurrentWaypoint.Position, new Vector((float)x, (float)y));
            if (distance <= 500 * 0.01) // 500 = canvas length
            {
                // Start the next waypoint target
                CurrentWaypointIndex++;
                if (CurrentWaypointIndex == Waypoints.Count)
                {
                    CurrentWaypoint.TimesCompleted++;
                    CurrentWaypointIndex = 0;
                }
                CurrentWaypoint = Waypoints[CurrentWaypointIndex];
            }

            // Get the angle
            double theta = Math.Atan2((CurrentWaypoint.Position.Y - y), (CurrentWaypoint.Position.X - x));
            if (theta < 0) { theta += 2 * Math.PI; }
            theta += Math.PI / 2; // Canvas rotation starts 0deg as up
            theta %= 2 * Math.PI;
            return theta;
        }
    }
    public class UserAircraft
    {
        public double X { get; set; }
        public double Y { get; set; }
        public double Speed { get; set; }
        public double Rotation { get; set; }
        public double RunningDistanceFromWaypoint { get; set; }
        public WaypointPath Path { get; set; } 

        public UserAircraft(double startX, double startY, WaypointPath path)
        {
            X = startX;
            Y = startY;
            Path = path;

            Speed = 2;
            Rotation = 0;
            RunningDistanceFromWaypoint = 999;
        }

        public void Move()
        {
            Rotation = GetDirectionFromPath();
            X += (int)(20 * Speed * Math.Cos(Rotation - Math.PI / 2) * 50.0 / 1000.0);
            Y += (int)(20 * Speed  * Math.Sin(Rotation - Math.PI / 2) * 50.0 / 1000.0);
        }
        public int GetRangeType(TargetShip target)
        {
            double distanceToTarget = Distance(X, target.X, Y, target.Y);

            double theta = Math.Atan2((target.Y - Y), (target.X - X));
            theta -= Rotation;
            if (theta < 0) { theta += 2 * Math.PI; }
            theta %= 2 * Math.PI;

            if (distanceToTarget <= 500 * 0.3)
            {
                return 2; // visual
            }
            else if (distanceToTarget <= 500 * 0.5 && theta > Math.PI && theta < 2 * Math.PI)
            {
                return 1; // isar
            }
            else
            {
                return 0; // none
            }
        }
        public double Distance(double x1, double x2, double y1, double y2)
        {
            return Math.Sqrt(Math.Pow(x2 - x1, 2) + Math.Pow(y2 - y1, 2));
        }
        public double GetDirectionFromPath()
        {
            return Path.GetDirection(X, Y);
        }
    }
}
