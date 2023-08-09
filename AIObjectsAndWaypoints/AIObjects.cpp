//------------------------------------------------------------------------------
//
//  SimConnect AI Objects sample
//  
//	Description:
//				Adds Non ATC controlled simulation objects.
//				Launch a flight from KSEA - Runway 34R
//				and watch the antics.
//				Press z to create the objects
//				Press x to load them with their waypoint lists
//				Press c to remove the generated objects
//------------------------------------------------------------------------------

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>

#include "SimConnect.h"

int     quit = 0;
HANDLE  hSimConnect = NULL;
DWORD	SHIP1ID = SIMCONNECT_OBJECT_ID_USER;
DWORD   SHIP2ID = SIMCONNECT_OBJECT_ID_USER;
DWORD   SHIP3ID = SIMCONNECT_OBJECT_ID_USER;
DWORD	SHIP4ID = SIMCONNECT_OBJECT_ID_USER;
DWORD   SHIP5ID = SIMCONNECT_OBJECT_ID_USER;
DWORD   SHIP6ID = SIMCONNECT_OBJECT_ID_USER;
DWORD	SHIP7ID = SIMCONNECT_OBJECT_ID_USER;
DWORD   SHIP8ID = SIMCONNECT_OBJECT_ID_USER;
DWORD   SHIP9ID = SIMCONNECT_OBJECT_ID_USER;
DWORD   SHIPKNZYID = SIMCONNECT_OBJECT_ID_USER;

static enum EVENT_ID {
	EVENT_SIM_START,
	EVENT_Z,
	EVENT_X,
	EVENT_C
};

static enum DATA_REQUEST_ID {

	REQUEST_ADD_SHIP1,
	REQUEST_ADD_SHIP2,
	REQUEST_ADD_SHIP3,
	REQUEST_ADD_SHIP4,
	REQUEST_ADD_SHIP5,
	REQUEST_ADD_SHIP6,
	REQUEST_ADD_SHIP7,
	REQUEST_ADD_SHIP8,
	REQUEST_ADD_SHIP9,
	REQUEST_ADD_SHIPKNZY,
	REQUEST_REMOVE_SHIPKNZY,
	REQUEST_REMOVE_SHIP9,
	REQUEST_REMOVE_SHIP8,
	REQUEST_REMOVE_SHIP7,
	REQUEST_REMOVE_SHIP6,
	REQUEST_REMOVE_SHIP5,
	REQUEST_REMOVE_SHIP4,
	REQUEST_REMOVE_SHIP3,
	REQUEST_REMOVE_SHIP2,
	REQUEST_REMOVE_SHIP1
};

static enum GROUP_ID {
	GROUP_ZX,
};

static enum INPUT_ID {
	INPUT_ZX,
};

static enum DEFINITION_ID {
	DEFINITION_WAYPOINT
};

// Set up flags so these operations only happen once
static bool plansSent = false;
static bool	objectsCreated = false;

void sendFlightPlans()
{
	HRESULT hr;
	SIMCONNECT_DATA_WAYPOINT	waypointListShip1[2];	// Ship1 waypoint list
	SIMCONNECT_DATA_WAYPOINT	waypointListShip2[2];	// CruiseShip01 waypoint list
	SIMCONNECT_DATA_WAYPOINT    waypointListShipKNZY[3];
	
	// Ship1 goes down the runway
	waypointListShip1[0].Flags = SIMCONNECT_WAYPOINT_SPEED_REQUESTED;
	waypointListShip1[0].Altitude = 433; //433
	waypointListShip1[0].Latitude = 47 + (25.95 / 60);
	waypointListShip1[0].Longitude = -122 - (18.47 / 60);
	waypointListShip1[0].ktsSpeed = 75;

	waypointListShip1[1].Flags = SIMCONNECT_WAYPOINT_WRAP_TO_FIRST | SIMCONNECT_WAYPOINT_SPEED_REQUESTED;
	waypointListShip1[1].Altitude = 433; //433
	waypointListShip1[1].Latitude = 47 + (26.25 / 60);
	waypointListShip1[1].Longitude = -122 - (18.46 / 60);
	waypointListShip1[1].ktsSpeed = 55;

	// Send the two waypoints to Ship1
	hr = SimConnect_SetDataOnSimObject(hSimConnect, DEFINITION_WAYPOINT, SHIP1ID, 0, ARRAYSIZE(waypointListShip1), sizeof(waypointListShip1[0]), waypointListShip1);

	waypointListShip2[0].Flags = SIMCONNECT_WAYPOINT_SPEED_REQUESTED;
	waypointListShip2[0].Altitude = 0;
	waypointListShip2[0].Latitude = 30 + (25.2 / 60); 
	waypointListShip2[0].Longitude = -81 - (23.24 / 60); 
	waypointListShip2[0].ktsSpeed = 5;

	waypointListShip2[1].Flags = SIMCONNECT_WAYPOINT_WRAP_TO_FIRST | SIMCONNECT_WAYPOINT_SPEED_REQUESTED;
	waypointListShip2[1].Altitude = 0;
	waypointListShip2[1].Latitude = 30 + (24.97 / 60);
	waypointListShip2[1].Longitude = -81 - (23.24 / 60);
	waypointListShip2[1].ktsSpeed = 10;

	// Send the two waypoints to the CruiseShip01
	hr = SimConnect_SetDataOnSimObject(hSimConnect, DEFINITION_WAYPOINT, SHIP2ID, 0, ARRAYSIZE(waypointListShip2), sizeof(waypointListShip2[0]), waypointListShip2);

	waypointListShipKNZY[0].Flags = SIMCONNECT_WAYPOINT_SPEED_REQUESTED;
	waypointListShipKNZY[0].Altitude = 0;
	waypointListShipKNZY[0].Latitude = 32 + (40.5 / 60);
	waypointListShipKNZY[0].Longitude = -117 - (13.25 / 60);
	waypointListShipKNZY[0].ktsSpeed = 50;

	waypointListShipKNZY[1].Flags = SIMCONNECT_WAYPOINT_SPEED_REQUESTED;
	waypointListShipKNZY[1].Altitude = 0;
	waypointListShipKNZY[1].Latitude = 32 + (40.6 / 60);
	waypointListShipKNZY[1].Longitude = -117 - (13 / 60);
	waypointListShipKNZY[1].ktsSpeed = 50;

	waypointListShipKNZY[2].Flags = SIMCONNECT_WAYPOINT_WRAP_TO_FIRST | SIMCONNECT_WAYPOINT_SPEED_REQUESTED;
	waypointListShipKNZY[2].Altitude = 0;
	waypointListShipKNZY[2].Latitude = 32 + (40.75 / 60);
	waypointListShipKNZY[2].Longitude = -117 - (13.75 / 60);
	waypointListShipKNZY[2].ktsSpeed = 50;

	hr = SimConnect_SetDataOnSimObject(hSimConnect, DEFINITION_WAYPOINT, SHIPKNZYID, 0, ARRAYSIZE(waypointListShipKNZY), sizeof(waypointListShipKNZY[0]), waypointListShipKNZY);
}

void setUpSimObjects()
{
	SIMCONNECT_DATA_INITPOSITION Init;
	HRESULT hr;
	int r = rand() % 10 + 1;
	for (int i = 0; i < 10; i++)
	{
		Init.Altitude = 0.0;
		Init.Latitude = 32 + ((40.45 + (i%2-1)*0.06*(rand()%10-2))/ 60);
		Init.Longitude = -117 - ((13.2 + (i%2-1)*0.06*(rand()%10-2))/ 60);	// straight ahead from KNZY
		Init.Pitch = 0.0;
		Init.Bank = 0.0;
		Init.Heading = 0.0;
		Init.OnGround = 1;
		Init.Airspeed = 0;
		hr = SimConnect_AICreateSimulatedObject(hSimConnect, "CargoShip01", Init, REQUEST_ADD_SHIPKNZY);
	}

	// Standard Cruise Ship
	Init.Altitude = 0.0;
	Init.Latitude = 30 + (24.97 / 60);
	Init.Longitude = -81 - (23.24 / 60);
	Init.Pitch = 0.0;
	Init.Bank = 0.0;
	Init.Heading = 0.0;
	Init.OnGround = 1;
	Init.Airspeed = 0;

	hr = SimConnect_AICreateSimulatedObject(hSimConnect, "CruiseShip01", Init, REQUEST_ADD_SHIP1);

	// Larger Cruise Ship
	Init.Altitude = 0.0;
	Init.Latitude = 30 + (24.97 / 60);		// paren num is minutes, .decimal is seconds/60 (~51)
	Init.Longitude = -81 - (23.21 / 60);	// straight ahead from KNRB
	Init.Pitch = 0.0;
	Init.Bank = 0.0;
	Init.Heading = 0.0;
	Init.OnGround = 1;
	Init.Airspeed = 0;
	hr = SimConnect_AICreateSimulatedObject(hSimConnect, "CruiseShip02", Init, REQUEST_ADD_SHIP2);

	// Small Fishing Ship
	Init.Altitude = 0.0;
	Init.Latitude = 30 + (24.97 / 60);		// paren num is minutes, .decimal is seconds/60 (~51)
	Init.Longitude = -81 - (23.27 / 60);	// straight ahead from KNRB
	Init.Pitch = 0.0;
	Init.Bank = 0.0;
	Init.Heading = 0.0;
	Init.OnGround = 1;
	Init.Airspeed = 0;
	hr = SimConnect_AICreateSimulatedObject(hSimConnect, "FishingShip02", Init, REQUEST_ADD_SHIP3);

	// Same size as FS02
	Init.Altitude = 0.0;
	Init.Latitude = 30 + (24.97 / 60);		// paren num is minutes, .decimal is seconds/60 (~51)
	Init.Longitude = -81 - (23.3 / 60);	// straight ahead from KNRB
	Init.Pitch = 0.0;
	Init.Bank = 0.0;
	Init.Heading = 0.0;
	Init.OnGround = 1;
	Init.Airspeed = 0;
	hr = SimConnect_AICreateSimulatedObject(hSimConnect, "FishingShip03", Init, REQUEST_ADD_SHIP4);

	// Largest Yacht, about 1/3 length of CS01
	Init.Altitude = 0.0;
	Init.Latitude = 30 + (24.97 / 60);		// paren num is minutes, .decimal is seconds/60 (~51)
	Init.Longitude = -81 - (23.33 / 60);	// straight ahead from KNRB
	Init.Pitch = 0.0;
	Init.Bank = 0.0;
	Init.Heading = 0.0;
	Init.OnGround = 1;
	Init.Airspeed = 0;
	hr = SimConnect_AICreateSimulatedObject(hSimConnect, "Yacht01", Init, REQUEST_ADD_SHIP5);

	// Same size as Yacht01 -- Substantially larger than fishing ships (?) 
	Init.Altitude = 0.0;
	Init.Latitude = 30 + (24.97 / 60);		// paren num is minutes, .decimal is seconds/60 (~51)
	Init.Longitude = -81 - (23.36 / 60);	// straight ahead from KNRB
	Init.Pitch = 0.0;
	Init.Bank = 0.0;
	Init.Heading = 0.0;
	Init.OnGround = 1;
	Init.Airspeed = 0;
	hr = SimConnect_AICreateSimulatedObject(hSimConnect, "FishingBoat", Init, REQUEST_ADD_SHIP6);

	// Medium sized Yacht
	Init.Altitude = 0.0;
	Init.Latitude = 30 + (24.97 / 60);		// paren num is minutes, .decimal is seconds/60 (~51)
	Init.Longitude = -81 - (23.39 / 60);	// straight ahead from KNRB
	Init.Pitch = 0.0;
	Init.Bank = 0.0;
	Init.Heading = 0.0;
	Init.OnGround = 1;
	Init.Airspeed = 0;
	hr = SimConnect_AICreateSimulatedObject(hSimConnect, "Yacht02", Init, REQUEST_ADD_SHIP7);

	// Smaller Yacht, still larger than Fishing Ships
	Init.Altitude = 0.0;
	Init.Latitude = 30 + (24.97 / 60);		// paren num is minutes, .decimal is seconds/60 (~51)
	Init.Longitude = -81 - (23.42 / 60);	// straight ahead from KNRB
	Init.Pitch = 0.0;
	Init.Bank = 0.0;
	Init.Heading = 0.0;
	Init.OnGround = 1;
	Init.Airspeed = 0;
	hr = SimConnect_AICreateSimulatedObject(hSimConnect, "Yacht03", Init, REQUEST_ADD_SHIP8);

	// Slightly larger than Yacht01 and FB
	Init.Altitude = 0.0;
	Init.Latitude = 30 + (24.97 / 60);		// paren num is minutes, .decimal is seconds/60 (~51)
	Init.Longitude = -81 - (23.45 / 60);	// straight ahead from KNRB
	Init.Pitch = 0.0;
	Init.Bank = 0.0;
	Init.Heading = 0.0;
	Init.OnGround = 1;
	Init.Airspeed = 0;
	hr = SimConnect_AICreateSimulatedObject(hSimConnect, "CargoShip01", Init, REQUEST_ADD_SHIP9);

	Init.Altitude = 0.0;
	Init.Latitude = 32 + (40.45 / 60);
	Init.Longitude = -117 - (13.2 / 60);	// straight ahead from KNRB
	Init.Pitch = 0.0;
	Init.Bank = 0.0;
	Init.Heading = 0.0;
	Init.OnGround = 1;
	Init.Airspeed = 0;
	hr = SimConnect_AICreateSimulatedObject(hSimConnect, "CargoShip01", Init, REQUEST_ADD_SHIPKNZY);
}

void removeSimObjects() {
	
	HRESULT hr;
	if (SHIP1ID != SIMCONNECT_OBJECT_ID_USER) {
		hr = SimConnect_AIRemoveObject(hSimConnect, SHIP1ID, REQUEST_REMOVE_SHIP1);
	}
	if (SHIP2ID != SIMCONNECT_OBJECT_ID_USER) {
		hr = SimConnect_AIRemoveObject(hSimConnect, SHIP2ID, REQUEST_REMOVE_SHIP2);
	}
	if (SHIP3ID != SIMCONNECT_OBJECT_ID_USER) {
		hr = SimConnect_AIRemoveObject(hSimConnect, SHIP3ID, REQUEST_REMOVE_SHIP3);
	}
	if (SHIP4ID != SIMCONNECT_OBJECT_ID_USER) {
		hr = SimConnect_AIRemoveObject(hSimConnect, SHIP4ID, REQUEST_REMOVE_SHIP4);
	}
	if (SHIP5ID != SIMCONNECT_OBJECT_ID_USER) {
		hr = SimConnect_AIRemoveObject(hSimConnect, SHIP5ID, REQUEST_REMOVE_SHIP5);
	}
	if (SHIP6ID != SIMCONNECT_OBJECT_ID_USER) {
		hr = SimConnect_AIRemoveObject(hSimConnect, SHIP6ID, REQUEST_REMOVE_SHIP6);
	}
	if (SHIP7ID != SIMCONNECT_OBJECT_ID_USER) {
			hr = SimConnect_AIRemoveObject(hSimConnect, SHIP7ID, REQUEST_REMOVE_SHIP7);
	}
	if (SHIP8ID != SIMCONNECT_OBJECT_ID_USER) {
			hr = SimConnect_AIRemoveObject(hSimConnect, SHIP8ID, REQUEST_REMOVE_SHIP8);
	}
	if (SHIP9ID != SIMCONNECT_OBJECT_ID_USER) {
			hr = SimConnect_AIRemoveObject(hSimConnect, SHIP9ID, REQUEST_REMOVE_SHIP9);
	}
	if (SHIPKNZYID != SIMCONNECT_OBJECT_ID_USER) {
		hr = SimConnect_AIRemoveObject(hSimConnect, SHIPKNZYID, REQUEST_REMOVE_SHIPKNZY);
	}
}



static const char* ExceptionName(SIMCONNECT_EXCEPTION exception) {
	switch (exception) {
	case SIMCONNECT_EXCEPTION_NONE:				//0
		return "EXCEPTION_NONE (0)";
	case SIMCONNECT_EXCEPTION_ERROR:			//1
		return "EXCEPTION_ERROR (1)";
	case SIMCONNECT_EXCEPTION_SIZE_MISMATCH:	//2
		return "EXCEPTION_SIZE_MISMATCH (2)";
	case SIMCONNECT_EXCEPTION_UNRECOGNIZED_ID:	//3
		return "EXCEPTION_UNRECOGNIZED_ID (3)";
	case SIMCONNECT_EXCEPTION_UNOPENED:			//4
		return "EXCEPTION_UNOPENED (4)";
	case SIMCONNECT_EXCEPTION_VERSION_MISMATCH:	//5
		return "EXCEPTION_VERSION_MISMATCH (5)";
	case SIMCONNECT_EXCEPTION_TOO_MANY_GROUPS:	//6
		return "EXCEPTION_TOO_MANY_GROUPS (6)";
	case SIMCONNECT_EXCEPTION_NAME_UNRECOGNIZED://7
		return "EXCEPTION_NAME_UNRECOGNIZED (7)";
	case SIMCONNECT_EXCEPTION_TOO_MANY_EVENT_NAMES:		//8
		return "EXCEPTION_TOO_MANY_EVENT_NAMES (8)";
	case SIMCONNECT_EXCEPTION_EVENT_ID_DUPLICATE:		//9
		return "EXCEPTION_EVENT_ID_DUPLICATE (9)";
	case SIMCONNECT_EXCEPTION_TOO_MANY_MAPS:			//10
		return "EXCEPTION_TOO_MANY_MAPS (10)";
	case SIMCONNECT_EXCEPTION_TOO_MANY_OBJECTS:			//11
		return "EXCEPTION_TOO_MANY_OBJECTS (11)";
	case SIMCONNECT_EXCEPTION_TOO_MANY_REQUESTS:				//12
		return "EXCEPTION_TOO_MANY_REQUESTS (12)";
	case SIMCONNECT_EXCEPTION_WEATHER_INVALID_PORT:				//13
		return "EXCEPTION_WEATHER_INVALID_PORT (13)";
	case SIMCONNECT_EXCEPTION_WEATHER_INVALID_METAR:			//14
		return "EXCEPTION_WEATHER_INVALID_METAR (14)";
	case SIMCONNECT_EXCEPTION_WEATHER_UNABLE_TO_GET_OBSERVATION://15
		return "EXCEPTION_WEATHER_UNABLE_TO_GET_OBSERVATION (15)";
	case SIMCONNECT_EXCEPTION_WEATHER_UNABLE_TO_CREATE_STATION:	//16
		return "EXCEPTION_WEATHER_UNABLE_TO_CREATE_STATION (16)";
	case SIMCONNECT_EXCEPTION_WEATHER_UNABLE_TO_REMOVE_STATION:	//17
		return "EXCEPTION_WEATHER_UNABLE_TO_REMOVE_STATION (17)";
	case SIMCONNECT_EXCEPTION_INVALID_DATA_TYPE:				//18
		return "EXCEPTION_INVALID_DATA_TYPE (18)";
	case SIMCONNECT_EXCEPTION_INVALID_DATA_SIZE:				//19
		return "EXCEPTION_INVALID_DATA_SIZE (19)";
	case SIMCONNECT_EXCEPTION_DATA_ERROR:						//20
		return "EXCEPTION_DATA_ERROR (20)";
	case SIMCONNECT_EXCEPTION_INVALID_ARRAY:			//21
		return "EXCEPTION_INVALID_ARRAY (21)";
	case SIMCONNECT_EXCEPTION_CREATE_OBJECT_FAILED:		//22
		return "EXCEPTION_CREATE_OBJECT_FAILED (22)";
	case SIMCONNECT_EXCEPTION_LOAD_FLIGHTPLAN_FAILED:	//23
		return "EXCEPTION_LOAD_FLIGHTPLAN_FAILED (23)";
	case SIMCONNECT_EXCEPTION_OPERATION_INVALID_FOR_OBJECT_TYPE://24
		return "EXCEPTION_OPERATION_INVALID_FOR_OBJECT_TYPE (24)";
	case SIMCONNECT_EXCEPTION_ILLEGAL_OPERATION:				//25
		return "EXCEPTION_ILLEGAL_OPERATION (25)";
	case SIMCONNECT_EXCEPTION_ALREADY_SUBSCRIBED:				//26
		return "EXCEPTION_ALREADY_SUBSCRIBED (26)";
	case SIMCONNECT_EXCEPTION_INVALID_ENUM:						//27
		return "EXCEPTION_INVALID_ENUM (27)";
	case SIMCONNECT_EXCEPTION_DEFINITION_ERROR:	//28
		return "EXCEPTION_DEFINITION_ERROR (28)";
	case SIMCONNECT_EXCEPTION_DUPLICATE_ID:		//29
		return "EXCEPTION_DUPLICATE_ID (29)";
	case SIMCONNECT_EXCEPTION_DATUM_ID:			//30
		return "EXCEPTION_DATUM_ID (30)";
	case SIMCONNECT_EXCEPTION_OUT_OF_BOUNDS:	//31
		return "EXCEPTION_OUT_OF_BOUNDS (31)";
	case SIMCONNECT_EXCEPTION_ALREADY_CREATED:	//32
		return "EXCEPTION_ALREADY_CREATED (32)";
	case SIMCONNECT_EXCEPTION_OBJECT_OUTSIDE_REALITY_BUBBLE://33
		return "EXCEPTION_OBJECT_OUTSIDE_REALITY_BUBBLE (33)";
	case SIMCONNECT_EXCEPTION_OBJECT_CONTAINER:				//34
		return "EXCEPTION_OBJECT_CONTAINER (34)";
	case SIMCONNECT_EXCEPTION_OBJECT_AI:					//35
		return "EXCEPTION_OBJECT_AI (35)";
	case SIMCONNECT_EXCEPTION_OBJECT_ATC:					//36
		return "EXCEPTION_OBJECT_ATC (36)";
	case SIMCONNECT_EXCEPTION_OBJECT_SCHEDULE:				//37
		return "EXCEPTION_OBJECT_SCHEDULE (37)";
	default:
		return "UNKNOWN EXCEPTION";
	}
}
void CALLBACK MyDispatchProcSO(SIMCONNECT_RECV* pData, DWORD cbData, void* pContext)
{
	HRESULT hr;

	switch (pData->dwID)
	{
	case SIMCONNECT_RECV_ID_EVENT:
	{
		SIMCONNECT_RECV_EVENT* evt = (SIMCONNECT_RECV_EVENT*)pData;

		switch (evt->uEventID)
		{
		case EVENT_Z:
			if (!objectsCreated)
			{
				setUpSimObjects();
				objectsCreated = true;
				printf("\nPress 'x' to add the waypoints");
			}
			break;

		case EVENT_X:
			if (!plansSent && objectsCreated)
			{
				sendFlightPlans();
				plansSent = true;
			}
			break;
		case EVENT_C:
			if (objectsCreated)
			{
				removeSimObjects();
				objectsCreated = false;
				plansSent = false;
			}
			break;

		default:
			printf("\nUnknown event: %d", evt->uEventID);
			break;
		}
		break;
	}

	case SIMCONNECT_RECV_ID_ASSIGNED_OBJECT_ID:
	{
		SIMCONNECT_RECV_ASSIGNED_OBJECT_ID* pObjData = (SIMCONNECT_RECV_ASSIGNED_OBJECT_ID*)pData;

		switch (pObjData->dwRequestID)
		{
		case REQUEST_ADD_SHIP1:
			SHIP1ID = pObjData->dwObjectID;
			printf("\nCreated Ship1 id = %d", SHIP1ID);
			break;
		case REQUEST_ADD_SHIP2:
			SHIP2ID = pObjData->dwObjectID;
			printf("\nCreated Ship2 id = %d", SHIP2ID);
			break;
		case REQUEST_ADD_SHIP3:
			SHIP2ID = pObjData->dwObjectID;
			printf("\nCreated Ship3 id = %d", SHIP3ID);
			break;
		case REQUEST_ADD_SHIP6:
			SHIP6ID = pObjData->dwObjectID;
			printf("\nCreated Ship1 id = %d", SHIP6ID);
			break;
		case REQUEST_ADD_SHIP5:
			SHIP5ID = pObjData->dwObjectID;
			printf("\nCreated Ship5 id = %d", SHIP5ID);
			break;
		case REQUEST_ADD_SHIP4:
			SHIP4ID = pObjData->dwObjectID;
			printf("\nCreated Ship4 id = %d", SHIP4ID);
			break;
		case REQUEST_ADD_SHIP7:
			SHIP7ID = pObjData->dwObjectID;
			printf("\nCreated Ship7 id = %d", SHIP7ID);
			break;
		case REQUEST_ADD_SHIP8:
			SHIP8ID = pObjData->dwObjectID;
			printf("\nCreated Ship8 id = %d", SHIP8ID);
			break;
		case REQUEST_ADD_SHIP9:
			SHIP9ID = pObjData->dwObjectID;
			printf("\nCreated Ship9 id = %d", SHIP9ID);
			break;
		case REQUEST_ADD_SHIPKNZY:
			SHIPKNZYID = pObjData->dwObjectID;
			printf("\nCreated ShipKNZY id = %d", SHIPKNZYID);
			break;
		default:
			printf("\nUnknown creation %d", pObjData->dwRequestID);
			break;
		}
		break;
	}
	case SIMCONNECT_RECV_ID_QUIT:
	{
		quit = 1;
		break;
	}
	case SIMCONNECT_RECV_ID_EXCEPTION:
	{
		SIMCONNECT_RECV_EXCEPTION* data = (SIMCONNECT_RECV_EXCEPTION*)(pData);
		SIMCONNECT_EXCEPTION exception = (SIMCONNECT_EXCEPTION)(data->dwException);
		printf("\nException: %s", ExceptionName(exception));
		break;
	}
	default:
		printf("\nReceived:%d", pData->dwID);
		break;
	}
}

void testSimObjects()
{
	HRESULT hr;

	if (SUCCEEDED(SimConnect_Open(&hSimConnect, "AI Objects and Waypoints", NULL, 0, 0, 0)))
	{
		printf("\nConnected to Flight Simulator!");

		// Create some private events
		hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_Z);
		hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_X);
		hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_C);

		// Link the private events to keyboard keys, and ensure the input events are off
		hr = SimConnect_MapInputEventToClientEvent(hSimConnect, INPUT_ZX, "Z", EVENT_Z);
		hr = SimConnect_MapInputEventToClientEvent(hSimConnect, INPUT_ZX, "X", EVENT_X);
		hr = SimConnect_MapInputEventToClientEvent(hSimConnect, INPUT_ZX, "C", EVENT_C);

		hr = SimConnect_SetInputGroupState(hSimConnect, INPUT_ZX, SIMCONNECT_STATE_OFF);

		// Sign up for notifications
		hr = SimConnect_AddClientEventToNotificationGroup(hSimConnect, GROUP_ZX, EVENT_Z);
		hr = SimConnect_AddClientEventToNotificationGroup(hSimConnect, GROUP_ZX, EVENT_X);
		hr = SimConnect_AddClientEventToNotificationGroup(hSimConnect, GROUP_ZX, EVENT_C);

		// Set up a definition for a waypoint list
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_WAYPOINT,
			"AI Waypoint List", "number", SIMCONNECT_DATATYPE_WAYPOINT);

		hr = SimConnect_SetInputGroupState(hSimConnect, INPUT_ZX, SIMCONNECT_STATE_ON);
		printf("\nHead straight out towards the ocean, Press 'z' to create the boats");

		printf("\nLaunch a flight.");

		while (0 == quit)
		{
			SimConnect_CallDispatch(hSimConnect, MyDispatchProcSO, NULL);
			Sleep(1);
		}

		hr = SimConnect_Close(hSimConnect);
	}
}


int __cdecl _tmain(int argc, _TCHAR* argv[])
{
	testSimObjects();
	return 0;
}