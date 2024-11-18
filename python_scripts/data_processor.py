import math
import numpy as np
from scipy.interpolate import griddata

def prepare_data(data):
    """Prepare the weather data for analysis."""
    vanes_data = {
        "x": [],
        "y": [],
        "wind_u": [],
        "wind_v": [],
    }
    stations_data = {
        "x": [],
        "y": [],
        "wind_u": {},
        "wind_v": {},
        "temperature": {},
        "pressure": {},
    }

    def make_wind_vector(wind_speed, wind_direction):
        normalized_speed = wind_speed / 20.0
        u = normalized_speed * math.cos(math.radians(wind_direction))
        v = normalized_speed * math.sin(math.radians(wind_direction))
        return u, v

    for station in data:
        x, y = station["x"], station["y"]
        match station["type"]:
            case "Weathervane":
                vanes_data["x"].append(x)
                vanes_data["y"].append(y)
                wind_speed, wind_direction = station["wind_speed"], station["wind_direction"]
                u, v = make_wind_vector(wind_speed, wind_direction)
                vanes_data["wind_u"].append(u)
                vanes_data["wind_v"].append(v)
            case "Meteostation":
                stations_data["x"].append(x)
                stations_data["y"].append(y)
                for num_of_day, day_data in enumerate(station["data"], start=1):
                    day_key = f"day_{num_of_day}"
                    if day_key not in stations_data["wind_u"]:
                        stations_data["wind_u"][day_key] = []
                        stations_data["wind_v"][day_key] = []
                        stations_data["temperature"][day_key] = []
                        stations_data["pressure"][day_key] = []

                    wind_speed, wind_direction = day_data[0], day_data[1]
                    u, v = make_wind_vector(wind_speed, wind_direction)
                    temperature = day_data[2]
                    pressure = day_data[3]

                    stations_data["wind_u"][day_key].append(u)
                    stations_data["wind_v"][day_key].append(v)
                    stations_data["temperature"][day_key].append(temperature)
                    stations_data["pressure"][day_key].append(pressure)

    return vanes_data, stations_data


def interpolate_data(stations_data, num_interp_points=50):
    """Interpolate temperature and pressure data."""
    xi = np.linspace(min(stations_data["x"]), max(stations_data["x"]), num_interp_points)
    yi = np.linspace(min(stations_data["y"]), max(stations_data["y"]), num_interp_points)
    xi, yi = np.meshgrid(xi, yi)

    temperature_interp_all_days = {}
    pressure_interp_all_days = {}

    for day in stations_data["temperature"].keys():
        temperature_interp_all_days[day] = griddata(
            (stations_data["x"], stations_data["y"]),
            stations_data["temperature"][day],
            (xi, yi), method='cubic'
        )
        
        pressure_interp_all_days[day] = griddata(
            (stations_data["x"], stations_data["y"]),
            stations_data["pressure"][day],
            (xi, yi), method='cubic'
        )

    return xi, yi, temperature_interp_all_days, pressure_interp_all_days