import json
from plotly.subplots import make_subplots
import plotly.graph_objects as go
import plotly.figure_factory as ff
import math
import numpy as np
from scipy.interpolate import griddata
import os


def make_wind_vector(wind_speed, wind_direction):
    normalized_speed = wind_speed / 20.0
    u = normalized_speed * math.cos(math.radians(wind_direction))
    v = normalized_speed * math.sin(math.radians(wind_direction))
    return (u, v)

vanes_data = {
    "x" : [],
    "y" : [],
    "wind_u" : [],
    "wind_v" : [],
}
stations_data = {
    "x" : [],
    "y" : [],
    "wind_u" : {},
    "wind_v" : {},
    "temperature" : {},
    "pressure" : {},
}

output_dir = "D:/oop_3_work/build/"
os.makedirs(output_dir, exist_ok=True)

filepath="D:/oop_3_work/data_json/data.json"
try:
    with open(filepath, 'r') as f:
        data = json.load(f)
except FileNotFoundError:
    print(f"Error: File '{filepath}' not found.")
    exit()
except json.JSONDecodeError:
    print(f"Error: Invalid JSON format in '{filepath}'.")
    exit()

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


num_interp_points = 50  #количество точек для интерполяции. Можно регулировать
xi = np.linspace(min(stations_data["x"]), max(stations_data["x"]), num_interp_points)
yi = np.linspace(min(stations_data["y"]), max(stations_data["y"]), num_interp_points)
xi, yi = np.meshgrid(xi, yi)

# Интерполируем температуру и давление
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


# --- Temperature Surface Plot ---
fig_temp = go.Figure()

for day in temperature_interp_all_days.keys():
    fig_temp.add_trace(go.Surface(
        visible=False,
        x=xi, y=yi, z=temperature_interp_all_days[day],
        colorscale='Viridis', showscale=True
    ))

fig_temp.data[0].visible = True

# Include buttons for each day
buttons = []
for i, day in enumerate(temperature_interp_all_days.keys()):
    buttons.append(dict(
        label=day,
        method="update",
        args=[{"visible": [j == i for j in range(len(fig_temp.data))]}],
    ))

fig_temp.update_layout(
    title="Temperature Surface",
    updatemenus=[dict(type="buttons", buttons=buttons)]
)
fig_temp.update_scenes(aspectratio=dict(x=1, y=1, z=0.4))
fig_temp.write_html(os.path.join(output_dir,"temperature_surface.html"), auto_open=True)

# --- Pressure Surface Plot ---
fig_pres = go.Figure()

for day in pressure_interp_all_days.keys():
    fig_pres.add_trace(go.Surface(
        visible=False,
        x=xi, y=yi, z=pressure_interp_all_days[day],
        colorscale='Viridis', showscale=True
    ))

fig_pres.data[0].visible = True

buttons = []
for i, day in enumerate(pressure_interp_all_days.keys()):
    buttons.append(dict(
        label=day,
        method="update",
        args=[{"visible": [j == i for j in range(len(fig_pres.data))]}],
    ))

fig_pres.update_layout(
    title="Pressure Surface",
    updatemenus=[dict(type="buttons", buttons=buttons)]
)
fig_pres.update_scenes(aspectratio=dict(x=1, y=1, z=0.4))
fig_pres.write_html(os.path.join(output_dir,"pressure_surface.html"), auto_open=True)


# --- Wind Vector Plot ---
# Determine the last day available in the data, which we'll consider as "Today"
all_days = list(stations_data["wind_u"].keys())
today = all_days[-1]

fig_wind = go.Figure()

# Create traces for previous days without vanes_data
for day in all_days[:-1]:
    quiver_figure = ff.create_quiver(
        x=stations_data["x"],
        y=stations_data["y"],
        u=stations_data["wind_u"][day],
        v=stations_data["wind_v"][day],
        scale=0.1,  # Adjust according to your preference for arrow sizes
        name=day
    )
    for trace in quiver_figure.data:
        fig_wind.add_trace(trace)

# Create trace for "Today" with vanes_data included
quiver_figure_today = ff.create_quiver(
    x=stations_data["x"] + vanes_data["x"],
    y=stations_data["y"] + vanes_data["y"],
    u=stations_data["wind_u"][today] + vanes_data["wind_u"],
    v=stations_data["wind_v"][today] + vanes_data["wind_v"],
    scale=0.1,
    name="Today",
    scaleratio=1
)


for trace in quiver_figure_today.data:
    fig_wind.add_trace(trace)

# Default visibility setting: only the "Today" trace is initially visible
for i, trace in enumerate(fig_wind.data):
    trace.visible = False
# Make the traces corresponding to "Today" visible
for i in range(len(quiver_figure_today.data)):
    fig_wind.data[len(fig_wind.data) - len(quiver_figure_today.data) + i].visible = True

# Add buttons for each day including "Today"
buttons = []
for i, day in enumerate(all_days[:-1]):
    buttons.append(dict(
        label=day,
        method="update",
        args=[{"visible": [False] * len(fig_wind.data)}]  # Reset visibility
    ))
    # Make the respective day's trace visible
    for j in range(len(quiver_figure.data)):
        buttons[i]["args"][0]["visible"][i * len(quiver_figure.data) + j] = True

# Add "Today" button separately
buttons.append(dict(
    label="Today",
    method="update",
    args=[{"visible": [False] * len(fig_wind.data)},]  # Reset visibility
))

# Make the "Today" trace visible
for i in range(len(quiver_figure_today.data)):
    buttons[-1]["args"][0]["visible"][len(fig_wind.data) - len(quiver_figure_today.data) + i] = True

fig_wind.update_layout(
    title="Wind Vectors",
    updatemenus=[dict(type="buttons", buttons=buttons)],
    width=1200, height=1200,
)


# Writing to HTML
fig_wind.write_html(os.path.join(output_dir, "wind_vectors.html"), auto_open=True)
