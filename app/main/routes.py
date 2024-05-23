# from flask import render_template, request, Blueprint
from flask import Blueprint

main = Blueprint("main", __name__)

# #  Route decorators
# @main.route("/")
# @main.route("/home")
# def home():
#     return render_template("home.html")

from flask import Flask, request, jsonify, render_template
import json

# app = Flask(__name__)

# Function to read sensor data from a JSON file (simulating the database)
# def get_sensor_data():
#     with open('app/main/data/sensor_data.json', 'r') as file:
#         data = json.load(file)
#     return data

# @main.route('/')
# def index():
#     return render_template('home.html')

# @main.route('/data')
# def data():
#     sensor_data = get_sensor_data()
#     return jsonify(sensor_data)

def get_sensor_data():
    with open('app/main/data/sensor_data.json', 'r') as file:
        data = json.load(file)
    return data

def save_sensor_data(data):
    with open('app/main/data/sensor_data.json', 'w') as file:
        json.dump(data, file)

@main.route('/')
def index():
    return render_template('home.html')

@main.route('/data')
def data():
    sensor_data = get_sensor_data()
    return jsonify(sensor_data)

@main.route('/ldr_data', methods=['POST'])
def ldr_data():
    ldr_value = request.form['value']
    sensor_data = get_sensor_data()
    sensor_data['light'] = ldr_value  # Update the light data
    save_sensor_data(sensor_data)
    return "Data received"