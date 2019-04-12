/*************************************************************************
* Testing sketch for Freematics OBD-II I2C Adapter
* Reads and prints several OBD-II PIDs value and MEMS sensor data
* Distributed under GPL v2.0
* Visit http://freematics.com for more information
* Written by Stanley Huang <support@freematics.com.au>
*************************************************************************/

#include <Arduino.h>
#include <OBD.h>

#define WAYOUT SerialUSB

const char PID_names[51][32] = {      //There are 51 names
    "PID_ENGINE_LOAD",                //The longest name has 31 characters (check in excel length =LARGO() )
    "PID_COOLANT_TEMP",
    "PID_SHORT_TERM_FUEL_TRIM_1",
    "PID_LONG_TERM_FUEL_TRIM_1",
    "PID_SHORT_TERM_FUEL_TRIM_2",
    "PID_LONG_TERM_FUEL_TRIM_2",
    "PID_FUEL_PRESSURE",
    "PID_INTAKE_MAP",
    "PID_RPM",
    "PID_SPEED",
    "PID_TIMING_ADVANCE",
    "PID_INTAKE_TEMP",
    "PID_MAF_FLOW",
    "PID_THROTTLE",
    "PID_AUX_INPUT",
    "PID_RUNTIME",
    "PID_DISTANCE_WITH_MIL",
    "PID_COMMANDED_EGR",
    "PID_EGR_ERROR",
    "PID_COMMANDED_EVAPORATIVE_PURGE",
    "PID_FUEL_LEVEL",
    "PID_WARMS_UPS",
    "PID_DISTANCE",
    "PID_EVAP_SYS_VAPOR_PRESSURE",
    "PID_BAROMETRIC",
    "PID_CATALYST_TEMP_B1S1",
    "PID_CATALYST_TEMP_B2S1",
    "PID_CATALYST_TEMP_B1S2",
    "PID_CATALYST_TEMP_B2S2",
    "PID_CONTROL_MODULE_VOLTAGE",
    "PID_ABSOLUTE_ENGINE_LOAD",
    "PID_AIR_FUEL_EQUIV_RATIO",
    "PID_RELATIVE_THROTTLE_POS",
    "PID_AMBIENT_TEMP",
    "PID_ABSOLUTE_THROTTLE_POS_B",
    "PID_ABSOLUTE_THROTTLE_POS_C",
    "PID_ACC_PEDAL_POS_D",
    "PID_ACC_PEDAL_POS_E",
    "PID_ACC_PEDAL_POS_F",
    "PID_COMMANDED_THROTTLE_ACTUATOR",
    "PID_TIME_WITH_MIL",
    "PID_TIME_SINCE_CODES_CLEARED",
    "PID_ETHANOL_FUEL",
    "PID_FUEL_RAIL_PRESSURE",
    "PID_HYBRID_BATTERY_PERCENTAGE",
    "PID_ENGINE_OIL_TEMP",
    "PID_FUEL_INJECTION_TIMING",
    "PID_ENGINE_FUEL_RATE",
    "PID_ENGINE_TORQUE_DEMANDED",
    "PID_ENGINE_TORQUE_PERCENTAGE",
    "PID_ENGINE_REF_TORQUE"
};

const byte PID_codes[51] = {     // Each number has its equivalent name in PID_NAMES.

    0x04,    0x05,    0x06,    0x07,    0x08,    0x09,    0x0A,    0x0B,    0x0C,    0x0D,
    0x0E,    0x0F,    0x10,    0x11,    0x1E,    0x1F,    0x21,    0x2C,    0x2D,    0x2E,
    0x2F,    0x30,    0x31,    0x32,    0x33,    0x3C,    0x3D,    0x3E,    0x3F,    0x42,
    0x43,    0x44,    0x45,    0x46,    0x47,    0x48,    0x49,    0x4A,    0x4B,    0x4C,
    0x4D,    0x4E,    0x52,    0x59,    0x5B,    0x5C,    0x5D,    0x5E,    0x61,    0x62,
    0x63
};

COBD obd;

void readPIDs(){ 
  WAYOUT.println("Read PIDS:"); 

  for (unsigned int i = 0; i < sizeof(PID_codes) ; i++){
    WAYOUT.print(millis());
    WAYOUT.print("->\t");
    WAYOUT.print(PID_names[i]);
    WAYOUT.print(" : ");
    if (obd.isValidPID(PID_codes[i]))
    {
      int value;
      obd.readPID(PID_codes[i], value);
      WAYOUT.print(value);
      WAYOUT.println();
    }
    delay(500);
  }
}

void setup()
{
  WAYOUT.begin(115200);
  delay(5000);                                  //delay to start, just to get to see the start

  WAYOUT.println("Testeando setup: ");

  const byte ver = obd.begin();
  WAYOUT.print("OBD version: ");
  WAYOUT.println(ver);
   // initialize OBD-II adapter
  do
  {
    WAYOUT.println("Init...");
  } while (!obd.init());

}

void loop()
{
  WAYOUT.println("Inicio Loop: ");
  readPIDs();
  delay(1300);
}