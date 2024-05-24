import csv
import random
from datetime import datetime, timedelta

# Function to generate random bin levels
def generate_bin_level():
    return random.randint(0, 100)

# Function to generate random timestamps
def generate_timestamp():
    start_date = datetime(2020, 5, 1)  # Start date for the dataset
    end_date = datetime(2024, 5, 31)   # End date for the dataset
    delta = end_date - start_date
    random_days = random.randint(0, delta.days)
    random_hours = random.randint(0, 23)
    random_minutes = random.randint(0, 59)
    random_seconds = random.randint(0, 59)
    return start_date + timedelta(days=random_days, hours=random_hours, minutes=random_minutes, seconds=random_seconds)

# Function to get the day of the week
def get_day_of_week(timestamp):
    return timestamp.strftime('%A')

# Generate test data
data = []
for _ in range(700):  # Adjust the number of rows as needed
    timestamp = generate_timestamp()
    bin_level = generate_bin_level()
    day_of_week = get_day_of_week(timestamp)
    data.append([timestamp, day_of_week, bin_level])

# Save data to CSV
with open('test_dataset.csv', mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['Timestamp', 'Day of the Week', 'Bin Level'])
    for row in data:
        writer.writerow(row)

print("Test dataset generated and saved to 'test_dataset.csv'")
