document.addEventListener('DOMContentLoaded', function() {
    fetch('/data')
        .then(response => response.json())
        .then(data => {
            const lightCtx = document.getElementById('lightChart').getContext('2d');
            const moistureCtx = document.getElementById('moistureChart').getContext('2d');
            const temperatureCtx = document.getElementById('temperatureChart').getContext('2d');
            const humidityCtx = document.getElementById('humidityChart').getContext('2d');

            new Chart(lightCtx, {
                type: 'bar',
                data: {
                    labels: ['Light Intensity'],
                    datasets: [{
                        label: 'Light Intensity (%)',
                        data: [data.light],
                        backgroundColor: 'rgba(255, 206, 86, 0.2)',
                        borderColor: 'rgba(255, 206, 86, 1)',
                        borderWidth: 1
                    }]
                },
                options: {
                    scales: {
                        y: {
                            beginAtZero: true,
                            max: 100
                        }
                    }
                }
            });

            new Chart(moistureCtx, {
                type: 'bar',
                data: {
                    labels: ['Moisture Level'],
                    datasets: [{
                        label: 'Moisture Level (%)',
                        data: [data.moisture],
                        backgroundColor: 'rgba(54, 162, 235, 0.2)',
                        borderColor: 'rgba(54, 162, 235, 1)',
                        borderWidth: 1
                    }]
                },
                options: {
                    scales: {
                        y: {
                            beginAtZero: true,
                            max: 100
                        }
                    }
                }
            });

            new Chart(temperatureCtx, {
                type: 'bar',
                data: {
                    labels: ['Temperature'],
                    datasets: [{
                        label: 'Temperature (°C)',
                        data: [data.temperature],
                        backgroundColor: 'rgba(255, 99, 132, 0.2)',
                        borderColor: 'rgba(255, 99, 132, 1)',
                        borderWidth: 1
                    }]
                },
                options: {
                    scales: {
                        y: {
                            beginAtZero: true,
                            max: 50
                        }
                    }
                }
            });

            new Chart(humidityCtx, {
                type: 'bar',
                data: {
                    labels: ['Humidity'],
                    datasets: [{
                        label: 'Humidity (%)',
                        data: [data.humidity],
                        backgroundColor: 'rgba(75, 192, 192, 0.2)',
                        borderColor: 'rgba(75, 192, 192, 1)',
                        borderWidth: 1
                    }]
                },
                options: {
                    scales: {
                        y: {
                            beginAtZero: true,
                            max: 100
                        }
                    }
                }
            });
        });
});
