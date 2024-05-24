from flask import render_template, request, Blueprint, jsonify, json
from flask import Blueprint

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
