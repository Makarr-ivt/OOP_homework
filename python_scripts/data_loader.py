import json

def load_data(filepath):
    """Load weather data from a JSON file."""
    try:
        with open(filepath, 'r') as f:
            data = json.load(f)
    except FileNotFoundError:
        print(f"Error: File '{filepath}' not found.")
        exit()
    except json.JSONDecodeError:
        print(f"Error: Invalid JSON format in '{filepath}'.")
        exit()
    return data
