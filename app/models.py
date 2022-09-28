from pydantic import BaseModel
from datetime import datetime


class Plant(BaseModel):
    id: int
    moisture_percent: int
    pump_percent: int
    next_water_time: datetime


class Plants(BaseModel):
    plants: dict
