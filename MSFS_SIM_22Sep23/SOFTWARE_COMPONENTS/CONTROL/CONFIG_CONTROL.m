function [CONTROL] = CONFIG_CONTROL(MODEL)
%--------------------------------------------------------------------------
% GENERAL PARAMETERS
%--------------------------------------------------------------------------
% Control sampling time (s)
ts = MODEL.PARAM.SAMPLING_TIME;
CONTROL.PARAM.SAMPLING_TIME = ts;
CONTROL.PARAM.TAU_MAX = 20;  %%%% NEW! - PTS %%%%
CONTROL.PARAM.SIM_TIME = 0;
CONTROL.PARAM.FLIGHT_STATUS = 0;
CONTROL.PARAM.TIMER = 0;

%--------------------------------------------------------------------------
% SAFETY FILTERS PARAMETERS
%--------------------------------------------------------------------------
CONTROL.PARAM.TIME_SAFE = 60; 
CONTROL.PARAM.TIME_NU_ACT = 30; %%%% NEW! - PTS %%%%
CONTROL.PARAM.DIST_THRESHOLD = 1*10e2; % Radious of 1000 ft to detect target
CONTROL.PARAM.DIST_CRITICAL = 100; % Can't get closer than 100 ft radious to target 
CONTROL.PARAM.DIST_GOAL = 1; % WP achieved within 1 ft distance
CONTROL.PARAM.WP_THRESHOLD = 0;
CONTROL.PARAM.WP_TIMER = 0;
CONTROL.PARAM.MU_MAX = 1; %%%% NEW! - PTS %%%%
CONTROL.PARAM.CBF_CONST = 1*10e-3; %%%% NEW! - PTS %%%%
CONTROL.PARAM.CBF_CONST2 = 1*10e-2; %%%% NEW! - PTS %%%%
CONTROL.PARAM.PTS_ACTIVE_FLAG = 0; %%%% NEW! - PTS %%%%
CONTROL.PARAM.CBF_ACTIVE_FLAG = 1;
CONTROL.PARAM.FVAL = 0;
CONTROL.PARAM.EXITVAL = 0;
CONTROL.PARAM.CBF_H = 0;
CONTROL.PARAM.CBF_PSI = 0;

CONTROL.PARAM.CLASSK = 0;%%%% NEW! - PTS %%%%
CONTROL.PARAM.MU2 = 0;%%%% NEW! - PTS %%%%
CONTROL.PARAM.T_REM = 0;%%%% NEW! - PTS %%%%
%--------------------------------------------------------------------------
% INITIALZIATION
%--------------------------------------------------------------------------
CONTROL.PARAM.NAV_D_1 = 10;
CONTROL.PARAM.NAV_D_2 = 10;
% Aircraft Altitude (feet)
CONTROL.PARAM.ALTITUDE = 1.5e3;
CONTROL.PARAM.RHO = 20.902e6 + CONTROL.PARAM.ALTITUDE;
%CONTROL.OUTPUT.ALTITUDE = 0;
CONTROL.PARAM.VERTICAL_SPEED =17; % (feet/s)
%--------------------------------------------------------------------------
% CONTROL TARGET
%--------------------------------------------------------------------------
CONTROL.TARGET.VELOCITY = 100*0.5; % Helicopter
CONTROL.TARGET.WP_INDEX = 1;
CONTROL.TARGET.SIMU_END = 0;
% CONTROL.TARGET.TARGET_POS1 = zeros(2,1);
% CONTROL.TARGET.TARGET_POS2 = zeros(2,1);
CONTROL.TARGET.LATITUDE = 0;
CONTROL.TARGET.LONGITUDE = 0;
% rho = 20.902e6 + 2*10e2; % During flight 
% TARGET_POS1(1) = rho*cos(phi_lat)*cos(theta_long);
% TARGET_POS2(1) = rho*cos(phi_lat)*sin(theta_long);

% CHILDRN HLTH CARE ATL SCOTTISH RITE
% LAT: 33.906866054481476 = 5.9179e-01, LONG: -84.35439102319383= -1.4723e+00
CONTROL.TARGET.TARGET_POS1(1) = 1.7061e+06;
CONTROL.TARGET.TARGET_POS2(1) = -1.7265e+07;

% EMORY UNIVERSITY HOSPITAL MIDTOWN
% LAT: 33.76878595666145 = 5.8938e-01, LOG = -84.38688413060517 = -1.4728e+00
CONTROL.TARGET.TARGET_POS1(2) = 1.7002e+06;
CONTROL.TARGET.TARGET_POS2(2) = -1.7294e+07;

% % WP 1: LAT = 0.589, LONG = -1.47
% CONTROL.TARGET.TARGET_POS1(1) = 1.7490e+06;
% CONTROL.TARGET.TARGET_POS2(1) = -1.7293e+07;
% 
% % WP2: LAT = 0.5895 , LONG = -1.47
% CONTROL.TARGET.TARGET_POS1(2) = 1.7485e+06;
% CONTROL.TARGET.TARGET_POS2(2) = -1.7288e+07;
% 
% % WP3: LAT = 0.59 , LONG = -1.469
% CONTROL.TARGET.TARGET_POS1(3) = 1.7651e+06;
% CONTROL.TARGET.TARGET_POS2(3) = -1.7280e+07;

%--------------------------------------------------------------------------
% CONTROL OUTPUT
%--------------------------------------------------------------------------
% Virtual Controller Input Tau1
CONTROL.OUTPUT.TAU1 = 0;
% Virtual Controller Input Tau2
CONTROL.OUTPUT.TAU2 = 0;
% Virtual Nominal Controller Input Tau1
CONTROL.OUTPUT.TAU1_NOM = 0;
% Virtual Nominal Controller Input Tau2
CONTROL.OUTPUT.TAU2_NOM = 0;

% Spherical coordinates relations:
% x1 = rho*cos(phi)*cos(theta)
% x2 = rho*cos(phi)*sin(theta)
% Aircraft Latitude (rad)
CONTROL.OUTPUT.LATITUDE = 0;
% Aircraft Longitude (rad)
CONTROL.OUTPUT.LONGITUDE = 0;
% Aircraft Heading (deg)
CONTROL.OUTPUT.HEADING = 0;
% Aircraft Heading NED (deg)
CONTROL.OUTPUT.HEADING_NED = 0;
% Aircraft Velorcity NED 
CONTROL.OUTPUT.NED_VY1 = 0;
CONTROL.OUTPUT.NED_VY2 = 0;

CONTROL.OUTPUT.AT_WP = 0;
CONTROL.OUTPUT.ALMOST_WP = 0;
CONTROL.PARAM.PREV_WP1 = 0;
CONTROL.PARAM.PREV_WP2 = 0;
return