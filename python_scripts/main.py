import os
from data_loader import load_data
from data_processor import prepare_data, interpolate_data
from plot_generator import create_temperature_plot, create_pressure_plot, create_wind_plot



def main(filepath, output_dir, num_interp_points=50):
    """Main function to process and visualize weather data."""
    data = load_data(filepath)
    vanes_data, stations_data = prepare_data(data)
    xi, yi, temperature_interp_all_days, pressure_interp_all_days = interpolate_data(stations_data, num_interp_points)

    create_temperature_plot(xi, yi, temperature_interp_all_days, output_dir)
    create_pressure_plot(xi, yi, pressure_interp_all_days, output_dir)
    create_wind_plot(vanes_data, stations_data, output_dir)


if __name__ == "__main__":
    filepath = "D:/oop_3_work/data_json/data.json"  # Replace with your data file path
    output_dir = "D:/oop_3_work/build/"
    os.makedirs(output_dir, exist_ok=True)
    main(filepath, output_dir)


