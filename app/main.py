"""_summary_
* Required operations
    GET methods
        - get list of all plants IDs
        - get moisture data as per ID
        - get pump opening % as per ID
        - get next watering time as per ID
    POST methods
        - update next watering time as per ID
        - turn on PUMP now as per ID
        - update/change PUMP opening % as per ID
        - TURN OFF watering as per ID
        - TURN ON watering as per ID
        - update/change all PUMPS opening 
        - TURN OFF all watering
        - TURN ON all watering 

_useful command_
    uvicorn main:app --reload
"""
from fastapi import FastAPI
from app.routes import ROUTES
app = FastAPI()

# -------------------------------------------------------
@app.get(ROUTES.ROOT)
async def root():
    return{"message": "Hello Plant"}

# -------------------------------------------------------
@app.get(ROUTES.ALL_IDS)
async def all_ids():
    return{"message": "all_ids"}

# -------------------------------------------------------
@app.get(ROUTES.MOISTURE)
async def moisture():
    return{"message": "moisture"}
# -------------------------------------------------------
@app.get(ROUTES.PUMP_PERCENTAGE)
async def pump_percentage():
    return{"message": "pump_percentage"}

# -------------------------------------------------------
@app.get(ROUTES.NEXT_WATER_TIME)
async def next_water_time():
    return{"message": "next_water_time"}

# -------------------------------------------------------
@app.post(ROUTES.PUMP_ON)
async def pump_on():
    return{"message": "pump_on"}

# -------------------------------------------------------
@app.post(ROUTES.PUMP_OFF)
async def pump_off():
    return{"message": "pump_off"}

# -------------------------------------------------------
@app.post(ROUTES.UPDATE_PUMP_PERCENTAGE)
async def update_pump_percentage():
    return{"message": "update_pump_percentage"}

# -------------------------------------------------------
@app.post(ROUTES.UPDATE_ALL_PUMPS_PERCENTAGE)
async def update_all_pumps_percentage():
    return{"message": "update_all_pumps_percentage"}

# -------------------------------------------------------
@app.post(ROUTES.ALL_PUMPS_OFF)
async def all_pumps_off():
    return{"message": "all_pumps_off"}

# -------------------------------------------------------
@app.post(ROUTES.ALL_PUMPS_ON)
async def all_pumps_on():
    return{"message": "all_pumps_on"}
