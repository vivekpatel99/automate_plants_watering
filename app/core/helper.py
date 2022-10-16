"""
update all the plant data.
"""
import time

from models import Plant, plant0
import rasp_spi


def update_plants_info(_plant: Plant) -> Plant:
    """
    This function will
    * send ID to Tiva and receive moisture value from the sensor
    *
    :return:
    """

    # for plant in Plants.plants:
    # print(plant.id)
    rasp_spi.send_data(_plant.id)
    data = rasp_spi.read_data()

    print(_plant.id, data)
    _plant.moisture_percent = data
    time.sleep(0.1)
    print(_plant.plants)
    return _plant


if __name__ == '__main__':
    update_plants_info(plant0)
