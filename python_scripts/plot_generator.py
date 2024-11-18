import os
import plotly.graph_objects as go
import plotly.figure_factory as ff

def create_temperature_plot(xi, yi, temperature_interp_all_days, output_dir):
    """Create and save the temperature surface plot."""
    fig_temp = go.Figure()

    for day in temperature_interp_all_days.keys():
        fig_temp.add_trace(go.Surface(
            visible=False,
            x=xi, y=yi, z=temperature_interp_all_days[day],
            colorscale='Viridis', showscale=True
        ))

    fig_temp.data[0].visible = True

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


def create_pressure_plot(xi, yi, pressure_interp_all_days, output_dir):
    """Create and save the pressure surface plot."""
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



def create_wind_plot(vanes_data, stations_data, output_dir):
    """Create and save the wind vector plot."""
    all_days = list(stations_data["wind_u"].keys())
    today = all_days[-1]

    fig_wind = go.Figure()

    for day in all_days[:-1]:
        quiver_figure = ff.create_quiver(
            x=stations_data["x"],
            y=stations_data["y"],
            u=stations_data["wind_u"][day],
            v=stations_data["wind_v"][day],
            scale=0.1,
            name=day
        )
        for trace in quiver_figure.data:
            fig_wind.add_trace(trace)

    quiver_figure_today = ff.create_quiver(
        x=stations_data["x"] + vanes_data["x"],
        y=stations_data["y"] + vanes_data["y"],
        u=stations_data["wind_u"][today] + vanes_data["wind_u"],
        v=stations_data["wind_v"][today] + vanes_data["wind_v"],
        scale=0.1, # size of vectors
        name="Today",
        scaleratio=1 # xaxis/yaxis = 1
    )

    for trace in quiver_figure_today.data:
        fig_wind.add_trace(trace)

    for i, trace in enumerate(fig_wind.data):
        trace.visible = False
    for i in range(len(quiver_figure_today.data)):
        fig_wind.data[len(fig_wind.data) - len(quiver_figure_today.data) + i].visible = True

    buttons = []
    for i, day in enumerate(all_days[:-1]):
        buttons.append(
            dict(
                label=day,
                method="update",
                args=[{"visible": [False] * len(fig_wind.data)}]  # Reset visibility
            ))
        for j in range(len(quiver_figure.data)):
            buttons[i]["args"][0]["visible"][i * len(quiver_figure.data) + j] = True

    buttons.append(dict(
        label="Today",
        method="update",
        args=[{"visible": [False] * len(fig_wind.data)},]  # Reset visibility
    ))

    for i in range(len(quiver_figure_today.data)):
        buttons[-1]["args"][0]["visible"][len(fig_wind.data) - len(quiver_figure_today.data) + i] = True

    fig_wind.update_layout(
        title="Wind Vectors",
        updatemenus=[dict(type="buttons", buttons=buttons)],
        width=1200, height=1200,
    )
    fig_wind.write_html(os.path.join(output_dir, "wind_vectors.html"), auto_open=True)