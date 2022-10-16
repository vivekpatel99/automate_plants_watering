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
    uvicorn main:app --host 0.0.0.0
    http://Raspberry.pi.IP.Address/moisture/1

TODO : learn about schemas
"""
from fastapi import FastAPI

from core.helper import update_plants_info
from routes import ROUTES
import rasp_spi

app = FastAPI()


# -------------------------------------------------------
@app.get(ROUTES.ROOT)
async def root():
    return {"message": "Hello Plants"}


# -------------------------------------------------------
@app.get(ROUTES.ALL_IDS)
async def all_ids():
    plants_info_tuple = update_plants_info().plants
    return {"IDs": f"{plants_info_tuple}"}


# -------------------------------------------------------
@app.get(ROUTES.MOISTURE)
async def moisture(id: str):
    plants_info_tuple = update_plants_info().plants
    moisture_percent = 0
    for plant in plants_info_tuple:
        if plant.id == int(id):
            moisture_percent = plant.moisture_percent

    if not moisture_percent == 0:
        return {f"Moisture Sensor id:{id} ": f"{moisture_percent}%"}
    else:
        return {f"ERROR Moisture Sensor id:{id} ": f"{moisture_percent}%"}

# # -------------------------------------------------------
# @app.get(ROUTES.PUMP_PERCENTAGE)
# async def pump_percentage():
#     return {"message": "pump_percentage"}


# -------------------------------------------------------
# @app.get(ROUTES.NEXT_WATER_TIME)
# async def next_water_time():
#     return {"message": "next_water_time"}


# # -------------------------------------------------------
# @app.post(ROUTES.PUMP_ON)
# async def pump_on():
#     return {"message": "pump_on"}
#
#
# # -------------------------------------------------------
# @app.post(ROUTES.PUMP_OFF)
# async def pump_off():
#     return {"message": "pump_off"}
#
#
# # -------------------------------------------------------
# @app.post(ROUTES.UPDATE_PUMP_PERCENTAGE)
# async def update_pump_percentage():
#     return {"message": "update_pump_percentage"}
#
#
# # -------------------------------------------------------
# @app.post(ROUTES.UPDATE_ALL_PUMPS_PERCENTAGE)
# async def update_all_pumps_percentage():
#     return {"message": "update_all_pumps_percentage"}
#
#
# # -------------------------------------------------------
# @app.post(ROUTES.ALL_PUMPS_OFF)
# async def all_pumps_off():
#     return {"message": "all_pumps_off"}
#
#
# # -------------------------------------------------------
# @app.post(ROUTES.ALL_PUMPS_ON)
# async def all_pumps_on():
#     return {"message": "all_pumps_on"}
