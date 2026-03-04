import os

class AQIAgent:
    def __init__(self, filename):
        self.filename = filename


    def create_default_file(self):
        if not os.path.exists(self.filename):
            print("No sensor data file found. Creating sample data...\n")
            with open(self.filename, "w") as f:
                f.write("Region PM25 PM10 NO2 CO\n")
                f.write("Area1 35 80 40 0.8\n")
                f.write("Area2 120 300 90 2.5\n")
                f.write("Area3 25 40 20 0.5\n")


    def read_environment(self):
        self.create_default_file()
        data = []

        with open(self.filename, "r") as file:
            next(file)  # Skip header line
            for line in file:
                region, pm25, pm10, no2, co = line.split()
                data.append({
                    "region": region,
                    "pm25": float(pm25),
                    "pm10": float(pm10),
                    "no2": float(no2),
                    "co": float(co)
                })
        return data


    def calculate_aqi(self, pm25, pm10):
        score = (pm25 * 0.6) + (pm10 * 0.4)

        if score <= 50:
            category = "Good"
            advice = "Air quality is satisfactory."
        elif score <= 100:
            category = "Moderate"
            advice = "Sensitive groups should reduce outdoor activity."
        elif score <= 200:
            category = "Poor"
            advice = "People with breathing issues should avoid outdoor activity."
        elif score <= 300:
            category = "Very Poor"
            advice = "Limit outdoor exposure."
        else:
            category = "Severe"
            advice = "Health alert! Avoid going outside."

        return score, category, advice


    def run(self):
        data = self.read_environment()
        print("\nAQI Monitoring System\n")
        for entry in data:
            score, category, advice = self.calculate_aqi(entry["pm25"], entry["pm10"])
            print("Region:", entry["region"])
            print("PM2.5:", entry["pm25"], " PM10:", entry["pm10"])
            print("AQI Score:", round(score, 2))
            print("Category:", category)
            print("Advice:", advice)
            print("-" * 40)


if __name__ == "__main__":
    agent = AQIAgent("sensor_data.txt")
    agent.run()