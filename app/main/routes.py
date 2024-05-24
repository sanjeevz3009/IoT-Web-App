from flask import render_template, request, Blueprint, jsonify, json
from flask import Blueprint
import pandas as pd

main = Blueprint("main", __name__)

# Global variables to store the received data
bin_data = {'distance': None, 'temperature': None, 'humidity': None}

@main.route('/data', methods=['POST'])
def receive_data():
    data = request.json
    if not data:
        return jsonify({'error': 'No data received'}), 400
    distance = data.get('distance')
    temperature = data.get('temperature')
    humidity = data.get('humidity')
    print(f"Received data - Distance: {distance} cm, Temperature: {temperature} C, Humidity: {humidity}%")
    return jsonify({'message': 'Data received successfully'}), 200

#  Route decorators
@main.route("/")
@main.route("/home")
def home():
    # global bin_level
    # return render_template("home.html", bin_data=bin_data)
    # Load test data from JSON file
    with open('app/main/data/sensor_data.json', 'r') as f:
        test_data = json.load(f)
    return render_template("home.html", bin_data=test_data)

@main.route('/chart')
def chart():
    # Read the CSV file
    df = pd.read_csv('test_dataset.csv')

    # Convert the 'Timestamp' column to datetime format
    df['Timestamp'] = pd.to_datetime(df['Timestamp'])

    # Extract the day of the week from the 'Timestamp' column
    df['Day of the Week'] = df['Timestamp'].dt.day_name()

    # Calculate the average bin level for each day of the week
    avg_bin_levels = df.groupby('Day of the Week')['Bin Level'].mean()

    # Prepare data for Chart.js
    chart_data = {
        'labels': avg_bin_levels.index.tolist(),
        'values': avg_bin_levels.values.tolist()
    }

    # Return JSON data to be rendered by Chart.js
    return render_template('chart.html', chart_data=json.dumps(chart_data))
