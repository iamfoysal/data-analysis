import csv

data = [
    ["Duration", "Average_Pulse", "Max_Pulse", "Calorie_Burnage", "Hours_Work", "Hours_Sleep"],
    [30, 80, 120, 240, 10, 7],
    [30, 85, 120, 250, 10, 7],
    [45, 90, 130, 260, 8, 7],
    [45, 95, 130, 270, 8, 7],
    [45, 100, 140, 280, 0, 7],
    [60, 105, 140, 290, 7, 8],
    [60, 110, 145, 300, 7, 8],
    [60, 115, 145, 310, 8, 8],
    [75, 120, 150, 320, 0, 8],
    [75, 125, 150, 330, 8, 8],
]

filename = "files/workout_data.csv"
with open(filename, mode="w", newline="", encoding="utf-8") as file:
    writer = csv.writer(file)
    writer.writerows(data)

print(f"Data has been successfully saved to {filename}.")
