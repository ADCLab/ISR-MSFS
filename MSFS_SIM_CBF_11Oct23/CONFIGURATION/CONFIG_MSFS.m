%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% CONFIG MSFS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clc
clear
format short e
warning ('off', 'all')
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% GENERAL CONFIGURATION
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% SIM CONTROL MODE: 0 - TRACKING ONLY / 1 - CBFS + TRACKING
SIM_CONTROL_MODE = 0;
% COMMUNICATIONS MODE: 0 - LOCAL / 1 - SERVER
COMMUNICATIONS_MODE = 1;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% MODEL
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
SAMPLING_TIME = 30e-3;
cd ../SOFTWARE_COMPONENTS/MODEL
MODEL_INI = CONFIG_MODEL(SAMPLING_TIME);
cd ../../CONFIGURATION
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% CONTROL
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
cd ../SOFTWARE_COMPONENTS/CONTROL
CONTROL_INI = CONFIG_CONTROL(MODEL_INI,SIM_CONTROL_MODE);
cd ../../CONFIGURATION
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% BUS DEFINITIONS
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
cd ../BUS_DEFINITIONS
BusDefinition(MODEL_INI, 'MODEL_Bus')
BusDefinition(CONTROL_INI, 'CONTROL_Bus')
cd ../CONFIGURATION
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% SIMULINK MODEL CONFIGURATION
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
cd ('../SIMULINK')
PC_SLX = 'PC_MSFS_STATION';
open(PC_SLX)
set_param(PC_SLX, 'FixedStep', num2str(MODEL_INI.PARAM.SIM_SAMPLING_TIME));
set_param(PC_SLX, 'StopTime', num2str(MODEL_INI.PARAM.SIM_FINAL_TIME));
% set_param([PC_MSFS_STATION 'SUBSYSTEM_NAME'], 'Commented', 'on');
set_param(PC_SLX, 'SimulationMode', 'Normal');
if (COMMUNICATIONS_MODE == 0)
    set_param('PC_MSFS_STATION/MSFS/COMMUNICATIONS/LOCAL COMMUNICATIONS', 'Commented', 'off');
    set_param('PC_MSFS_STATION/MSFS/COMMUNICATIONS/SERVER COMMUNICATIONS', 'Commented', 'on');
else
    set_param('PC_MSFS_STATION/MSFS/COMMUNICATIONS/LOCAL COMMUNICATIONS', 'Commented', 'on');
    set_param('PC_MSFS_STATION/MSFS/COMMUNICATIONS/SERVER COMMUNICATIONS', 'Commented', 'off');
end


