import sqlite3
import pandas as pd
from faker import Faker

fake = Faker()

# Database setup
db_name = "db/users.db"
table_name = "users"

def create_database():
    conn = sqlite3.connect(db_name)
    cursor = conn.cursor()
    cursor.execute(f"""
        CREATE TABLE IF NOT EXISTS {table_name} (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT,
            email TEXT,
            address TEXT,
            phone TEXT,
            birth_date TEXT
        )
    """)
    conn.commit()
    conn.close()

def insert_fake_data(n=100):
    conn = sqlite3.connect(db_name)
    cursor = conn.cursor()
    for _ in range(n):
        cursor.execute(f"""
            INSERT INTO {table_name} (name, email, address, phone, birth_date)
            VALUES (?, ?, ?, ?, ?)
        """, (
            fake.name(),
            fake.email(),
            fake.address(),
            fake.phone_number(),
            fake.date_of_birth(minimum_age=18, maximum_age=80).strftime("%Y-%m-%d")
        ))
    conn.commit()
    conn.close()



if __name__ == "__main__":
    create_database()
    insert_fake_data(100)
    