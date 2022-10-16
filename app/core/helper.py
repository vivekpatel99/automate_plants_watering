"""
update all the plant data.
"""

from app.models import Plants

from app import rasp_spi


def update_plants_info() -> Plants:
    """
    This function will
    * send ID to Tiva and receive moisture value from the sensor
    *
    :return:
    """

    for plant in Plants.plants:
        rasp_spi.send_data(plant.id)
        data = rasp_spi.read_data()
        plant.moisture_percent = data

    return Plants


if __name__ == '__main__':
    update_plants_info()
