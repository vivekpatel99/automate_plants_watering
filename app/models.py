from pydantic import BaseModel
from pydantic.dataclasses import dataclass
from pydantic import Field
import dataclasses
from datetime import datetime


class Plant(BaseModel):
    id: int
    moisture_percent: int = 0
    pump_percent: int

    # next_water_time: datetime
    def __post_init__(self, moisture_percent):
        ...


plant0 = Plant(id=0, pump_percent=40)

# Plant1 = Plant(id=1, pump_percent=50)


# @dataclass
# class Plants:
#     plants: list[Plant] = [Plant0]
